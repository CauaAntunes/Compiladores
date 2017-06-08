#define	TYPE_INT	0
#define	TYPE_REAL	1
#define	TYPE_BOOL	2
#define	TYPE_STR	3
#define COMMAND		4

#define	NAT_VAR	0
#define	NAT_VEC	1
#define	NAT_FUN	2

int count(int s_type, AST *tree){
	if(tree != NULL){
		int r = 0;
		while(tree != NULL && tree->type == s_type){
			r++;
			tree = tree->son[1];
		}
		return r;
	} else return 0;
}

typedef struct s_tree_list{
	struct s_tree_list *next;
	AST *f_params;
	AST *f_body;
} tree_list;

void clear_params(AST *aux){
	while(aux != NULL && aux->type == ','){
		if(aux->son[0] != NULL && aux->son[0]->type == FPAR){
			AST *aux0 = aux->son[0]->son[1];
			if(aux0 != NULL){
				entry_t *son0 = ht_get(ht,aux0->hash_key);
				if(son0 != NULL)
					son0->declared = 0;
			}
		}
		if(aux->son[1] != NULL && aux->son[1]->type == FPAR){
			AST *aux0 = aux->son[1]->son[1];
			if(aux0 != NULL){
				entry_t *son1 = ht_get(ht,aux0->hash_key);
				if(son1 != NULL)
					son1->declared = 0;
			}
		}
		aux = aux->son[1];
	}
}

int checkDeclarations(AST *tree){
	tree_list *f_list = NULL;
	AST *next;

	while(tree != NULL && tree->type == ';'){
		int i;
		for(i = 0; i <= 1; i++)
			if(tree->son[i] != NULL && tree->son[i]->type != ';'){
				next = tree->son[i];
				if (next != NULL){
					entry_t *entry;
					switch (next->type){
						case ':':
							entry = ht_get(ht, next->son[0]->hash_key);
							if(entry->declared)
								exit(4);

							entry->declared = 1;
							entry->nature = NAT_VAR;
							switch(next->son[1]->type){
								case KW_BYTE:
								case KW_SHORT:
								case KW_LONG:
									entry->data_type = TYPE_INT;
									break;
								case KW_FLOAT:
								case KW_DOUBLE:
									entry->data_type = TYPE_REAL;
									break;
								default: exit(4);
							}
							break;

						case VDEF:
							entry = ht_get(ht, next->son[0]->hash_key);
							if(entry->declared)
								exit(4);

							entry->declared = 1;
							entry->nature = NAT_VEC;

							switch(next->son[1]->type){
								case KW_BYTE:
								case KW_SHORT:
								case KW_LONG:
									entry->data_type = TYPE_INT;
									break;
								case KW_FLOAT:
								case KW_DOUBLE:
									entry->data_type = TYPE_REAL;
									break;
								default: exit(4);
							}

							int vlen = atoi(ht_get(ht, next->son[2]->hash_key)->value);

							if(next->son[3] != NULL && vlen != count(' ', next->son[3]))
								exit(4);
							break;

						case FDEF:
							entry = ht_get(ht, next->son[1]->hash_key);
							if(entry->declared)
								exit(4);

							entry->declared = 1;
							entry->nature = NAT_FUN;
							switch(next->son[0]->type){
								case KW_BYTE:
								case KW_SHORT:
								case KW_LONG:
									entry->data_type = TYPE_INT;
									break;
								case KW_FLOAT:
								case KW_DOUBLE:
									entry->data_type = TYPE_REAL;
									break;
								default: exit(4);
							}

							entry->params = count(',',next->son[2]);

							tree_list *n = malloc(sizeof(tree_list));
							n->f_params = next->son[2];
							n->f_body = next->son[3];
							n->next = f_list;
							f_list = n;
							break;
						default: exit(4);
					}
				}
		}
		tree = tree->son[1];
	}

	while(f_list != NULL){
		semantic(f_list->f_params);
		if(f_list->f_body != NULL && semantic(f_list->f_body) != COMMAND)
			exit(4);
		clear_params(f_list->f_params);
		tree_list *tl = f_list->next;
		free(f_list);
		f_list = tl;
	}
	return 0;
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
							if(tree->son[3] == NULL || semantic(tree->son[3]) == COMMAND)
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
							break;
						case KW_FLOAT:
						case KW_DOUBLE:
							entry->data_type = TYPE_REAL;
							break;
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
					return COMMAND;

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
					return TYPE_BOOL;

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
					if(tree->son[0] != NULL && semantic(tree->son[0]) != COMMAND)
						exit(4);
					else return COMMAND;

		}
	}
}