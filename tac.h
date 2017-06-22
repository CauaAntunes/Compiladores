
typedef struct s_TAC{
	int type;
	char* op_keys[3];
	struct s_TAC *prev;
	struct s_TAC *next;
} TAC;
