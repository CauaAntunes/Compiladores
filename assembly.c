#define MAXSIZE 1024*1024

int str = 1;
char *regs[4] = {NULL};
char* data;
char* prog;
char* endlbl;

void memTemp(){
	int i;
	for(i = 0; i < temp; i++){
		char aux[64];
		sprintf(aux,"__temp%d",i);
		entry_t *e = ht_get(ht, aux);
		if(e->reg == -2){
			sprintf(aux,"\t.comm\t__temp%d,4,4\n",i);
			strcat(data,aux);
		}
	}
}

void findReg(int *x1, int *x2){
	char aux[64];

	if(*x1 < 0){
		int i;
		for(i = 0; i < 4 && regs[i] != NULL; i++);
		i %= 4;

		if (regs[i] != NULL){
			entry_t *e = ht_get(ht, regs[i]);

			if(e->nature == NAT_PAR){
				sprintf(aux,"\tmovl\t%%e%cx, -%d(%%rbp)\n", 'a'+i, e->params*4);
			} else {
				sprintf(aux,"\tmovl\t%%e%cx, %s(%%rip)\n", 'a'+i, regs[i]);
			}
			strcat(prog,aux);

			e->reg = -2;
		}
		*x1 = i;
	}
	if(x2 != NULL) {
		int i;
		for(i = 0; i < 4 && regs[i] != NULL; i++);
		i %= 4;

		if(i == *x1) i++;

		if (regs[i] != NULL){
			entry_t *e = ht_get(ht, regs[i]);

			if(e->nature == NAT_PAR){
				sprintf(aux,"\tmovl\t%%e%cx, -%d(%%rbp)\n", 'a'+i, e->params*4);
			} else {
				sprintf(aux,"\tmovl\t%%e%cx, %s(%%rip)\n", 'a'+i, regs[i]);
			}
			strcat(prog,aux);

			e->reg = -2;
		}
		*x2 = i;
	}
}

void asmLabel(TAC *tac){
	char aux[16];
	sprintf(aux,".%s:\n",tac->op_keys[0]);
	strcat(prog,aux);
}

void asmArithmetic(TAC *tac){
	char aux[64];
	int x[2] = {-1, -1};

	entry_t *e1 = ht_get(ht, tac->op_keys[1]);
	if(e1->reg < 0){
		findReg(&x[0], NULL);

		if(tac->op_keys[1][0] == '\''){
			sprintf(aux,"\tmovl\t$%d, %%e%cx\n",tac->op_keys[1][1],'a'+x[0]);
		} else if(tac->op_keys[1][0] > '9' || tac->op_keys[1][0] < '0'){
			if(e1->nature == NAT_PAR){
				sprintf(aux,"\tmovl\t-%d(%%rbp), %%e%cx\n", 4*e1->params,'a'+x[0]);
			} else {
				sprintf(aux,"\tmovl\t%s(%%rip), %%e%cx\n",tac->op_keys[1],'a'+x[0]);
			}
		} else {
			sprintf(aux,"\tmovl\t$%d, %%e%cx\n",atoi(tac->op_keys[1]),'a'+x[0]);
		}
		strcat(prog,aux);
	} else x[0] = e1->reg;

	 if(tac->op_keys[2][0] == '\'') switch(tac->type){
		case TAC_ADD:
			sprintf(aux,"\taddl\t$%d, %%e%cx\n",tac->op_keys[2][1],'a'+x[0]);
			break;

		case TAC_SUB:
			sprintf(aux,"\tsubl\t$%d, %%e%cx\n",tac->op_keys[2][1],'a'+x[0]);
			break;

		case TAC_MUL:
			sprintf(aux,"\timull\t$%d, %%e%cx\n",tac->op_keys[2][1],'a'+x[0]);
			break;
	} else if(tac->op_keys[2][0] > '9' || tac->op_keys[2][0] < '0'){
		entry_t *e2 = ht_get(ht, tac->op_keys[2]);
		if(e2->reg < 0){
			findReg(&x[0], &x[1]);
			if(e2->nature == NAT_PAR){
				sprintf(aux,"\tmovl\t-%d(%%rbp), %%e%cx\n", 4*e2->params,'a'+x[1]);
			} else {
				sprintf(aux,"\tmovl\t%s(%%rip), %%e%cx\n",tac->op_keys[2],'a'+x[1]);
			}
			strcat(prog,aux);
		} else {
			x[1] = e2->reg;
		}
		switch(tac->type){
			case TAC_ADD:
				sprintf(aux,"\taddl\t%%e%cx, %%e%cx\n",'a'+x[0],'a'+x[1]);
				break;

			case TAC_SUB:
				sprintf(aux,"\tsubl\t%%e%cx, %%e%cx\n",'a'+x[1],'a'+x[0]);
				int i = x[1];
				x[1] = x[0];
				x[0] = i; 
				break;

			case TAC_MUL:
				sprintf(aux,"\timull\t%%e%cx, %%e%cx\n",'a'+x[0],'a'+x[1]);
				break;
		}
	} else switch(tac->type){
		case TAC_ADD:
			sprintf(aux,"\taddl\t$%d, %%e%cx\n",atoi(tac->op_keys[2]),'a'+x[0]);
			break;

		case TAC_SUB:
			sprintf(aux,"\tsubl\t$%d, %%e%cx\n",atoi(tac->op_keys[2]),'a'+x[0]);
			break;

		case TAC_MUL:
			sprintf(aux,"\timull\t$%d, %%e%cx\n",atoi(tac->op_keys[2]),'a'+x[0]);
			break;
	}
	strcat(prog,aux);

	entry_t *e = ht_get(ht, tac->op_keys[0]);
	if(x[1] >= 0){
		regs[x[0]] = NULL;
		regs[x[1]] = tac->op_keys[0];
		e->reg = x[1];
	} else {
		regs[x[0]] = tac->op_keys[0];
		e->reg = x[0];
	}
}

void asmDiv(TAC *tac){
	char aux[64];

	if(tac->op_keys[2][0] == '\''){
		sprintf(aux,"\tmovl\t$%d, %%esi\n",tac->op_keys[2][1]);
	} else if(tac->op_keys[2][0] > '9' || tac->op_keys[2][0] < '0'){
		entry_t *e = ht_get(ht, tac->op_keys[2]);

		if(e->reg < 0){
			if(e->nature == NAT_PAR){
				sprintf(aux,"\tmovl\t-%d(%%rbp), %%esi\n", 4*e->params);
			} else {
				sprintf(aux,"\tmovl\t%s(%%rip), %%esi\n",tac->op_keys[2]);
			}
		} else {
			sprintf(aux,"\tmovl\t%%e%cx, %%esi\n",'a'+e->reg);
			regs[e->reg] = NULL;
			e->reg = -1;
		}
	} else {
		sprintf(aux,"\tmovl\t$%d, %%esi\n",atoi(tac->op_keys[2]));
	}
	strcat(prog,aux);

	entry_t *e = ht_get(ht, tac->op_keys[1]);

	int i;
	for(i = 0; i < 4; i+=3)
		if(i != e->reg && regs[i] != NULL){
			entry_t *e0 = ht_get(ht, regs[i]);
			if(e0->nature == NAT_PAR){
				sprintf(aux,"\tmovl\t%%e%cx, -%d(%%rbp)\n",'a'+i, 4*e0->params);
			} else {
				sprintf(aux,"\tmovl\t%%e%cx, %s(%%rip)\n",'a'+i,regs[i]);
			}
			strcat(prog,aux);
			e0->reg == -2;
	}

	if(e->reg < 0){
		if(tac->op_keys[1][0] == '\''){
			sprintf(aux,"\tmovl\t$%d, %%eax\n",tac->op_keys[1][1]);
		} else if(tac->op_keys[1][0] > '9' || tac->op_keys[1][0] < '0'){
			if(e->nature == NAT_PAR){
				sprintf(aux,"\tmovl\t-%d(%%rbp), %%eax\n",4*e->params);
			} else {
				sprintf(aux,"\tmovl\t%s(%%rip), %%eax\n",tac->op_keys[1]);
			}
		} else {
			sprintf(aux,"\tmovl\t$%d, %%eax\n",atoi(tac->op_keys[1]));
		}
		strcat(prog,aux);
	} else if (e->reg > 0){
		sprintf(aux,"\tmovl\t%%e%cx, %%eax\n",'a'+e->reg);
		regs[e->reg] = NULL;
		e->reg = -1;
		strcat(prog,aux);
	}

	sprintf(aux,"\tcltd\n\tidivl\t%%esi\n");
	strcat(prog,aux);
	
	e = ht_get(ht, tac->op_keys[0]);
	e->reg = 0;
	regs[0] = tac->op_keys[0];
	regs[3] = NULL;
}

void asmMov(TAC *tac){
	char aux[64];
	entry_t *e0 = ht_get(ht, tac->op_keys[0]);
	entry_t *e1 = ht_get(ht, tac->op_keys[1]);

	if(e0->reg >= 0){
		regs[e0->reg] == NULL;
		e0->reg = -1;
	}

	if(tac->op_keys[1][0] == '\''){
		sprintf(aux,"\tmovl\t$%d, ", tac->op_keys[1][1]);
	} else if(tac->op_keys[1][0] > '9' || tac->op_keys[1][0] < '0'){
		if(e1->reg < 0){
			findReg(&(e1->reg), NULL);
			if(e1->nature == NAT_PAR){
				sprintf(aux,"\tmovl\t-%d(%%rbp), %%e%cx\n", 4*e1->params, 'a'+e1->reg);
			} else {
				sprintf(aux,"\tmovl\t%s(%%rip), %%e%cx\n", tac->op_keys[1], 'a'+e1->reg);
			}
			strcat(prog,aux);
		}

		sprintf(aux,"\tmovl\t%%e%cx, ", 'a'+e1->reg);
		regs[e1->reg] = NULL;
		e1->reg = -1;

	} else sprintf(aux,"\tmovl\t$%d, ", atoi(tac->op_keys[1]));
	strcat(prog, aux);

	if(e0->nature == NAT_PAR){
		sprintf(aux,"-%d(%%rbp)\n",4*e0->params);
	} else {
		sprintf(aux,"%s(%%rip)\n",tac->op_keys[0]);
	}
	strcat(prog, aux);
}

void asmInc(TAC *tac){
	char aux[64];

	entry_t *e = ht_get(ht, tac->op_keys[0]);
	if(e->reg < 0){
		findReg(&(e->reg),NULL);

		if(e->nature == NAT_PAR){
			sprintf(aux,"\tmovl\t-%d(%%rbp), %%e%cx\n", 4*e->params, 'a'+e->reg);
		} else {
			sprintf(aux,"\tmovl\t%s(%%rip), %%e%cx\n", tac->op_keys[0], 'a'+e->reg);
		}
		strcat(prog,aux);
	}

	if(e->nature == NAT_PAR){
		sprintf(aux,"\taddl\t$1, %%e%cx\n\tmovl\t%%e%cx, -%d(%%rbp)\n", 'a'+e->reg, 'a'+e->reg, 4*e->params);
	} else {
		sprintf(aux,"\taddl\t$1, %%e%cx\n\tmovl\t%%e%cx, %s(%%rip)\n", 'a'+e->reg, 'a'+e->reg, tac->op_keys[0]);
	}
	strcat(prog,aux);

	regs[e->reg] = NULL;
	e->reg = -1;
}

void asmVarDef(TAC *tac){
	char aux[256];
	if(tac->op_keys[1] != NULL){
		sprintf(aux,"\t.globl\t%s\n\t.align\t4\n\t.type\t%s, @object\n\t.size\t%s, 4\n%s:\n", tac->op_keys[0], tac->op_keys[0], tac->op_keys[0], tac->op_keys[0]);
		strcat(data,aux);

		int value;
		//entry_t *e = ht_get(ht, tac->op_keys[0]);
		//if(e->data_type == TYPE_INT){
			if(tac->op_keys[1][0] == '\''){
				value = tac->op_keys[1][1];
			} else {
				value = atoi(tac->op_keys[1]);
			}
		//}

		sprintf(aux,"\t.long\t%d\n",value);
		strcat(data,aux);
	} else {
		sprintf(aux,"\t.comm\t%s,4,4\n",tac->op_keys[0]);
		strcat(data,aux);
	}
}

void asmVecDef(TAC *tac){
	char aux[256];
	if(tac->prev != NULL && tac->prev->type == TAC_SYMBOL){
		sprintf(aux,"\t.globl\t%s\n\t.align\t4\n\t.type\t%s, @object\n\t.size\t%s, %d\n%s:\n", tac->op_keys[0], tac->op_keys[0], tac->op_keys[0], atoi(tac->op_keys[1])*4,tac->op_keys[0]);
		strcat(data,aux);

		TAC *t;
		for(t = tac; t->prev != NULL && t->prev->type == TAC_SYMBOL; t = t->prev);
		//entry_t *e = ht_get(ht, tac->op_keys[0]);
		//if(e.data_type == TYPE_INT){
		for(; t != tac; t = t->next){
			int value;
			if(t->op_keys[0][0] == '\''){
				value = t->op_keys[0][1];
			} else {
				value = atoi(t->op_keys[0]);
			}
			sprintf(aux,"\t.long\t%d\n",value);
			strcat(data,aux);
		}
		//}
	} else {
		sprintf(aux,"\t.comm\t%s,%d,4\n",tac->op_keys[0],atoi(tac->op_keys[1])*4);
		strcat(data,aux);
	}
}

void asmJL(TAC *tac){
	char aux[32];
	sprintf(aux,"\tjl\t.%s\n",tac->op_keys[0]);
	strcat(prog, aux);
}

void asmJLE(TAC *tac){
	char aux[32];
	sprintf(aux,"\tjle\t.%s\n",tac->op_keys[0]);
	strcat(prog, aux);
}

void asmJG(TAC *tac){
	char aux[32];
	sprintf(aux,"\tjg\t.%s\n",tac->op_keys[0]);
	strcat(prog, aux);
}

void asmJGE(TAC *tac){
	char aux[32];
	sprintf(aux,"\tjge\t.%s\n",tac->op_keys[0]);
	strcat(prog, aux);
}

void asmJE(TAC *tac){
	char aux[32];
	sprintf(aux,"\tje\t.%s\n",tac->op_keys[0]);
	strcat(prog, aux);
}

void asmJNE(TAC *tac){
	char aux[32];
	sprintf(aux,"\tjne\t.%s\n",tac->op_keys[0]);
	strcat(prog, aux);
}

void asmJMP(TAC *tac){
	char aux[32];
	sprintf(aux,"\tjmp\t.%s\n",tac->op_keys[0]);
	strcat(prog, aux);
}

void asmComp(TAC *tac){
	char aux[64];
	entry_t *e0 = ht_get(ht, tac->op_keys[0]);
	entry_t *e1 = ht_get(ht, tac->op_keys[1]);
	int r0 = e0->reg;
	int r1 = e1->reg;

	if (r1 < 0){
		if(r0 < 0) findReg(&r1,NULL);
		else findReg(&r0, &r1);

		if(tac->op_keys[1][0] == '\'') {
			sprintf(aux,"\tmovl\t$%d, %%e%cx\n", tac->op_keys[1][1], 'a'+r1);
		} else if(tac->op_keys[1][0] > '9' || tac->op_keys[1][0] < '0'){
			if(e1->nature == NAT_PAR){
				sprintf(aux,"\tmovl\t-%d(%%rbp), %%e%cx\n", 4*e1->params, 'a'+r1);
			} else {
				sprintf(aux,"\tmovl\t%s(%%rip), %%e%cx\n", tac->op_keys[1], 'a'+r1);
			}
		} else sprintf(aux,"\tmovl\t$%d, %%e%cx\n", atoi(tac->op_keys[1]), 'a'+r1);
		strcat(prog,aux);
	}

	if(tac->op_keys[0][0] == '\''){
		sprintf(aux,"\tcmpl\t$%d, %%e%cx\n",tac->op_keys[0][1], r1+'a');
	} else if(tac->op_keys[0][0] > '9' || tac->op_keys[0][0] < '0'){
		if (r0 < 0){
			findReg(&r1,&r0);
			if(e0->nature == NAT_PAR){
				sprintf(aux,"\tmovl\t-%d(%%rbp), %%e%cx\n", 4*e0->params, 'a'+r0);
			} else {
				sprintf(aux,"\tmovl\t%s(%%rip), %%e%cx\n", tac->op_keys[0], 'a'+r0);
			}
			strcat(prog,aux);
		}
		sprintf(aux,"\tcmpl\t%%e%cx, %%e%cx\n",r0+'a', r1+'a');	
	} else sprintf(aux,"\tcmpl\t$%d, %%e%cx\n",atoi(tac->op_keys[0]), r1+'a');
	strcat(prog,aux);
}

void asmPrint(TAC *tac){
	char aux[64];
	if(tac->op_keys[0][0] == '\''){
		sprintf(aux,"\tmovl\t$%d, %%edi\n\tcall\tputchar\n",tac->op_keys[0][1]);
		strcat(prog,aux);
	} else {
		entry_t *e = ht_get(ht, tac->op_keys[0]);

		if(tac->op_keys[0][0] == '"'){
			if(e->reg < 0){
				e->reg = str;
				str++;
				sprintf(aux,".str%d:\n\t.string\t%s\n",e->reg,tac->op_keys[0]);
				strcat(data,aux);
			}
			sprintf(aux,"\tmovl\t$.str%d, %%edi\n",e->reg);
		} else if(tac->op_keys[0][0] > '9' || tac->op_keys[0][0] < '0'){
			if(e->reg < 0){
				findReg(&(e->reg), NULL);
				if(e->nature == NAT_PAR){
					sprintf(aux,"\tmovl\t-%d(%%rbp), %%e%cx\n",4*e->params,'a'+e->reg);
				} else {
					sprintf(aux,"\tmovl\t%s(%%rip), %%e%cx\n",tac->op_keys[0],'a'+e->reg);
				}
				strcat(prog,aux);
			}

			sprintf(aux,"\tmovl\t%%e%cx, %%esi\n\tmovl\t$.str0, %%edi\n",'a'+e->reg);
			regs[e->reg] = NULL;
			e->reg = -1;
		} else {
			sprintf(aux,"\tmovl\t$%d, %%esi\n\tmovl\t$.str0, %%edi\n",atoi(tac->op_keys[0]));
		}
		strcat(prog,aux);

		if(regs[0] != NULL && e->reg != 0){
			entry_t *e0 = ht_get(ht,regs[0]);
			if(e0->nature == NAT_PAR){
				sprintf(aux,"\tmovl\t%%eax, -%d(%%rbp)\n", 4*e0->params);
			} else {
				sprintf(aux,"\tmovl\t%%eax, %s(%%rip)\n", regs[0]);
			}
			regs[0] = NULL;
			e0->reg = -2;
		}

		sprintf(aux,"\tmovl\t$0, %%eax\n\tcall\tprintf\n");
		strcat(prog,aux);
	}
}

void asmRead(TAC *tac){
	char aux[128];

	if(regs[0] != NULL){
		entry_t *e = ht_get(ht,tac->op_keys[0]);
		if(e->reg != 0){
			entry_t *e0 = ht_get(ht,regs[0]);
			if(e->nature == NAT_PAR){
				sprintf(aux,"\tmovl\t%%eax, -%d(%%rbp)\n", 4*e->params);
			} else {
				sprintf(aux,"\tmovl\t%%eax, %s(%%rip)\n", regs[0]);
			}
			strcat(prog,aux);
			regs[0] = NULL;
			e0->reg = -2;
		}
		e->reg = -1;
	}
	sprintf(aux,"\tmovl\t$%s, %%esi\n\tmovl\t$.str0, %%edi\n\tmovl\t$0, %%eax\n\tcall\t__isoc99_scanf\n",tac->op_keys[0]);
	strcat(prog,aux);
}

void asmArg(TAC *tac){
	char aux[64];
	if(tac->op_keys[1][0] == '\''){
		sprintf(aux,"\tmovl\t$%d, %s(%%rip)\n", tac->op_keys[1][1], tac->op_keys[0]);
	} else if(tac->op_keys[1][0] > '9' || tac->op_keys[1][0] < '0'){
		entry_t *e = ht_get(ht, tac->op_keys[1]);
		if(e->reg < 0){
			findReg(&(e->reg), NULL);
			sprintf(aux,"\tmovl\t%s(%%rip), %%e%cx\n", tac->op_keys[1], 'a'+e->reg);
			strcat(prog,aux);
		}

		sprintf(aux,"\tmovl\t%%e%cx, %s(%%rip)\n", 'a'+e->reg, tac->op_keys[0]);
		regs[e->reg] = NULL;
		e->reg = -1;
	} else {
		sprintf(aux,"\tmovl\t$%d, %s(%%rip)\n", atoi(tac->op_keys[1]), tac->op_keys[0]);
	}
	strcat(prog,aux);
}

void asmCall(TAC *tac){
	char aux[32];
	sprintf(aux,"\tcall\t%s\n",tac->op_keys[1]);
	strcat(prog,aux);

	ht_get(ht, tac->op_keys[0])->reg = 0;
	regs[0] = tac->op_keys[0];
	regs[1] = NULL;
	regs[2] = NULL;
	regs[3] = NULL;
}

void asmFBegin(TAC *tac){
	char aux[128];
	char *lbl = makeLabel();

	sprintf(aux,"\t.text\n\t.globl\t%s\n\t.type\t%s, @function\n%s:\n.%s:\n", tac->op_keys[0], tac->op_keys[0], tac->op_keys[0], lbl);
	strcat(prog, aux);
	strcat(prog,"\t.cfi_startproc\n\tpushq\t%rbp\n\t.cfi_def_cfa_offset 16\n\t.cfi_offset 6, -16\n\tmovq\t%rsp, %rbp\n\t.cfi_def_cfa_register 6\n");

	entry_t *e = ht_get(ht, tac->op_keys[0]);
	if(e->params > 0){
		int i = 0.75+e->params/4.0;
		sprintf(aux,"\tsubq\t$%d, %%rsp\n",16*i);
		strcat(prog,aux);
	}

	TAC *taux;
	for(taux = tac->prev; taux->type == TAC_SYMBOL; taux = taux->prev){
		sprintf(aux,"\tmovl\t%s(%%rip), %%eax\n\tmovl\t%%eax,-%d(%%rbp)\n",taux->op_keys[0],4*ht_get(ht,taux->op_keys[0])->params);
		strcat(prog,aux);
		sprintf(aux,"\t.comm\t%s,4,4\n",taux->op_keys[0]);
		strcat(data,aux);
	}

	endlbl = makeLabel();
}

void asmRet(TAC *tac){
	char aux[64];

	entry_t *e = ht_get(ht,tac->op_keys[0]);

	if(regs[0] != NULL){
		if(e->reg != 0){
			entry_t *e0 = ht_get(ht,regs[0]);
			if(e0->nature == NAT_PAR){
				sprintf(aux,"\tmovl\t%%eax, -%d(%%rbp)\n", 4*e0->params);
			} else {
				sprintf(aux,"\tmovl\t%%eax, %s(%%rip)\n", regs[0]); 
			}
			strcat(prog,aux);
			regs[0] = NULL;
			e0->reg = -2;
		}
	}

	if(tac->op_keys[0][0] == '\''){
		sprintf(aux, "\tmovl\t$%d, %%eax\n", tac->op_keys[0][1]);
		strcat(prog, aux);
	} else if(tac->op_keys[0][0] > '9' || tac->op_keys[0][0] < '0'){
		if(e->reg < 0){
			if(e->nature == NAT_PAR){
				sprintf(aux, "\tmovl\t-%d(%%rbp), %%eax\n", 4*e->params);
			} else {
				sprintf(aux, "\tmovl\t%s(%%rip), %%eax\n", tac->op_keys[0]);
			}
			strcat(prog, aux);
		} else if (e->reg > 0){
			sprintf(aux, "\tmovl\t%%e%cx, %%eax\n", 'a'+e->reg);
			strcat(prog, aux);
		}
	} else {
		sprintf(aux, "\tmovl\t$%d, %%eax\n", atoi(tac->op_keys[0]));
		strcat(prog, aux);
	}

	TAC *taux;
	for(taux = tac->next; taux->type == TAC_LABEL; taux = taux->next);
	if(taux->type != TAC_FEND){
		sprintf(aux,"\tjmp\t.%s\n", endlbl);
		strcat(prog,aux);
	}
}

void asmFEnd(TAC *tac){
	char aux[256];
	char *lbl = makeLabel();
	sprintf(aux,".%s:\n\tleave\n\t.cfi_def_cfa 7, 8\n\tret\n\t.cfi_endproc\n.%s:\n.size\t%s, .-%s\n", endlbl, lbl, tac->op_keys[0], tac->op_keys[0]);
	strcat(prog,aux);
}

void asmVWrite(TAC *tac){
	char aux[64];

	entry_t *e2 = ht_get(ht, tac->op_keys[2]);

	if ((tac->op_keys[1][0] > '9' || tac->op_keys[1][0] < '0') && tac->op_keys[1][0] != '\''){
		// se 2ºparam = var
		if(e2->reg == 0){
			findReg(&(e2->reg), &(e2->reg));
			regs[0] = NULL;
			sprintf(aux, "\tmovl\t%%eax, %%e%cx\n",'a'+e2->reg);
			strcat(prog,aux);
		}

		entry_t *e1 = ht_get(ht, tac->op_keys[1]);
		if(e1->reg != 0){
			if(regs[0] != NULL){
				entry_t *e = ht_get(ht, regs[0]);
				if(e->nature == NAT_PAR){
					sprintf(aux,"\tmovl\t%%eax, -%d(%%rbp)\n",4*e->params);
				} else {
					sprintf(aux,"\tmovl\t%%eax, %s(%%rip)\n",regs[0]);
				}
				strcat(prog,aux);
				e->reg = -2;
				regs[0] = NULL;
			}

			if(e1->reg < 0){
				if(e1->nature == NAT_PAR){
					sprintf(aux,"\tmovl\t-%d(%%rbp), %%eax\n", 4*e1->params);
				} else {
					sprintf(aux,"\tmovl\t%s(%%rip), %%eax\n", tac->op_keys[1]);
				}
			} else {
				regs[e1->reg] = NULL;
				sprintf(aux,"\tmovl\t%%e%cx, %%eax\n", 'a'+e1->reg);
			}
			strcat(prog,aux);
			e1->reg = 0;
		}

		if(tac->op_keys[2][0] == '\''){
			sprintf(aux,"\tcltq\n\tmovl\t$%d, %s(,%%rax,4)\n", tac->op_keys[2][1], tac->op_keys[0]);
		} else if(tac->op_keys[2][0] > '9' || tac->op_keys[2][0] < '0'){
			// se 3ºparam = var
			if(e2->reg < 0){
				findReg(&(e1->reg), &(e2->reg));
				if(e2->nature == NAT_PAR){
					sprintf(aux,"\tmovl\t-%d(%%rbp), %%e%cx\n", 4*e2->params, 'a'+e2->reg);
				} else {
					sprintf(aux,"\tmovl\t%s(%%rip), %%e%cx\n", tac->op_keys[2], 'a'+e2->reg);
				}
				strcat(prog,aux);
				regs[e2->reg] = NULL;
			}

			sprintf(aux,"\tcltq\n\tmovl\t%%e%cx, %s(,%%rax,4)\n", 'a'+e2->reg, tac->op_keys[0]);
		} else {
			// se 3ºparam = num
			sprintf(aux,"\tcltq\n\tmovl\t$%d, %s(,%%rax,4)\n", atoi(tac->op_keys[2]), tac->op_keys[0]);
		}
		strcat(prog,aux);

		e1->reg = -1;
		e2->reg = -1;
	} else {
		// se 2ºparam = num
		int i;
		if(tac->op_keys[1][0] == '\''){
			i = tac->op_keys[1][1];
		} else {
			i = atoi(tac->op_keys[1]);
		}

		if(tac->op_keys[2][0] == '\''){
			sprintf(aux,"\tmovl\t$%d, %s+%d(%%rip)\n\n", tac->op_keys[2][1], tac->op_keys[0], 4*i);
		} else if(tac->op_keys[2][0] > '9' || tac->op_keys[2][0] < '0'){
			// se 3ºparam = var
			if(e2->reg < 0){
				findReg(&(e2->reg), NULL);

				if(e2->nature == NAT_PAR){
					sprintf(aux,"\tmovl\t-%d(%%rbp), %%e%cx\n", 4*e2->params, 'a'+e2->reg);
				} else {
					sprintf(aux,"\tmovl\t%s(%%rip), %%e%cx\n", tac->op_keys[2], 'a'+e2->reg);
				}
				strcat(prog,aux);
				regs[e2->reg] = NULL;
			}

			sprintf(aux,"\tmovl\t%%e%cx, %s+%d(%%rip)\n", 'a'+e2->reg, tac->op_keys[0], 4*i);
			e2->reg = -1;
		} else {
			// se 3ºparam = num
			sprintf(aux,"\tmovl\t$%d, %s+%d(%%rip)\n\n", atoi(tac->op_keys[2]), tac->op_keys[0], 4*i);
		}
		strcat(prog,aux);
	}	
}

void asmVRead(TAC *tac){
	char aux[64];
	int var;
	
	if ((tac->op_keys[1][0] > '9' || tac->op_keys[1][0] < '0') && tac->op_keys[1][0] != '\''){
		entry_t *e2 = ht_get(ht, tac->op_keys[2]);

		if(e2->reg != 0){
			if(regs[0] != NULL){
				entry_t *e = ht_get(ht, regs[0]);
				if(e->nature == NAT_PAR){
					sprintf(aux,"\tmovl\t%%eax, -%d(%%rbp)\n",4*e->params);
				} else {
					sprintf(aux,"\tmovl\t%%eax, %s(%%rip)\n",regs[0]);
				}
				strcat(prog,aux);
				e->reg = -2;
			}

			if(e2->reg < 0){
				if(e2->nature == NAT_PAR){
					sprintf(aux,"\tmovl\t-%d(%%rbp), %%eax\n", 4*e2->params);
				} else {
					sprintf(aux,"\tmovl\t%s(%%rip), %%eax\n", tac->op_keys[2]);
				}
			} else {
				regs[e2->reg] = NULL;
				sprintf(aux,"\tmovl\t%%e%cx, %%eax\n", 'a'+e2->reg);
			}
			strcat(prog,aux);
		}
		sprintf(aux, "\tcltq\n\tmovl\t%s(,%%rax,4), %%eax\n", tac->op_keys[1]);
		strcat(prog, aux);

		entry_t *e0 = ht_get(ht, tac->op_keys[0]);
		regs[0] = tac->op_keys[0];
		e0->reg = 0;
		e2->reg = -1;
	} else {
		entry_t *e0 = ht_get(ht, tac->op_keys[0]);
		findReg(&(e0->reg), NULL);
		regs[e0->reg] = tac->op_keys[0];

		int i;
		if(tac->op_keys[2][0] == '\''){
			i = tac->op_keys[2][1];
		} else {
			i = atoi(tac->op_keys[2]);
		}

		sprintf(aux,"\tmovl\t%s+%d(%%rip), %%e%cx\n",tac->op_keys[1], 4*i, 'a'+e0->reg);
		strcat(prog,aux);
	}
}

void makeASM(TAC *tac){
	data = (char*) malloc(MAXSIZE);
	prog = (char*) malloc(MAXSIZE);

	data[0] = 0;
	prog[0] = 0;

	for(tac = first(tac); tac != NULL; tac = tac->next){
		switch(tac->type){
			case TAC_SYMBOL:
				break;

			case TAC_LABEL:
				asmLabel(tac); break;

			case TAC_ADD:
			case TAC_SUB:
			case TAC_MUL:
				asmArithmetic(tac); break;

			case TAC_DIV:
				asmDiv(tac); break;

			case TAC_CMP:
				asmComp(tac); break;

			case TAC_JL:
				asmJL(tac); break; 

			case TAC_JLE:
				asmJLE(tac); break;

			case TAC_JG:
				asmJG(tac); break;

			case TAC_JGE:
				asmJGE(tac); break;

			case TAC_JE:
				asmJE(tac); break;

			case TAC_JNE:
				asmJNE(tac); break;

			case TAC_JMP:
				asmJMP(tac); break;

			case TAC_MOV:
				asmMov(tac); break;

			case TAC_CALL:
				asmCall(tac); break;

			case TAC_ARG:
				asmArg(tac); break;

			case TAC_RET:
				asmRet(tac); break;

			case TAC_FBEGIN:
				asmFBegin(tac); break;

			case TAC_FEND:
				asmFEnd(tac); break;

			case TAC_PRINT:
				asmPrint(tac); break;

			case TAC_READ:
				asmRead(tac); break;

			case TAC_VWRITE:
				asmVWrite(tac); break;

			case TAC_VREAD:
				asmVRead(tac); break;

			case TAC_INC:
				asmInc(tac); break;

			case TAC_VARDEF:
				asmVarDef(tac); break;

			case TAC_VECDEF:
				asmVecDef(tac); break;

			default: break;
		}
		/*printf("%s",data);
		data[0] = 0;
		printf("%s",prog);
		prog[0] = 0;
		int i;
		for(i = 0; i < 4; i++)
			if(regs[i] != NULL)
			printf("%%e%cx: %s\n",'a'+i,regs[i]);*/
	}
	memTemp();
	printf("\t.data\n%s.str0:\n\t.string\t\"%%d\"\n", data);
	printf("%s", prog);
}

