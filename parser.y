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
litinit		: TK_IDENTIFIER
		| LIT_INTEGER
		| LIT_REAL
		| LIT_CHAR
		;
type		: KW_BYTE
		| KW_SHORT
		| KW_LONG
		| KW_FLOAT
		| KW_DOUBLE
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
exp		: exp '+' exp 
		| exp '-' exp
		| exp '*' exp
		| exp '/' exp
		| TK_IDENTIFIER
		| TK_IDENTIFIER '(' parempty ')'
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

void InitParser()
{
	fprint(stderr, "Syntax.Error\n");
	exit(3);
}
