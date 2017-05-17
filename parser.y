%{

#define 

typedef struct s_AST{
	int type;
	char* hash_key;
	s_AST* son[4];		
} AST;

AST* create(int type, char* key, AST* son0, AST* son1, AST* son2, AST* son3);{
	AST *tree = (AST*) calloc(1, sizeof(AST));
	tree->type = type;
	tree->key = key;
	tree->son[0] = son0;
	tree->son[1] = son1;
	tree->son[2] = son2;
	tree->son[3] = son3;
	return tree;
}

AST* create(int type, char* key, AST* son0, AST* son1, AST* son2);{
	return create(type, key, son0, son1, son2, NULL);
}

AST* create(int type, char* key, AST* son0, AST* son1);{
	return create(type, key, son0, son1, NULL, NULL);
}

AST* create(int type, char* key, AST* son0);{
	return create(type, key, son0, NULL, NULL, NULL);
}

AST* create(int type, char* key);{
	return create(type, key, NULL, NULL, NULL, NULL);
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

%token VDEF
%token FDEF
%token FCALL
%token FPAR

%left '-' '+'
%left '*' '/'

%%

program		: def ';' program	{$$ = create(';',NULL,$1,$3);}
		| def ';'		{$$ = create(';',NULL,$1);}
		;
def		: var
		| func
		;
var		: TK_IDENTIFIER ':' type litinit			{$$ = create(':',NULL,create(TK_IDENTIFIER,yylval.symbol),$3,$4);}
		| TK_IDENTIFIER ':' type '[' LIT_INTEGER ']' vec	{$$ = create(VDEF,NULL,create(TK_IDENTIFIER,yylval.symbol),$3,$5,$7);}
		;
vec		: litinit vec		{$$ = create(' ', NULL, $1, $2);}
		|			{$$ = 0;}
		;
litinit		: LIT_INTEGER		{create(LIT_INTEGER,yylval.symbol);}
		| LIT_REAL		{create(LIT_REAL,yylval.symbol);}
		| LIT_CHAR		{create(LIT_CHAR,yylval.symbol);}
		;
type		: KW_BYTE		{create(KW_BYTE,NULL);}
		| KW_SHORT		{create(KW_SHORT,NULL);}
		| KW_LONG		{create(KW_LONG,NULL);}
		| KW_FLOAT		{create(KW_FLOAT,NULL);}
		| KW_DOUBLE		{create(KW_DOUBLE,NULL);}
		;
func		: type TK_IDENTIFIER '(' parempty ')' cmd		{$$ = create(FDEF,NULL,$1,create(TK_IDENTIFIER,yylval.symbol),$4,$5);}
		;
parempty	: param
		|			{$$ = NULL;}
		;
param		: type TK_IDENTIFIER ',' param		{$$ = create(FPAR,NULL,create(,NULL,$1,create(TK_IDENTIFIER,yylval.symbol),$4);}
		| type TK_IDENTIFIER			{$$ = create(FPAR,NULL,$1,create(TK_IDENTIFIER,yylval.symbol));}
		;
inputempty	: input
		|			{$$ = NULL;}
		;
input		: exp ',' input		{$$ = create(',',NULL,$1,$3);}
		| exp
		;
cmdblock	: '{' cmdlist '}' 	{$$ = create('{',NULL,$2);}
		| '{' '}'		{$$ = create('{',NULL);}
		;
cmdlist		: cmd ';' cmdlist	{$$ = create(';',NULL,$1,$3);}
		| cmd ';'		{$$ = create(';',NULL,$1);}
		;
cmd		: cmdblock
		| TK_IDENTIFIER '=' exp					{$$ = create ('=',NULL,create(TK_IDENTIFIER,yylval.symbol),$3);}
		| TK_IDENTIFIER '#' exp '=' exp				{$$ = create ('=',NULL,create('#',NULL,create(TK_IDENTIFIER,yylval.symbol),$3),$5);}
		| KW_READ TK_IDENTIFIER					{$$ = create(KW_READ,NULL,create(TK_IDENTIFIER,yylval.symbol));}
		| KW_PRINT printlist					{$$ = create(KW_PRINT,NULL,$2);}
		| KW_RETURN exp						{$$ = create(KW_RETURN,NULL,$2);}
		| KW_WHEN '(' exp ')' KW_THEN cmd			{$$ = create(KW_WHEN,NULL,$3,$6);}
		| KW_WHEN '(' exp ')' KW_THEN cmd KW_ELSE cmd		{$$ = create(KW_WHEN,NULL,$3,$6,$8);}
		| KW_WHILE '(' exp ')' cmd				{$$ = create(KW_WHILE,NULL,$3,$5);}
		| KW_FOR '(' TK_IDENTIFIER '=' exp KW_TO exp ')' cmd	{$$ = create(KW_FOR,NULL,create(TK_IDENTIFIER,yylval.symbol),$5,$7,$9);}
		|
		;
printlist	: printable printlist 	{$$ = create(' ', NULL, $1, $2);}
		| printable
		;
printable	: exp
		| LIT_STRING		{create(LIT_STRING,yylval.symbol);}
		;
exp		: exp '+' exp				{$$ = create('+',NULL,$1,$3);}
		| exp '-' exp				{$$ = create('-',NULL,$1,$3);}
		| exp '*' exp				{$$ = create('*',NULL,$1,$3);}
		| exp '/' exp				{$$ = create('/',NULL,$1,$3);}
		| TK_IDENTIFIER				{$$ = create(TK_IDENTIFIER,yylval.symbol);}
		| TK_IDENTIFIER '(' inputempty ')'	{$$ = create(FCALL,NULL,create(TK_IDENTIFIER,yylval.symbol),$3);}
		| TK_IDENTIFIER '[' exp ']'		{$$ = create('[',NULL,create(TK_IDENTIFIER,yylval.symbol),$3);}
		| exp '<' exp				{$$ = create('<',NULL,$1,$3);}
		| exp '>' exp				{$$ = create('>',NULL,$1,$3);}
		| '!' exp				{$$ = create('!',NULL,$2);}
		| exp OPERATOR_LE exp			{$$ = create(OPERATOR_LE,NULL,$1,$3);}
		| exp OPERATOR_GE exp			{$$ = create(OPERATOR_GE,NULL,$1,$3);}
		| exp OPERATOR_EQ exp			{$$ = create(OPERATOR_EQ,NULL,$1,$3);}
		| exp OPERATOR_NE exp			{$$ = create(OPERATOR_NE,NULL,$1,$3);}
		| exp OPERATOR_AND exp			{$$ = create(OPERATOR_AND,NULL,$1,$3);}
		| exp OPERATOR_OR exp			{$$ = create(OPERATOR_OR,NULL,$1,$3);}
		| litinit
		| '(' exp ')'				{$$ = create('(',NULL,$2);}
		;	

%%
