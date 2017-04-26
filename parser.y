%{

%}

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

%token TK_IDENTIFIER
%token LIT_INTEGER
%token LIT_REAL
%token LIT_CHAR
%token LIT_STRING

%token TOKEN_ERROR

%left '-' '+'
%left '*' '/'

%%

program		: cmdlist 
		;
var		: TK_IDENTIFIER':'type litinit
		| TK_IDENTIFIER':'type'['LIT_INTEGER']'
		;

type		: KW_BYTE
		|
		|
		|
		|
		;
func		: TK_IDENTIFIER'('parempty')' cmd
		;
parempty	: param
		|
		;
param		: type TK_IDENTIFIER ',' param
		| type TK_IDENTIFIER
		;
cmdblock	: '{'cmdlist'}'
		| '{' '}'
		;
cmdlist		: cmd';'cmdlist
		| cmd';'
		;
cmd		: LIT_INTEGER
		| TK_IDENTIFIER'='LIT_INTEGER
		| '='exp
		| cmdblock
		|
		;
exp		: exp'+'exp 
		| exp'-'exp
		| exp '*' exp
		| '-'exp
		| TK_IDENTIFIER
		| LIT_INTEGER
		;	

%%

void InitParser()
{
	fprint(stderr, "Syntax.Error\n");
	exit(3);
}
