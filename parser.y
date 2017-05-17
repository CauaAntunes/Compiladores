%{

typedef struct s_AST{
	int type;
	char* hash_key;
	s_AST* son[4];		
} AST;

AST* create(int type, char* key, AST* son0, AST* son2, AST* son1, AST* son3);{
	AST *tree = (AST*) calloc(1, sizeof(AST));		
	tree->type = type;
	tree->key = key;
	tree->son[0] = son0;
	tree->son[1] = son1;
	tree->son[2] = son2;
	tree->son[3] = son3;
	return tree;
}

void astPrint(AST *tree, int level )
{
	int i;
	if (tree == NULL)
		return;
	for(i=0; i<level; i++)
		fprintf("	");
        //astPrint(tree->son[i]);
	printf("%d\n", tree->type); 
	for(i=0; i<3; i++)
		astPrint(tree->son[i], level+1);	
}

%}

%union{ char* symbol; }

%token KW_BYTE
%token KW_SHORT
%token KW_LONG
%token KW_FLOAT
%token KW_DOUBLE
%token KW_WHEN
%token KW_THEN
%token KW_ELSE
%token KW_WHILE
%token KW_FOR
%token KW_TO
%token KW_READ
%token KW_RETURN
%token KW_PRINT

%token OPERATOR_LE 
%token OPERATOR_GE
%token OPERATOR_EQ
%token OPERATOR_NE
%token OPERATOR_AND
%token OPERATOR_OR

%token <symbol> TK_IDENTIFIER
%token <symbol> LIT_INTEGER
%token <symbol> LIT_REAL
%token <symbol> LIT_CHAR
%token <symbol> LIT_STRING

%token TOKEN_ERROR

%left '-' '+'
%left '*' '/'

%%

program		: def ';' program
		| def ';'
		;
def		: var
		| func
		;
var		: TK_IDENTIFIER ':' type litinit
		| TK_IDENTIFIER ':' type '[' LIT_INTEGER ']' vec
		;
vec		: litinit vec
		|
		;
litinit		: LIT_INTEGER
		| LIT_REAL
		| LIT_CHAR
		;
type		: KW_BYTE
		| KW_SHORT
		| KW_LONG
		| KW_FLOAT
		| KW_DOUBLE
		;
func		: type TK_IDENTIFIER '(' parempty ')' cmd
		;
parempty	: param
		|
		;
param		: type TK_IDENTIFIER ',' param
		| type TK_IDENTIFIER
		;
inputempty	: input
		|
		;
input		: exp ',' input
		| exp
		;
cmdblock	: '{' cmdlist '}'
		| '{' '}'
		;
cmdlist		: cmd ';' cmdlist
		| cmd ';'
		;
cmd		: cmdblock
		| TK_IDENTIFIER '=' exp
		| TK_IDENTIFIER '#' exp '=' exp
		| KW_READ TK_IDENTIFIER
		| KW_PRINT printlist
		| KW_RETURN exp
		| KW_WHEN '(' exp ')' KW_THEN cmd
		| KW_WHEN '(' exp ')' KW_THEN cmd KW_ELSE cmd
		| KW_WHILE '(' exp ')' cmd
		| KW_FOR '(' TK_IDENTIFIER '=' exp KW_TO exp ')' cmd
		|
		;
printlist	: printable printlist
		| printable
		;
printable	: exp
		| LIT_STRING
		;
exp		: exp '+' exp 
		| exp '-' exp
		| exp '*' exp
		| exp '/' exp
		| TK_IDENTIFIER
		| TK_IDENTIFIER '(' inputempty ')'
		| TK_IDENTIFIER '[' exp ']'
		| exp '<' exp
		| exp '>' exp
		| '!' exp
		| exp OPERATOR_LE exp
		| exp OPERATOR_GE exp
		| exp OPERATOR_EQ exp
		| exp OPERATOR_NE exp
		| exp OPERATOR_AND exp
		| exp OPERATOR_OR exp
		| litinit
		| '(' exp ')'
		;	

%%
