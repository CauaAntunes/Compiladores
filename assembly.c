#define MAXSIZE 1024

int printNumber = 0;
char *regs[4] = {NULL};
char* data;
char* prog;

void asmLabel(TAC *tac){
	char aux[16];
	sprintf(aux,".%s:\n",tac->op_keys[0]);
	strcat(prog,aux);
}

void asmArithmetic(TAC *tac){
	char aux[64];
	int i;
	int x[2] = {0,-1};

	for(i = 1; i < 3; i++){
		if(i == 1 || tac->op_keys[i][0] > '9' || tac->op_keys[i][0] < '0'){

			entry_t *e = ht_get(ht, tac->op_keys[i]);
			if(e->reg < 0){
				int j = 0;
				for(j = 0; j < 4 && regs[j] != NULL; j++);

				if(i==2 && j == x[0]) j++;
				j %= 4;

				if(regs[j] != NULL){
					sprintf(aux,"\tmovl\t%%e%cx, %s(%%rip)\n",'a'+j,regs[j]);
					strcat(prog,aux);

					entry_t *e0 = ht_get(ht, regs[j]);
					e0->reg == -2;
				}

				x[i-1] = j;

				regs[j] = tac->op_keys[i];
				if(tac->op_keys[i][0] > '9' || tac->op_keys[i][0] < '0'){
					sprintf(aux,"\tmovl\t%s(%%rip), %%e%cx\n",tac->op_keys[i],'a'+j);
					strcat(prog,aux);
				} else if (i==1){
					sprintf(aux,"\tmovl\t$%s, %%e%cx\n",tac->op_keys[i],'a'+j);
					strcat(prog,aux);
				}
			} else {
				x[i-1] = e->reg;
			}
		}
	}

	if(tac->op_keys[2][0] <= '9' && tac->op_keys[2][0] >= '0'){
		switch(tac->type){
			case TAC_ADD:
				sprintf(aux,"\taddl\t$%s, %%e%cx\n",tac->op_keys[2],'a'+x[0]);
				break;

			case TAC_SUB:
				sprintf(aux,"\tsubl\t$%s, %%e%cx\n",tac->op_keys[2],'a'+x[0]);
				break;

			case TAC_MUL:
				sprintf(aux,"\timull\t$%s, %%e%cx\n",tac->op_keys[2],'a'+x[0]);
				break;

			//case TAC_DIV: divisão é diferente

			default: aux[0] = 0; break;
		}
	} else switch(tac->type){
		case TAC_ADD:
			sprintf(aux,"\taddl\t%%e%cx, %%e%cx\n",'a'+x[0],'a'+x[1]);
			break;

		case TAC_SUB:
			sprintf(aux,"\tsubl\t%%e%cx, %%e%cx\n",'a'+x[0],'a'+x[1]);
			break;

		case TAC_MUL:
			sprintf(aux,"\timull\t%%e%cx, %%e%cx\n",'a'+x[0],'a'+x[1]);
			break;

		//case TAC_DIV: divisão é diferente

		default: aux[0] = 0; break;
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

	sprintf(aux,"\tcltd\n\tidivl %%esi\n");
	strcat(prog,aux);
	
	e = ht_get(ht, tac->op_keys[0]);
	e->reg = 0;
	regs[0] = tac->op_keys[0];
	regs[3] = NULL;
}

void asmMov(TAC *tac){
	entry_t *e0 = ht_get(ht, tac->op_keys[0]);
	entry_t *e1 = ht_get(ht, tac->op_keys[1]);

	if(e0->reg < 0){
		int i;
		for(i = 0; i < 4 && regs[i] != NULL; i++);
		i %= 4;

		if(i == e1->reg) i++;

		if (regs[i] != NULL){
			sprintf(aux,"\tmovl\t%%e%cx, __temp%d(%%rip)\n", 'a'+i, regs[i]);
			strcat(prog,aux);

			entry_t *e1 = ht_get(ht, regs[i]);
			e1->reg = -2;
		}

		if(e1->reg < 0){
			sprintf(aux,"\tmovl\t%s(%%rip), %%e%cx\n", tac->op_keys[1], 'a'+i);
		} else {
			sprintf(aux,"\tmovl\t%s(%%rip), %%e%cx\n", 'a'+e1->reg, 'a'+i);
		}

	} else {
		if(e1->reg < 0){
			sprintf(aux,"\tmovl\t%s(%%rip), %%e%cx\n", tac->op_keys[1], e0->reg);
		} else {
			sprintf(aux,"\tmovl\t%%e%cx, %%e%cx\n", e1->reg, e0->reg);
		}
		strcat(prog,aux);
	}
}

void asmInc(TAC *tac){
	char aux[64];
	entry_t *e = ht_get(ht, tac->op_keys[0]);

	if(e->reg < 0){
		int i;
		for(i = 0; i < 4 && regs[i] != NULL; i++);
		i %= 4;

		if (regs[i] != NULL){
			sprintf(aux,"\tmovl\t%%e%cx, __temp%d(%%rip)\n", 'a'+i, regs[i]);
			strcat(prog,aux);

			entry_t *e0 = ht_get(ht, regs[i]);
			e0->reg = -2;
		}

		sprintf(aux,"\tmovl\t%s(%%rip), %%e%cx\n", tac->op_keys[0], 'a'+i);
		strcat(prog,aux);
		regs[i] = tac->op_keys[0];
		e->reg = i;
	}

	sprintf(aux,"\taddl\t$1, %%e%cx\n", 'a'+e->reg);
	strcat(prog,aux);
}

void asmVarDef(TAC *tac){
	char *aux = (char*) malloc(256);
	sprintf(aux,"\t.globl %s\n\t.data\n\t.align 4\n\t.type %s, @object\n\t.size %s, 4\n%s:\n", tac->op_keys[0], tac->op_keys[0], tac->op_keys[0], tac->op_keys[0]);
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
}

void asmVecDef(TAC *tac){
	char aux[256];
	sprintf(aux,"\t.globl %s\n\t.data\n\t.align 4\n\t.type %s, @object\n\t.size %s, %d\n%s:\n", tac->op_keys[0], tac->op_keys[0], tac->op_keys[0], atoi(tac->op_keys[1])*4,tac->op_keys[0]);
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

			case TAC_GT:
				printf("TAC_ADD"); break;

			case TAC_LT:
				printf("TAC_LT"); break;

			case TAC_GE:
				printf("TAC_GE"); break;

			case TAC_LE:
				printf("TAC_LE"); break;

			case TAC_EQ:
				printf("TAC_EQ"); break;

			case TAC_NE:
				printf("TAC_NE"); break;

			case TAC_NOT:
				printf("TAC_NOT"); break;

			case TAC_JMP:
				printf("TAC_JMP"); break;

			case TAC_JZ:
				printf("TAC_JZ"); break;

			case TAC_JNZ:
				printf("TAC_JNZ"); break;

			case TAC_MOV:
				printf("TAC_MOV"); break;

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
	printf("%s", data);
	printf("%s", prog);
}
