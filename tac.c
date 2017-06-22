#define	TAC_SYMBOL	0
#define	TAC_LABEL	1
#define	TAC_ADD		2
#define	TAC_SUB		3
#define	TAC_MUL		4
#define	TAC_DIV		5
#define	TAC_GT		6
#define	TAC_LT		7
#define	TAC_GE		8
#define	TAC_LE		9
#define	TAC_EQ		10
#define	TAC_NE		11
#define	TAC_NOT		12
#define	TAC_JMP		13
#define	TAC_JZ		14
#define	TAC_JNZ		15
#define	TAC_MOV		16
#define	TAC_CALL	17
#define	TAC_RET		18
#define	TAC_FBEGIN	19
#define	TAC_FEND	20

typedef struct s_TAC{
	int type;
	char* op_keys[3];
	struct s_TAC *prev;
	struct s_TAC *next;
} TAC;

int label = 0, temp = 0;

TAC *createTAC(int type, char* op0, char* op1, char* op2){
	TAC t = (TAC*) malloc(sizeof(TAC));
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
	for(tac = first(tac); tac != NULL; tac = tac->next){
		switch(tac->type){
			case TAC_SYMBOL:
				printf("TAC_SYMBOL"); break;

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

			case TAC_JN:
				printf("TAC_JN"); break;

			case TAC_MOV:
				printf("TAC_MOV"); break;

			case TAC_CALL:
				printf("TAC_CALL"); break;

			case TAC_RET:
				printf("TAC_RET"); break;

			case TAC_FBEGIN:
				printf("TAC_FBEGIN"); break;

			case TAC_FEND:
				printf("TAC_FEND"); break;
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
	char lab[12];
	sprintf(lab,"$label%d",label);
	ht_set(ht,lab,lab);
	label++;
	return lab;
}

char *makeTemp(){
	char lab[11];
	sprintf(lab,"$temp%d",temp);
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

TAC *createTACWhen(AST *tree){
	char *end = makeLabel();
	TAC *cond = makeTAC(tree->son[0]);
	TAC *jmp = createTAC(TAC_JZ, end, cond->op_keys[0], NULL);
	TAC *body = makeTAC(tree->son[1]);
	TAC *lab = createTACLabel(end);
	return joinTAC(joinTAC(joinTAC(cond,jmp),body),lab);
}

TAC *createTACWhenElse(AST *tree){
	char *els = makeLabel();
	char *end = makeLabel();
	TAC *cond = makeTAC(tree->son[0]);
	TAC *jmp_els = createTAC(TAC_JZ, els, cond->op_keys[0], NULL);
	TAC *body = makeTAC(tree->son[1]);
	TAC *jmp_end = createTAC(TAC_JMP, end, NULL, NULL);
	TAC *lab_els = createTACLabel(els);
	TAC *body_els = makeTAC(tree->son[2]);
	TAC *lab_end = createTACLabel(end);
	return joinTAC(joinTAC(joinTAC(joinTAC(joinTAC(joinTAC(cond,jmp_els),body),jmp_end),lab_els),body_els),lab_end);
}

TAC *createTACWhile(AST *tree){
	char *begin = makeLabel();
	char *end = makeLabel();
	TAC *lbgn = createTACLabel(begin);
	TAC *cond = makeTAC(tree->son[0]);
	TAC *j0 = createTAC(TAC_JZ, end, cond->op_keys[0], NULL);
	TAC *body = makeTAC(tree->son[1]);
	TAC *j1 = createTAC(TAC_JMP, begin);
	TAC *lend = createTACLabel(end);
	return joinTAC(joinTAC(joinTAC(joinTAC(joinTAC(lbgn,cond),j0),body),j1),lend);
}

TAC *createTACFor(AST *tree){
	char *begin = makeLabel();
	char *end = makeLabel();

	TAC *var = makeTAC(tree->son[0]);
	TAC *init = makeTAC(tree->son[1]);
	TAC *mov = createTAC(TAC_MOV, var->op_keys[0], init->op_keys[0],NULL);

	TAC *max = makeTAC(tree->son[2]);

	TAC *lbgn = createTACLabel(begin);
	char *aux = makeTemp();
	TAC *check = createTAC(TAC_EQ, aux, max->op_keys[0], var->op_keys[0]);
	TAC *jend = createTAC(TAC_JNZ, end, check->op_keys[0], NULL);
	TAC *body = makeTAC(tree->son[3]);
	TAC *inc = createTAC(TAC_ADD, var->op_keys[0], var->op_keys[0], "$1");
	TAC *jbgn = createTAC(TAC_JMP, begin, NULL, NULL);
	TAC *lend = createTACLabel(end);

	return joinTAC(joinTAC(joinTAC(joinTAC(joinTAC(joinTAC(joinTAC(joinTAC(joinTAC(joinTAC(var,init),mov),max),lbgn),check),jend),body),inc),jbgn),lend);
}

TAC *createTACOperation(AST *tree){
	TAC *op0 = makeTAC(tree->son[0]);
	TAC *op1 = makeTAC(tree->son[1]);

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

		case '>':	type = TAC_GT;
				break;

		case '<':	type = TAC_LT;
				break;

		case OPERATOR_LE:
				type = TAC_LE;
				break;

		case OPERATOR_GE:
				type = TAC_GE;
				break;

		case OPERATOR_EQ:
				type = TAC_EQ;
				break;

		case OPERATOR_NE:
				type = TAC_NE;
				break;

		case OPERATOR_AND:
				type = TAC_AND;
				break;

		case OPERATOR_OR:
				type = TAC_OR;
				break;

	}

	char *res = makeTemp();
	TAC *tac = createTAC(type,res,op0->op_keys[0],op1->op_keys[0]);

	return joinTAC(joinTAC(op0,op1),tac);
}

TAC *createTACNot(tree){
	TAC *op = makeTAC(tree->son[0]);
	TAC *not = createTAC(TAC_NOT, op->op_keys[0], NULL, NULL);
	return joinTAC(op,not);
}

TAC *createTACAssign(AST *tree){
	TAC *op0 = makeTAC(tree->son[0]);
	TAC *op1 = makeTAC(tree->son[1]);
	TAC *mov = createTAC(TAC_MOV, op0->op_keys[0], op1->op_keys[0], NULL);
	return joinTAC(joinTAC(op0,op1),mov);
}

TAC *createTACVarDef(AST *tree){
	TAC *var = makeTAC(tree->son[0]);
	TAC *init = makeTAC(tree->son[2]);
	TAC *mov = createTAC(TAC_MOV, var->op_keys[0], init->op_keys[0], NULL);
	return joinTAC(joinTAC(var,init),mov);
}

TAC *createTACFunDef(AST *tree){
	TAC *fun = makeTAC(tree->son[1]);
	char *lab = makeLabel();

	AST *aux = tree->son[2];
	TAC *t = fun;

	while(aux != NULL && aux->type == ','){
		t = joinTAC(t,makeTAC(aux->son[0]));
		aux = aux->son[1];
	}
	t = joinTAC(t,makeTAC(aux));

	TAC *lbgn = createTACLabel(lab);

	ht_get(ht,fun->op_keys[0])->label = lbgn;

	TAC *body = makeTAC(tree->son[3]);
	TAC *ret = createTAC(TAC_RET, NULL, NULL, NULL);
	return joinTAC(joinTAC(joinTAC(t,lbgn),body),ret);
}

TAC *createTACFunCall(AST *tree){
	TAC *fun = makeTAC(tree->son[1]);
	char *lab = makeLabel();

	struct s_parlist p = ht_get(ht,fun->op_keys[0])->parlist;
	AST *aux = tree->son[2];
	TAC *t = NULL;

	while(aux != NULL && aux->type == ','){
		t = joinTAC(t,makeTAC(aux->son[0]));
		t = joinTAC(t,createTAC(TAC_MOV, p->param, t->op_keys[0], NULL);
		aux = aux->son[1];
		p = p->next;
	}
	t = joinTAC(t,makeTAC(aux));
	t = joinTAC(t,createTAC(TAC_MOV, p->param, t->op_keys[0], NULL);

	TAC *cal = createTAC(TAC_CALL, res, fun->op_keys[0], NULL);
	return joinTAC(t,cal);
}

TAC *makeTAC(AST *tree){
	if (tree != NULL){
		switch (tree->type){
			case KW_READ:	
					break;

			case KW_PRINT:	
					break;

			case KW_RETURN:
					break;

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
					break;

			case FDEF:
					return createTACFunDef(tree);

			case FCALL:
					return createTACFunCall(tree);

			case FPAR:
					break;

			case '[':
					break;

			case '=':
					return createTACAssign(tree);

			case '#':
					break;

			case ';':
					return joinTAC(makeTAC(tree->son[0]),makeTAC(tree->son[1]));

			case OPERATOR_LE:
			case OPERATOR_GE:
			case OPERATOR_EQ:
			case OPERATOR_NE:
			case OPERATOR_AND:
			case OPERATOR_OR:
			case '>':
			case '<':
			case '+':
			case '-':
			case '*':
			case '/':
					return createTACOperation(tree);

			case '!':
					return createTACNot(tree);

			case '(':
			case '{':
					return makeTAC(tree->son[0]);

		}
	}
}
