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
	aux->prev = begin;
	begin->next = aux;
	return end;
}

TAC *createTACWhen(AST *tree){
	char *end = makeLabel();
	TAC *cond = makeTAC(tree->son[0]);
	TAC *jmp = createTAC(TAC_JNZ, end, cond->op[0], NULL);
	TAC *body = makeTAC(tree->son[1]);
	TAC *lab = createTAC(TAC_LABEL, end, NULL, NULL);
	return joinTAC(joinTAC(joinTAC(cond,jmp),body),lab);
}

TAC *createTACWhenElse(AST *tree){
	char *els = makeLabel();
	char *end = makeLabel();
	TAC *cond = makeTAC(tree->son[0]);
	TAC *jmp_els = createTAC(TAC_JNZ, els, cond->op[0], NULL);
	TAC *body = makeTAC(tree->son[1]);
	TAC *jmp_end = createTAC(TAC_JMP, end, cond->op[0], NULL);
	TAC *lab_els = createTAC(TAC_LABEL, els, NULL, NULL);
	TAC *body_els = makeTAC(tree->son[2]);
	TAC *lab_end = createTAC(TAC_LABEL, end, NULL, NULL);
	return joinTAC(joinTAC(joinTAC(joinTAC(joinTAC(joinTAC(cond,jmp_els),body),jmp_end),lab_els),body_els),lab_end);
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
					break;

			case KW_ELSE:
					break;

			case KW_WHILE:
					break;

			case KW_FOR:
					break;

			case KW_BYTE:
					break;

			case KW_SHORT:
					break;

			case KW_LONG:
					break;

			case KW_FLOAT:
					break;

			case KW_DOUBLE:
					break;

			case TK_IDENTIFIER:
			case LIT_INTEGER:
			case LIT_REAL:
			case LIT_CHAR:
			case LIT_STRING:
					return createTAC(TAC_SYMBOL, tree->hash_key, NULL, NULL);

			case ':':
					print(f, tree->son[0]);
					fprintf(f," : ");
					print(f, tree->son[1]);
					fprintf(f," ");
					print(f, tree->son[2]);
					break;

			case VDEF:
					print(f, tree->son[0]);
					fprintf(f," : ");
					print(f, tree->son[1]);
					fprintf(f,"[");
					print(f, tree->son[2]);
					fprintf(f,"]");
					if(tree->son != NULL){
						fprintf(f," ");
						print(f, tree->son[3]);
					}
					break;

			case FDEF:
					print(f, tree->son[0]);
					fprintf(f," ");
					print(f, tree->son[1]);
					fprintf(f,"(");
					print(f, tree->son[2]);
					fprintf(f,") ");
					print(f, tree->son[3]);
					break;

			case FPAR:
					print(f, tree->son[0]);
					fprintf(f," ");
					print(f, tree->son[1]);
					break;

			case FCALL:
					print(f, tree->son[0]);
					fprintf(f,"(");
					print(f, tree->son[1]);
					fprintf(f,")");
					break;

			case '[':
					print(f, tree->son[0]);
					fprintf(f,"[");
					print(f, tree->son[1]);
					fprintf(f,"]");
					break;

			case '=':
					print(f, tree->son[0]);
					fprintf(f," = ");
					print(f, tree->son[1]);
					break;

			case '#':
					print(f, tree->son[0]);
					fprintf(f,"#");
					print(f, tree->son[1]);
					break;

			case ';':
					print(f, tree->son[0]);
					fprintf(f, ";\n");
					print(f, tree->son[1]);
					break;

			case ',':
					print(f, tree->son[0]);
					fprintf(f, ", ");
					print(f, tree->son[1]);
					break;

			case ' ':
					print(f, tree->son[0]);
					if(tree->son[1] != NULL){
						fprintf(f, " ");
						print(f, tree->son[1]);
					}
					break;

			case OPERATOR_LE:
					print(f, tree->son[0]);
					fprintf(f, " <= ");
					print(f, tree->son[1]);
					break;

			case OPERATOR_GE:
					print(f, tree->son[0]);
					fprintf(f, " >= ");
					print(f, tree->son[1]);
					break;


			case OPERATOR_EQ:
					print(f, tree->son[0]);
					fprintf(f, " == ");
					print(f, tree->son[1]);
					break;

			case OPERATOR_NE:
					print(f, tree->son[0]);
					fprintf(f, " != ");
					print(f, tree->son[1]);
					break;


			case OPERATOR_AND:
					print(f, tree->son[0]);
					fprintf(f, " && ");
					print(f, tree->son[1]);
					break;

			case OPERATOR_OR:
					print(f, tree->son[0]);
					fprintf(f, " || ");
					print(f, tree->son[1]);
					break;

			case '>':
					print(f, tree->son[0]);
					fprintf(f, " > ");
					print(f, tree->son[1]);
					break;

			case '<':
					print(f, tree->son[0]);
					fprintf(f, " < ");
					print(f, tree->son[1]);
					break;

			case '+':
					print(f, tree->son[0]);
					fprintf(f, " + ");
					print(f, tree->son[1]);
					break;

			case '-':
					print(f, tree->son[0]);
					fprintf(f, " - ");
					print(f, tree->son[1]);
					break;

			case '*':
					print(f, tree->son[0]);
					fprintf(f, " * ");
					print(f, tree->son[1]);
					break;

			case '/':
					print(f, tree->son[0]);
					fprintf(f, " / ");
					print(f, tree->son[1]);
					break;

			case '!':
					fprintf(f, "! ");
					print(f, tree->son[0]);
					break;

			case '(':
					fprintf(f, "(");
					print(f, tree->son[0]);
					fprintf(f, ")");
					break;

			case '{':
					fprintf(f, "{\n");
					print(f, tree->son[0]);
					fprintf(f, "}");
					break;

		}
	}
}
