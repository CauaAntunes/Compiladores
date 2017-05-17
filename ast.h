typedef struct s_AST{
	int type;
	char* hash_key;
	struct s_AST* son[4];		
} AST;

AST *ASTree;

AST* create(int type, char* key, AST* son0, AST* son1, AST* son2, AST* son3);

void astPrint(AST *tree, int level);
