#define	TAC_SYMBOL	0
#define	TAC_LABEL	1
#define	TAC_ADD		2	// LEITURA
#define	TAC_SUB		3	// LEITURA
#define	TAC_MUL		4	// LEITURA
#define	TAC_DIV		5	// LEITURA
#define	TAC_CMP		6	// LEITURA
#define	TAC_JL		7
#define	TAC_JLE		8
#define	TAC_JG		9
#define	TAC_JGE		10
#define	TAC_JE		11
#define	TAC_JNE		12
#define	TAC_JMP		15
#define	TAC_MOV		18	// LEITURA + ESCRITA
#define	TAC_CALL	19
#define TAC_ARG		20	// LEITURA
#define	TAC_RET		21	// LEITURA
#define	TAC_FBEGIN	22
#define	TAC_FEND	23
#define	TAC_PRINT	24	// LEITURA
#define	TAC_READ	25	// ESCRITA
#define	TAC_VWRITE	26
#define	TAC_VREAD	27
#define	TAC_INC		28
#define	TAC_VARDEF	29
#define	TAC_VECDEF	30

int label = 0, temp = 0;

TAC *makeTAC(AST *tree);
TAC *createTACBoolean(AST *tree, char* labTrue, char* labFalse);

TAC *createTAC(int type, char* op0, char* op1, char* op2){
	TAC *t = (TAC*) malloc(sizeof(TAC));
	t->type = type;
	t->op_keys[0] = op0;
	t->op_keys[1] = op1;
	t->op_keys[2] = op2;
	t->prev = NULL;
	t->next = NULL;
	return t;
}

TAC *first(TAC *tac){
	if(tac == NULL)
		return NULL;

	for(; tac->prev != NULL; tac = tac->prev);
	return tac;
}

void printTAC(TAC *tac){
	for(tac = first(tac); tac != NULL; tac = tac->next)
		if(tac->type != TAC_SYMBOL){
		switch(tac->type){

			case TAC_LABEL:
				printf("TAC_LABEL"); break;

			case TAC_ADD:
				printf("TAC_ADD"); break;

			case TAC_SUB:
				printf("TAC_SUB"); break;

			case TAC_MUL:
				printf("TAC_MUL"); break;

			case TAC_DIV:
				printf("TAC_DIV"); break;

			case TAC_CMP:
				printf("TAC_CMP"); break;

			case TAC_JL:
				printf("TAC_JL"); break;

			case TAC_JLE:
				printf("TAC_JLE"); break;

			case TAC_JG:
				printf("TAC_JG"); break;

			case TAC_JGE:
				printf("TAC_JGE"); break;

			case TAC_JE:
				printf("TAC_JE"); break;

			case TAC_JNE:
				printf("TAC_JNE"); break;

			case TAC_JMP:
				printf("TAC_JMP"); break;

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
				printf("TAC_INC"); break;

			case TAC_VARDEF:
				printf("TAC_VARDEF"); break;

			case TAC_VECDEF:
				printf("TAC_VECDEF"); break;

			default: printf("%d",tac->type); break;
		}

		int i;
		for(i = 0; i < 3; i++){
			if(tac->op_keys[i] != NULL)
				printf(" %s",tac->op_keys[i]);
		}
		printf("\n");
	}
}

char *makeLabel(){
	char *lab = (char*) malloc(sizeof(char)*13);
	sprintf(lab,".label%d",label);
	ht_set(ht,lab,lab);
	label++;
	return lab;
}

char *makeTemp(){
	char *lab = (char*) malloc(sizeof(char)*12);
	sprintf(lab,".temp%d",temp);
	ht_set(ht,lab,lab);
	temp++;
	return lab;
}

TAC *joinTAC(TAC *begin, TAC *end){
	if(end == NULL)
		return begin;

	if(begin == NULL)
		return end;

	TAC *aux;
	for(aux = end; aux->prev != NULL; aux = aux->prev);
	for(; begin->next != NULL; begin = begin->next);

	aux->prev = begin;
	begin->next = aux;
	return end;
}

TAC *createTACLabel(char *label){
	TAC *r = createTAC(TAC_LABEL,label,NULL,NULL);
	ht_get(ht,label)->label = r;
	return r;
}

TAC *createTACEqual(AST *tree, char* labTrue, char* labFalse){
	TAC *op0 = makeTAC(tree->son[0]);
	TAC *op1 = makeTAC(tree->son[1]);

	TAC *cmp = createTAC(TAC_CMP, op0->op_keys[0], op1->op_keys[0], NULL);

	TAC *jmp;
	if(labFalse == NULL){
		jmp = createTAC(TAC_JE, labTrue, NULL, NULL);
	} else {
		jmp = createTAC(TAC_JNE, labFalse, NULL, NULL);
	}

	return joinTAC(joinTAC(joinTAC(op0,op1),cmp),jmp);
}

TAC *createTACGreater(AST *tree, char* labTrue, char* labFalse){
	TAC *op0 = makeTAC(tree->son[0]);
	TAC *op1 = makeTAC(tree->son[1]);

	TAC *cmp = createTAC(TAC_CMP, op1->op_keys[0], op0->op_keys[0], NULL);

	TAC *jmp;
	if(labFalse == NULL){
		jmp = createTAC(TAC_JG, labTrue, NULL, NULL);
	} else {
		jmp = createTAC(TAC_JLE, labFalse, NULL, NULL);
	}

	return joinTAC(joinTAC(joinTAC(op0,op1),cmp),jmp);
}

TAC *createTACLess(AST *tree, char* labTrue, char* labFalse){
	TAC *op0 = makeTAC(tree->son[0]);
	TAC *op1 = makeTAC(tree->son[1]);

	TAC *cmp = createTAC(TAC_CMP, op1->op_keys[0], op0->op_keys[0], NULL);

	TAC *jmp;
	if(labFalse == NULL){
		jmp = createTAC(TAC_JL, labTrue, NULL, NULL);
	} else {
		jmp = createTAC(TAC_JGE, labFalse, NULL, NULL);
	}

	return joinTAC(joinTAC(joinTAC(op0,op1),cmp),jmp);
}

TAC *createTACAnd(AST *tree, char* labTrue, char* labFalse){
	TAC *o1 = createTACBoolean(tree->son[1],labTrue,labFalse);
	TAC *o0;
	if(labFalse != NULL){
		o0 = createTACBoolean(tree->son[0],NULL,labFalse);
	} else {
		char *end = makeLabel();
		o0 = createTACBoolean(tree->son[0],NULL,end);
		TAC *lend = createTACLabel(end);
		o1 = joinTAC(o1,lend);
	}
	return joinTAC(o0,o1);
}

TAC *createTACOr(AST *tree, char* labTrue, char* labFalse){
	TAC *o1 = createTACBoolean(tree->son[1],labTrue,labFalse);
	TAC *o0;
	if(labTrue != NULL){
		o0 = createTACBoolean(tree->son[0],labTrue,NULL);
	} else {
		char *end = makeLabel();
		o0 = createTACBoolean(tree->son[0],end,NULL);
		TAC *lend = createTACLabel(end);
		o1 = joinTAC(o1,lend);
	}
	return joinTAC(o0,o1);
}

TAC *createTACBoolean(AST *tree, char* labTrue, char* labFalse){
	switch(tree->type){
		case OPERATOR_LE:
			return createTACGreater(tree, labFalse, labTrue);

		case OPERATOR_GE:
			return createTACLess(tree, labFalse, labTrue);

		case OPERATOR_EQ:
			return createTACEqual(tree, labTrue, labFalse);

		case OPERATOR_NE:
			return createTACEqual(tree, labFalse, labTrue);

		case OPERATOR_AND:
			return createTACAnd(tree, labTrue, labFalse);

		case OPERATOR_OR:
			return createTACOr(tree, labTrue, labFalse);

		case '>':
			return createTACGreater(tree, labTrue, labFalse);

		case '<':
			return createTACLess(tree, labTrue, labFalse);

		case '!':
			return createTACBoolean(tree->son[0], labFalse, labTrue);
	}
}

TAC *createTACWhen(AST *tree){
	if (tree->son[1] != NULL){
		char *end = makeLabel();
		TAC *cond = createTACBoolean(tree->son[0], NULL, end);
		TAC *body = makeTAC(tree->son[1]);
		TAC *lab = createTACLabel(end);
		return joinTAC(joinTAC(cond,body),lab);
	}else return NULL;
}

TAC *createTACWhenElse(AST *tree){
	if (tree->son[2]==NULL){
		return createTACWhen(tree);
	}else{
		if(tree->son[1] == NULL){
			tree->son[1] = tree->son[2];
			tree->son[2] = NULL;
			tree->son[0] = create ('!', 0, tree->son[0], 0, 0, 0);
			return createTACWhen(tree);
		}else {
			char *els = makeLabel();
			char *end = makeLabel();
			TAC *cond = createTACBoolean(tree->son[0], NULL, els);
			TAC *body = makeTAC(tree->son[1]);
			TAC *jmp_end = createTAC(TAC_JMP, end, NULL, NULL);
			TAC *lab_els = createTACLabel(els);
			TAC *body_els = makeTAC(tree->son[2]);
			TAC *lab_end = createTACLabel(end);
			return joinTAC(joinTAC(joinTAC(joinTAC(joinTAC(cond,body),jmp_end),lab_els),body_els),lab_end);
		}	
	}
}

TAC *createTACWhile(AST *tree){
	if (tree->son[1] != NULL){
		char *begin = makeLabel();
		char *end = makeLabel();
		TAC *lbgn = createTACLabel(begin);
		TAC *cond = createTACBoolean(tree->son[0],NULL,end);
		TAC *body = makeTAC(tree->son[1]);
		TAC *j = createTAC(TAC_JMP, begin, NULL, NULL);
		TAC *lend = createTACLabel(end);
		return joinTAC(joinTAC(joinTAC(joinTAC(lbgn,cond),body),j),lend);
	}else 
		return NULL;
}

TAC *createTACFor(AST *tree){

	TAC *var = makeTAC(tree->son[0]);
	TAC *init = makeTAC(tree->son[1]);
	TAC *max = makeTAC(tree->son[2]);

	char *begin = makeLabel();
	char *end = makeLabel();
	TAC *lend = createTACLabel(end);
	TAC *lbgn = createTACLabel(begin);
	if (tree->son[3] == NULL){
		if(init->type == TAC_SYMBOL && (init->op_keys[0][0] == '\'' || ( init->op_keys[0][0] <='9' && init->op_keys[0][0] >= '0')) &&
		   max->type == TAC_SYMBOL && (max->op_keys[0][0] == '\'' || ( max->op_keys[0][0] <='9' && max->op_keys[0][0] >= '0'))){
			int x0, x1;
			if (init->op_keys[0][0] == '\'')
				x0 = init->op_keys[0][1];
			else
				x0 = atoi(init->op_keys[0]);
			if (max->op_keys[0][0] == '\'')
				x1 = max->op_keys[0][1];
			else
				x1 = atoi(max->op_keys[0]);

			if(x0 > x1){
				return createTAC(TAC_MOV, var->op_keys[0], init->op_keys[0], NULL);
			} else {
				return createTAC(TAC_MOV, var->op_keys[0], max->op_keys[0], NULL);
			}
		} else {
			TAC *cmp  = createTAC(TAC_CMP, init->op_keys[0], max->op_keys[0], NULL);
			TAC *jge = createTAC(TAC_JGE, begin, NULL, NULL);
			TAC *mov = createTAC(TAC_MOV, var->op_keys[0], init->op_keys[0], NULL);
			TAC *jmp = createTAC(TAC_JMP, end, NULL, NULL); 
			// entre -> lbgn
			TAC *movl = createTAC(TAC_MOV, var->op_keys[0], max->op_keys[0], NULL);
	
	 		return joinTAC(joinTAC(joinTAC(joinTAC(joinTAC(joinTAC(joinTAC(joinTAC(joinTAC(var,init), max), cmp), jge), mov), jmp), lbgn), movl), lend);
		}
	} else {
		TAC *mov = createTAC(TAC_MOV, var->op_keys[0], init->op_keys[0],NULL);
		TAC *check = createTAC(TAC_CMP, max->op_keys[0], var->op_keys[0], NULL);
		TAC *jend = createTAC(TAC_JGE, end, NULL, NULL);
		TAC *body = makeTAC(tree->son[3]);
		TAC *inc = createTAC(TAC_INC, var->op_keys[0], NULL, NULL);
		TAC *jbgn = createTAC(TAC_JMP, begin, NULL, NULL);

		return joinTAC(joinTAC(joinTAC(joinTAC(joinTAC(joinTAC(joinTAC(joinTAC(joinTAC(joinTAC(var,init),mov),max),lbgn),check),jend),body),inc),jbgn),lend);
	}
}

TAC *createTACArithmetic(AST *tree){
	TAC *op0 = makeTAC(tree->son[0]);
	TAC *op1 = makeTAC(tree->son[1]);
	

	if ( op0->type == TAC_SYMBOL && (op0->op_keys[0][0] == '\'' || ( op0->op_keys[0][0] <='9' && op0->op_keys[0][0] >= '0')) &&
	     op1->type == TAC_SYMBOL && (op1->op_keys[0][0] == '\'' || ( op1->op_keys[0][0] <='9' && op1->op_keys[0][0] >= '0'))){
		int x0, x1;
		if (op0->op_keys[0][0] == '\'')
			x0 = op0->op_keys[0][1];
		else
			x0 = atoi(op0->op_keys[0]);
		if (op1->op_keys[0][0] == '\'')
			x1 = op1->op_keys[0][1];
		else
			x1 = atoi(op1->op_keys[0]);
		int valor;
		switch(tree->type){
			case '+':	valor = x0 + x1;
					break;

			case '-':	valor = x0 - x1;
					break;

			case '*':	valor = x0 * x1;
					break;

			case '/':	valor = x0 / x1;
					break;
		}
		TAC *tac = createTAC (TAC_SYMBOL, NULL, NULL, NULL);
		tac->op_keys[0] = malloc (11*sizeof(char)); 
		sprintf (tac->op_keys[0],"%d", valor);
		ht_set(ht, tac->op_keys[0], tac->op_keys[0]);	
		return tac;

	}else{	
		int type;
		switch(tree->type){
			case '+':	type = TAC_ADD;
					break;

			case '-':	type = TAC_SUB;
					break;

			case '*':	type = TAC_MUL;
					break;

			case '/':	type = TAC_DIV;
					break;

		}

		char *res = makeTemp();
		TAC *tac = createTAC(type,res,op0->op_keys[0],op1->op_keys[0]);

		return joinTAC(joinTAC(op0,op1),tac);
	}
}

TAC *createTACVarAssign(AST *tree){
	TAC *op0 = makeTAC(tree->son[0]);
	TAC *op1 = makeTAC(tree->son[1]);
	TAC *mov = createTAC(TAC_MOV, op0->op_keys[0], op1->op_keys[0], NULL);
	return joinTAC(joinTAC(op0,op1),mov);
}

TAC *createTACVecAssign(AST *tree){
	TAC *op0 = makeTAC(tree->son[0]);
	TAC *op1 = makeTAC(tree->son[1]);
	TAC *op2 = makeTAC(tree->son[2]);
	TAC *vw = createTAC(TAC_VWRITE, op0->op_keys[0], op1->op_keys[0], op2->op_keys[0]);
	return joinTAC(joinTAC(joinTAC(op2,op1),op0),vw);
}

TAC *createTACVarDef(AST *tree){
	TAC *var = makeTAC(tree->son[0]);
	TAC *init = makeTAC(tree->son[2]);
	TAC *def = createTAC(TAC_VARDEF, var->op_keys[0], init->op_keys[0], NULL);
	return joinTAC(joinTAC(var,init),def);
}

TAC *createTACVecDef(AST *tree){
	TAC *vec = makeTAC(tree->son[0]);
	TAC *size = makeTAC(tree->son[2]);
	TAC *t0 = NULL;

	AST *aux;
	for(aux = tree->son[3]; aux != NULL && aux->type == ' '; aux = aux->son[1]){
		t0 = joinTAC(t0,makeTAC(aux->son[0]));
	}
	if(aux != NULL){
		t0 = joinTAC(t0,makeTAC(aux));
	}

	return joinTAC(t0,createTAC(TAC_VECDEF,vec->op_keys[0],size->op_keys[0], NULL));
}

TAC *createTACVecRead(AST *tree){
	TAC *op0 = makeTAC(tree->son[0]);
	TAC *op1 = makeTAC(tree->son[1]);
	char *res = makeTemp();
	TAC *r = createTAC(TAC_VREAD, res, op0->op_keys[0], op1->op_keys[0]);
	return joinTAC(joinTAC(op0,op1),r);
}

TAC *createTACFunDef(AST *tree){
	TAC *fun = makeTAC(tree->son[1]);

	AST *aux = tree->son[2];
	TAC *t = NULL;

	int i = 1;
	while(aux != NULL && aux->type == ','){
		t = joinTAC(t,createTAC(TAC_SYMBOL,aux->son[0]->son[1]->hash_key,NULL,NULL));
		entry_t *e = ht_get(ht, aux->son[0]->son[1]->hash_key);
		e->nature = NAT_PAR;
		e->params = i;
		i++;

		aux = aux->son[1];
	}
	if (aux != NULL){
		t = joinTAC(t,createTAC(TAC_SYMBOL,aux->son[1]->hash_key,NULL,NULL));
		entry_t *e = ht_get(ht, aux->son[1]->hash_key);
		e->nature = NAT_PAR;
		e->params = i;
	}

	TAC *begin = createTAC(TAC_FBEGIN, fun->op_keys[0], NULL, NULL);

	TAC *body = makeTAC(tree->son[3]);
	TAC *end = createTAC(TAC_FEND, fun->op_keys[0], NULL, NULL);
	return joinTAC(joinTAC(joinTAC(t,begin),body),end);
}

TAC *createTACFunCall(AST *tree){
	TAC *fun = makeTAC(tree->son[0]);

	AST *aux = tree->son[1];
	TAC *t0 = NULL;
	TAC *t1 = NULL;

	struct s_parlist *par = ht_get(ht, fun->op_keys[0])->parlist;
	while(aux != NULL && aux->type == ','){
		t0 = joinTAC(t0,makeTAC(aux->son[0]));
		t0 = joinTAC(t0,createTAC(TAC_ARG, par->param, t0->op_keys[0], NULL));
		aux = aux->son[1];
		par = par->next;
	}
	if(aux != NULL){
		t0 = joinTAC(t0,makeTAC(aux));
		t0 = joinTAC(t0,createTAC(TAC_ARG, par->param, t0->op_keys[0], NULL));
	}

	char *res = makeTemp();
	TAC *cal = createTAC(TAC_CALL, res, fun->op_keys[0], NULL);
	return joinTAC(joinTAC(t0,t1),cal);
}

TAC *createTACRead(AST *tree){
	TAC *op = makeTAC(tree->son[0]);
	TAC *r = createTAC(TAC_READ, op->op_keys[0], NULL, NULL);
	return joinTAC(op,r);
}

TAC *createTACReturn(AST *tree){
	TAC *op = makeTAC(tree->son[0]);
	TAC *r = createTAC(TAC_RET, op->op_keys[0], NULL, NULL);
	return joinTAC(op,r);
}

TAC *createTACPrint(AST *tree){
	AST *aux = tree->son[0];
	TAC *t0 = NULL;
	TAC *t1 = NULL;

	while(aux != NULL && aux->type == ' '){
		t0 = joinTAC(t0,makeTAC(aux->son[0]));
		t0 = joinTAC(t0,createTAC(TAC_PRINT, t0->op_keys[0], NULL, NULL));
		aux = aux->son[1];
	}
	t0 = joinTAC(t0,makeTAC(aux));
	t0 = joinTAC(t0,createTAC(TAC_PRINT, t0->op_keys[0], NULL, NULL));

	return joinTAC(t0,t1);
}

TAC *makeTAC(AST *tree){
	if (tree != NULL){
		switch (tree->type){
			case KW_READ:
					return createTACRead(tree);

			case KW_PRINT:
					return createTACPrint(tree);

			case KW_RETURN:
					return createTACReturn(tree);

			case KW_WHEN:
					return createTACWhen(tree);

			case KW_ELSE:
					return createTACWhenElse(tree);

			case KW_WHILE:
					return createTACWhile(tree);

			case KW_FOR:
					return createTACFor(tree);

			/** NOT USED **
			case KW_BYTE:
			case KW_SHORT:
			case KW_LONG:
			case KW_FLOAT:
			case KW_DOUBLE:
			**************/

			case TK_IDENTIFIER:
			case LIT_INTEGER:
			case LIT_REAL:
			case LIT_CHAR:
			case LIT_STRING:
					return createTAC(TAC_SYMBOL, tree->hash_key, NULL, NULL);

			case ':':
					return createTACVarDef(tree);

			case VDEF:
					return createTACVecDef(tree);

			case FDEF:
					return createTACFunDef(tree);

			case FCALL:
					return createTACFunCall(tree);

			//case FPAR: //not used

			case '[':
					return createTACVecRead(tree);

			case '=':
					return createTACVarAssign(tree);

			case '#':
					return createTACVecAssign(tree);

			case ';':
					return joinTAC(makeTAC(tree->son[0]),makeTAC(tree->son[1]));

			case '+':
			case '-':
			case '*':
			case '/':
					return createTACArithmetic(tree);

			case '(':
			case '{':
					return makeTAC(tree->son[0]);

			default:	return joinTAC(joinTAC(joinTAC(makeTAC(tree->son[0]),makeTAC(tree->son[1])),makeTAC(tree->son[2])),makeTAC(tree->son[3]));

		}
	}
	return NULL;
}
