#define MAXSIZE 1024

int printNumber = 0;
char *regs[4] = {NULL};
char* data;
char* prog;

void findReg(int *x1, int *x2){
	char aux[64];

	if(*x1 < 0){
		int i;
		for(i = 0; i < 4 && regs[i] != NULL; i++);
		i %= 4;

		if (regs[i] != NULL){
			sprintf(aux,"\tmovl\t%%e%cx, %s(%%rip)\n", 'a'+i, regs[i]);
			strcat(prog,aux);

			entry_t *e = ht_get(ht, regs[i]);
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
			sprintf(aux,"\tmovl\t%%e%cx, %s(%%rip)\n", 'a'+i, regs[i]);
			strcat(prog,aux);

			entry_t *e = ht_get(ht, regs[i]);
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
	int i;
	int x[2] = {0,-1};

	entry_t *e1 = ht_get(ht, tac->op_keys[1]);
	if(e1->reg < 0){
		findReg(&x[0], NULL);
		if(tac->op_keys[1][0] > '9' || tac->op_keys[1][0] < '0'){
			sprintf(aux,"\tmovl\t%s(%%rip), %%e%cx\n",tac->op_keys[1],'a'+x[0]);
		} else {
			sprintf(aux,"\tmovl\t$%s, %%e%cx\n",tac->op_keys[1],'a'+x[0]);
		}
		strcat(prog,aux);
	} else x[0] = e1->reg;

	if(tac->op_keys[2][0] > '9' || tac->op_keys[2][0] < '0'){
		entry_t *e2 = ht_get(ht, tac->op_keys[2]);
		if(e2->reg < 0){
			findReg(&x[0], &x[1]);
			sprintf(aux,"\tmovl\t%s(%%rip), %%e%cx\n",tac->op_keys[2],'a'+x[1]);
			strcat(prog,aux);
		} else {
			x[1] = e2->reg;
		}
		switch(tac->type){
			case TAC_ADD:
				sprintf(aux,"\taddl\t%%e%cx, %%e%cx\n",'a'+x[0],'a'+x[1]);
				break;

			case TAC_SUB:
				sprintf(aux,"\tsubl\t%%e%cx, %%e%cx\n",'a'+x[0],'a'+x[1]);
				break;

			case TAC_MUL:
				sprintf(aux,"\timull\t%%e%cx, %%e%cx\n",'a'+x[0],'a'+x[1]);
				break;
		}
	} else switch(tac->type){
		case TAC_ADD:
			sprintf(aux,"\taddl\t$%s, %%e%cx\n",tac->op_keys[2],'a'+x[0]);
			break;

		case TAC_SUB:
			sprintf(aux,"\tsubl\t$%s, %%e%cx\n",tac->op_keys[2],'a'+x[0]);
			break;

		case TAC_MUL:
			sprintf(aux,"\timull\t$%s, %%e%cx\n",tac->op_keys[2],'a'+x[0]);
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

	if(tac->op_keys[2][0] > '9' || tac->op_keys[2][0] < '0'){
		entry_t *e = ht_get(ht, tac->op_keys[2]);

		if(e->reg < 0){
			sprintf(aux,"\tmovl\t%s(%%rip), %%esi\n",tac->op_keys[2]);
		} else {
			sprintf(aux,"\tmovl\t%%e%cx, %%esi\n",'a'+e->reg);
			regs[e->reg] = NULL;
			e->reg = -1;
		}
	} else {
		sprintf(aux,"\tmovl\t$%s, %%esi\n",tac->op_keys[2]);
	}
	strcat(prog,aux);

	entry_t *e = ht_get(ht, tac->op_keys[1]);

	int i;
	for(i = 0; i < 4; i+=3)
		if(i != e->reg && regs[i] != NULL){
			sprintf(aux,"\tmovl\t%%e%cx, %s(%%rip)\n",'a'+i,regs[i]);
			strcat(prog,aux);
			entry_t *e0 = ht_get(ht, regs[i]);
			e0->reg == -2;
	}

	if(e->reg < 0){
		if(tac->op_keys[1][0] <= '9' && tac->op_keys[1][0] >= '0'){
			sprintf(aux,"\tmovl\t$%s, %%eax\n",tac->op_keys[1]);
		} else {
			sprintf(aux,"\tmovl\t%s(%%rip), %%eax\n",tac->op_keys[1]);
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

	if(tac->op_keys[1][0] > '9' || tac->op_keys[1][0] < '0'){
		if(e1->reg < 0){
			findReg(&(e1->reg), NULL);
			sprintf(aux,"\tmovl\t%s(%%rip), %%e%cx\n", tac->op_keys[1], 'a'+e1->reg);
			strcat(prog,aux);
		}

		sprintf(aux,"\tmovl\t%%e%cx, %s(%%rip)\n", 'a'+e1->reg, tac->op_keys[0]);
		regs[e1->reg] = NULL;
		e1->reg = -1;

	} else sprintf(aux,"\tmovl\t$%s, %s(%%rip)\n", tac->op_keys[1], tac->op_keys[0]);
	strcat(prog, aux);
}

void asmInc(TAC *tac){
	char aux[64];

	entry_t *e = ht_get(ht, tac->op_keys[0]);
	if(e->reg < 0){
		findReg(&(e->reg),NULL);

		sprintf(aux,"\tmovl\t%s(%%rip), %%e%cx\n", tac->op_keys[0], 'a'+e->reg);
		strcat(prog,aux);
	}

	sprintf(aux,"\taddl\t$1, %%e%cx\n\tmovl\t%%e%cx, %s(%%rip)\n", 'a'+e->reg, 'a'+e->reg, tac->op_keys[0]);
	strcat(prog,aux);

	regs[e->reg] = NULL;
	e->reg = -1;
}

void asmVarDef(TAC *tac){
	char aux[256];
	if(tac->op_keys[1] != NULL){
		sprintf(aux,"\t.globl %s\n\t.align 4\n\t.type %s, @object\n\t.size %s, 4\n%s:\n", tac->op_keys[0], tac->op_keys[0], tac->op_keys[0], tac->op_keys[0]);
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

		sprintf(aux,"\t.long %d\n",value);
		strcat(data,aux);
	} else {
		sprintf(aux,"\t.comm\t%s,4,4\n",tac->op_keys[0]);
		strcat(data,aux);
	}
}

void asmVecDef(TAC *tac){
	char aux[256];
	if(tac->prev != NULL && tac->prev->type == TAC_SYMBOL){
		sprintf(aux,"\t.globl %s\n\t.align 4\n\t.type %s, @object\n\t.size %s, %d\n%s:\n", tac->op_keys[0], tac->op_keys[0], tac->op_keys[0], atoi(tac->op_keys[1])*4,tac->op_keys[0]);
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
			sprintf(aux,"\t.long %d\n",value);
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

		if(tac->op_keys[1][0] > '9' || tac->op_keys[1][0] < '0')
			sprintf(aux,"\tmovl\t%s(%%rip), %%e%cx\n", tac->op_keys[1], 'a'+r1);
		else sprintf(aux,"\tmovl\t$%s, %%e%cx\n", tac->op_keys[1], 'a'+r1);
		strcat(prog,aux);
	}
	if(tac->op_keys[0][0] > '9' || tac->op_keys[0][0] < '0'){
		if (r0 < 0){
			findReg(&r1,&r0);
			sprintf(aux,"\tmovl\t%s(%%rip), %%e%cx\n", tac->op_keys[0], 'a'+r0);
			strcat(prog,aux);
		}
		sprintf(aux,"\tcmpl\t%%e%cx, %%e%cx\n",r0+'a', r1+'a');	
	} else sprintf(aux,"\tcmpl\t$%s, %%e%cx\n",tac->op_keys[0], r1+'a');
	strcat(prog,aux);
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
				printf("TAC_CALL"); break;

			case TAC_ARG:
				printf("TAC_ARG"); break;

			case TAC_RET:
				printf("TAC_RET"); break;

			case TAC_FBEGIN:
				printf("TAC_FBEGIN"); break;

			case TAC_FEND:
				printf("TAC_FEND"); break;

			case TAC_PRINT:
				printf("TAC_PRINT"); break;

			case TAC_READ:
				printf("TAC_READ"); break;

			case TAC_VWRITE:
				printf("TAC_VWRITE"); break;
			// tac: 1o param nome vetor 2o param posicao e 3o var temporaria

			case TAC_VREAD:
				printf("TAC_VREAD"); break;

			case TAC_INC:
				asmInc(tac); break;

			case TAC_VARDEF:
				asmVarDef(tac); break;

			case TAC_VECDEF:
				asmVecDef(tac); break;

			default: break;
		}
	}
	printf("\t.data\n%s", data);
	printf("\t.text\n%s", prog);
}

