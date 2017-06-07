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

int count(int s_type, AST *tree){
	if(tree != NULL){
		int r = 1;
		while(tree->type == s_type){
			r++;
			tree = tree->son[1];
		}
		return r;
	} else return 0;
}

int semantic(AST *tree)
{
	if (tree != NULL){
		int aux, aux0, aux1, aux2;
		entry_t *entry;
		switch (tree->type){
			case KW_READ:
					semantic(tree->son[0]);
					return COMMAND;

			case KW_PRINT:
					semantic(tree->son[0]);
					return COMMAND;

			case KW_RETURN:
					aux = semantic(tree->son[0]);
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
					aux1 = semantic(tree->son[1]);
					if(aux1 == TYPE_INT || aux1 == TYPE_REAL){
						aux2 = semantic(tree->son[2]);
						if(aux2 == TYPE_INT || aux2 == TYPE_REAL)
							if(tree->son[1] == NULL || semantic(tree->son[1]) == COMMAND)
								return COMMAND;
					}
					exit(4);

			/***** not needed *****
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
			**********************/

			case TK_IDENTIFIER:
					entry = ht_get(ht,tree->hash_key);
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
					entry = ht_get(ht, tree->son[0]->hash_key);
					if(entry->declared)
						exit(4);

					entry->declared = 1;
					entry->nature = NAT_VAR;

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

					return COMMAND;

			case VDEF:
					entry = ht_get(ht, tree->son[0]->hash_key);
					if(entry->declared)
						exit(4);

					entry->declared = 1;
					entry->nature = NAT_VEC;

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

					int vlen = atoi(ht_get(ht, tree->son[2]->hash_key)->value);
					if(vlen != count(' ', tree->son[3]))
						exit(4);

					return COMMAND;

			case FDEF:
					entry = ht_get(ht, tree->son[1]->hash_key);
					if(entry->declared)
						exit(4);

					entry->declared = 1;
					entry->nature = NAT_FUN;

					switch(tree->son[0]->type){
						case KW_BYTE:
						case KW_SHORT:
						case KW_LONG:
							entry->data_type = TYPE_INT;
						case KW_FLOAT:
						case KW_DOUBLE:
							entry->data_type = TYPE_REAL;
						default: exit(4);
					}

					semantic(tree->son[2]);
					entry->params = count(',',tree->son[2]);

					if(tree->son[3]!= NULL && semantic(tree->son[3]) != COMMAND)
						exit(4);

					// Se funções puderem ter parâmetros com os mesmos nomes,
					// temos que marcar eles como "não declarados" após analisada a função
					return COMMAND;

			case FPAR:
					entry = ht_get(ht, tree->son[1]->hash_key);
					if(entry->declared)
						exit(4);

					entry->declared = 1;
					entry->nature = NAT_VAR;

					switch(tree->son[0]->type){
						case KW_BYTE:
						case KW_SHORT:
						case KW_LONG:
							entry->data_type = TYPE_INT;
						case KW_FLOAT:
						case KW_DOUBLE:
							entry->data_type = TYPE_REAL;
						default: exit(4);
					}

					return entry->data_type;

			case FCALL:
					entry = ht_get(ht,tree->son[0]->hash_key);
					if(entry->nature != NAT_FUN || !entry->declared)
						exit(4);

					semantic(tree->son[1]);
					if(entry->params != count(',',tree->son[1]))
						exit(4);

					return entry->data_type;

			case '[':
					entry = ht_get(ht,tree->son[0]->hash_key);
					if(entry->nature != NAT_VEC || !entry->declared)
						exit(4);

					if(semantic(tree->son[1]) != TYPE_INT)
						exit(4);

					return entry->data_type;

			case '=':
					semantic(tree->son[0]);
					aux = semantic(tree->son[1]);
					if(aux != TYPE_INT && aux != TYPE_REAL)
						exit(4);
					return COMMAND;

			case '#':
					entry = ht_get(ht,tree->son[0]->hash_key);
					if(entry->nature != NAT_VEC || !entry->declared)
						exit(4);

					if(semantic(tree->son[1]) != TYPE_INT)
						exit(4);

					return entry->data_type;

			case ';':
					if((tree->son[0] == NULL || semantic(tree->son[0]) == COMMAND) &&
					   (tree->son[1] == NULL || semantic(tree->son[1]) == COMMAND))
						return COMMAND;
					else exit(4);

			case ',':
					aux = semantic(tree->son[0]);
					if(aux != TYPE_INT && aux != TYPE_REAL)
						exit(4);

					aux = semantic(tree->son[1]);
					if(aux != TYPE_INT && aux != TYPE_REAL)
						exit(4);

					return aux;

			case ' ':
					semantic(tree->son[0]);
					semantic(tree->son[1]);
					return COMMAND; // Not sure o que retornar aqui

			case OPERATOR_LE:
			case OPERATOR_GE:
			case OPERATOR_EQ:
			case OPERATOR_NE:
			case '>':
			case '<':
					aux = semantic(tree->son[0]);
					if(aux != TYPE_INT && aux != TYPE_REAL)
						exit(4);

					aux = semantic(tree->son[1]);
					if(aux != TYPE_INT && aux != TYPE_REAL)
						exit(4);

					return TYPE_BOOL;

			case OPERATOR_AND:
			case OPERATOR_OR:
					if(semantic(tree->son[0]) != TYPE_BOOL || semantic(tree->son[1]) != TYPE_BOOL)
						exit(4);
					else return TYPE_BOOL;

			case '+':
			case '-':
			case '*':
			case '/':
					aux0 = semantic(tree->son[0]);
					if(aux0 != TYPE_INT && aux0 != TYPE_REAL)
						exit(4);

					aux1 = semantic(tree->son[1]);
					if(aux1 == TYPE_INT){
						return aux0;
					} else if (aux0 == TYPE_REAL)
						return TYPE_REAL;
					else exit(4);

			case '!':
					if(semantic(tree->son[0]) != TYPE_BOOL)
						exit(4);
					else return TYPE_BOOL;

			case '(':
					return semantic(tree->son[0]);

			case '{':
					if(semantic(tree->son[0]) != COMMAND)
						exit(4);
					else return COMMAND;

		}
	}
}
