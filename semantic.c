#define	TYPE_INT	0
#define	TYPE_REAL	1
#define	TYPE_BOOL	2
#define	TYPE_STR	3
#define COMMAND		4

#define	NAT_VAR	0
#define	NAT_VEC	1
#define	NAT_FUN	2

int nature(AST *tree){
	if(tree == NULL)
		return -1;
	if(tree->type != TK_IDENTIFIER)
		return -1;
	return ht_get(ht,tree->hash_key)->nature;
}

int semantic(AST *tree)
{
	if (tree != NULL){
		switch (tree->type){
			case KW_READ:
					semantic(tree->son[0]);
					return COMMAND;

			case KW_PRINT:
					semantic(tree->son[0]);
					return COMMAND;

			case KW_RETURN:
					int aux = semantic(tree->son[0]);
					if(aux == TYPE_INT || aux == TYPE_REAL)
						return COMMAND;
					else exit(4);

			case KW_WHEN:
					if(semantic(tree->son[0]) == TYPE_BOOL &&
					   (tree->son[1] == NULL || semantic(tree->son[1]) == COMMAND))
							return COMMAND;
					exit(4);

			case KW_ELSE:
					if(semantic(tree->son[0]) == TYPE_BOOL &&
					   (tree->son[1] == NULL || semantic(tree->son[1]) == COMMAND) &&
					   (tree->son[2] == NULL || semantic(tree->son[2]) == COMMAND))
						return COMMAND;
					else exit(4);

			case KW_WHILE:
					if(semantic(tree->son[0]) == TYPE_BOOL &&
					   (tree->son[1] == NULL || semantic(tree->son[1]) == COMMAND))
							return COMMAND;
					exit(4);

			case KW_FOR:	
					semantic(tree->son[0]);
					int aux1 = semantic(tree->son[1]);
					if(aux1 == TYPE_INT || aux1 == TYPE_REAL){
						int aux2 = semantic(tree->son[2]);
						if(aux2 == TYPE_INT || aux2 == TYPE_REAL)
							if(tree->son[1] == NULL || semantic(tree->son[1]) == COMMAND)
								return COMMAND;
					}
					exit(4);

			/***** not used *****
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
			*********************/

			case TK_IDENTIFIER:
					entry_t *entry = ht_get(ht,tree->hash_key);
					if(entry->nature != NAT_VAR || !entry->declared)
						exit(4);
					return entry->data_type;

			case LIT_INTEGER:
					return TYPE_INT;

			case LIT_REAL:
					return TYPE_REAL;

			case LIT_CHAR:
					return TYPE_INT;

			case LIT_STRING:
					return TYPE_STR;

			case ':':
					if(nature(tree->son[0]) != NAT_VAR)
						exit(4);

					entry_t *entry = ht_get(ht, tree->son[0]->hash_key);
					if(entry->declared)
						exit(4);
					entry->declared = true;

					switch(tree->son[1]->type){
						case KW_BYTE:
						case KW_SHORT:
						case KW_LONG:
							entry->data_type = TYPE_INT;
						case KW_FLOAT:
						case KW_DOUBLE:
							entry->data_type = TYPE_REAL;
						default: exit(4);
					}

					int aux = semantic(tree->son[2]);
					if(aux != TYPE_INT && aux != TYPE_REAL)
						exit(4);
					return COMMAND;
			case VDEF:
					if(nature(tree->son[0]) != NAT_VEC)
						exit(4);

					entry_t *entry = ht_get(ht, tree->son[0]->hash_key);
					if(entry->declared)
						exit(4);
					entry->declared = true;

					switch(tree->son[1]->type){
						case KW_BYTE:
						case KW_SHORT:
						case KW_LONG:
							entry->data_type = TYPE_INT;
						case KW_FLOAT:
						case KW_DOUBLE:
							entry->data_type = TYPE_REAL;
						default: exit(4);
					} // TO DO
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
