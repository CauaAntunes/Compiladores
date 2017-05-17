%{
#include "ast.h"

AST* create(int type, char* key, AST* son0, AST* son1, AST* son2, AST* son3){
	AST *tree = (AST*) calloc(1, sizeof(AST));
	tree->type = type;
	tree->hash_key = key;
	tree->son[0] = son0;
	tree->son[1] = son1;
	tree->son[2] = son2;
	tree->son[3] = son3;
	return tree;
}

void astPrint(AST *tree, int level)
{
	int i;
	if (tree != 0){
		for(i=0; i<level; i++)
			printf(" ");
		printf("%d\n", tree->type); 
		//printf("*\n");
		for(i=0; i < 4; i++){
			//if(tree->son[i] != 0)
				astPrint(tree->son[i], level+1);
		}
	}
}

%}

%union{ char* symbol; int num;}

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

%type <num> code program def var vec litinit type func parempty param inputempty input cmdblock cmd cmdlist printlist printable exp

%%
code		: program		{$$ = $1; ASTree = $$;}
		;
program		: def ';' program	{$$ = create(';',0,$1,$3,0,0);}
		| def ';'		{$$ = create(';',0,$1,0,0,0);}
		;
def		: var
		| func
		;
var		: TK_IDENTIFIER ':' type litinit			{$$ = create(':',0,create(TK_IDENTIFIER,yylval.symbol,0,0,0,0),$3,$4,0);}
		| TK_IDENTIFIER ':' type '[' LIT_INTEGER ']' vec	{$$ = create(VDEF,0,create(TK_IDENTIFIER,yylval.symbol,0,0,0,0),$3,create(LIT_INTEGER,yylval.symbol,0,0,0,0),$7);}
		;
vec		: litinit vec		{$$ = create(' ',0,$1,$2,0,0);}
		|			{$$ = 0;}
		;
litinit		: LIT_INTEGER		{$$ = create(LIT_INTEGER,yylval.symbol,0,0,0,0);}
		| LIT_REAL		{$$ = create(LIT_REAL,yylval.symbol,0,0,0,0);}
		| LIT_CHAR		{$$ = create(LIT_CHAR,yylval.symbol,0,0,0,0);}
		;
type		: KW_BYTE		{$$ = create(KW_BYTE,0,0,0,0,0);}
		| KW_SHORT		{$$ = create(KW_SHORT,0,0,0,0,0);}
		| KW_LONG		{$$ = create(KW_LONG,0,0,0,0,0);}
		| KW_FLOAT		{$$ = create(KW_FLOAT,0,0,0,0,0);}
		| KW_DOUBLE		{$$ = create(KW_DOUBLE,0,0,0,0,0);}
		;
func		: type TK_IDENTIFIER '(' parempty ')' cmd		{$$ = create(FDEF,0,$1,create(TK_IDENTIFIER,yylval.symbol,0,0,0,0),$4,$6);}
		;
parempty	: param
		|			{$$ = 0;}
		;
param		: type TK_IDENTIFIER ',' param		{$$ = create(',',0,create(FPAR,0,$1,create(TK_IDENTIFIER,yylval.symbol,0,0,0,0),0,0),$4,0,0);}
		| type TK_IDENTIFIER			{$$ = create(FPAR,0,$1,create(TK_IDENTIFIER,yylval.symbol,0,0,0,0),0,0);}
		;
inputempty	: input
		|			{$$ = 0;}
		;
input		: exp ',' input		{$$ = create(',',0,$1,$3,0,0);}
		| exp
		;
cmdblock	: '{' cmdlist '}' 	{$$ = create('{',0,$2,0,0,0);}
		| '{' '}'		{$$ = create('{',0,0,0,0,0);}
		;
cmdlist		: cmd ';' cmdlist	{$$ = create(';',0,$1,$3,0,0);}
		| cmd ';'		{$$ = create(';',0,$1,0,0,0);}
		;
cmd		: cmdblock
		| TK_IDENTIFIER '=' exp					{$$ = create ('=',0,create(TK_IDENTIFIER,yylval.symbol,0,0,0,0),$3,0,0);}
		| TK_IDENTIFIER '#' exp '=' exp				{$$ = create ('=',0,create('#',0,create(TK_IDENTIFIER,yylval.symbol,0,0,0,0),$3,0,0),$5,0,0);}
		| KW_READ TK_IDENTIFIER					{$$ = create(KW_READ,0,create(TK_IDENTIFIER,yylval.symbol,0,0,0,0),0,0,0);}
		| KW_PRINT printlist					{$$ = create(KW_PRINT,0,$2,0,0,0);}
		| KW_RETURN exp						{$$ = create(KW_RETURN,0,$2,0,0,0);}
		| KW_WHEN '(' exp ')' KW_THEN cmd			{$$ = create(KW_WHEN,0,$3,$6,0,0);}
		| KW_WHEN '(' exp ')' KW_THEN cmd KW_ELSE cmd		{$$ = create(KW_WHEN,0,$3,$6,$8,0);}
		| KW_WHILE '(' exp ')' cmd				{$$ = create(KW_WHILE,0,$3,$5,0,0);}
		| KW_FOR '(' TK_IDENTIFIER '=' exp KW_TO exp ')' cmd	{$$ = create(KW_FOR,0,create(TK_IDENTIFIER,yylval.symbol,0,0,0,0),$5,$7,$9);}
		|							{$$ = 0;}
		;
printlist	: printable printlist 	{$$ = create(' ', 0, $1, $2,0,0);}
		| printable
		;
printable	: exp
		| LIT_STRING		{$$ = create(LIT_STRING,yylval.symbol,0,0,0,0);}
		;
exp		: exp '+' exp				{$$ = create('+',0,$1,$3,0,0);}
		| exp '-' exp				{$$ = create('-',0,$1,$3,0,0);}
		| exp '*' exp				{$$ = create('*',0,$1,$3,0,0);}
		| exp '/' exp				{$$ = create('/',0,$1,$3,0,0);}
		| TK_IDENTIFIER				{$$ = create(TK_IDENTIFIER,yylval.symbol,0,0,0,0);}
		| TK_IDENTIFIER '(' inputempty ')'	{$$ = create(FCALL,0,create(TK_IDENTIFIER,yylval.symbol,0,0,0,0),$3,0,0);}
		| TK_IDENTIFIER '[' exp ']'		{$$ = create('[',0,create(TK_IDENTIFIER,yylval.symbol,0,0,0,0),$3,0,0);}
		| exp '<' exp				{$$ = create('<',0,$1,$3,0,0);}
		| exp '>' exp				{$$ = create('>',0,$1,$3,0,0);}
		| '!' exp				{$$ = create('!',0,$2,0,0,0);}
		| exp OPERATOR_LE exp			{$$ = create(OPERATOR_LE,0,$1,$3,0,0);}
		| exp OPERATOR_GE exp			{$$ = create(OPERATOR_GE,0,$1,$3,0,0);}
		| exp OPERATOR_EQ exp			{$$ = create(OPERATOR_EQ,0,$1,$3,0,0);}
		| exp OPERATOR_NE exp			{$$ = create(OPERATOR_NE,0,$1,$3,0,0);}
		| exp OPERATOR_AND exp			{$$ = create(OPERATOR_AND,0,$1,$3,0,0);}
		| exp OPERATOR_OR exp			{$$ = create(OPERATOR_OR,0,$1,$3,0,0);}
		| litinit
		| '(' exp ')'				{$$ = create('(',0,$2,0,0,0);}
		;	

%%
