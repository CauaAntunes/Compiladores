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

%token <symbol> TK_IDENTIFIER
%token <symbol> LIT_INTEGER
%token <symbol> LIT_REAL
%token <symbol> LIT_CHAR
%token <symbol> LIT_STRING

%token TOKEN_ERROR

%left '-' '+'
%left '*' '/'

%%

program		: cmdlist 
		;
var		: TK_IDENTIFIER ':' type litinit
		| TK_IDENTIFIER ':' type '[' LIT_INTEGER ']'
		;

type		: KW_BYTE
		|
		|
		|
		|
		;
func		: TK_IDENTIFIER '(' parempty ')' cmd
		;
parempty	: param
		|
		;
param		: type TK_IDENTIFIER ',' param
		| type TK_IDENTIFIER
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
