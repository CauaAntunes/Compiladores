%{
#include "scanner.l"

%}

%token <intergerConstant> LIT_INT
%token <identifier> TK_ID

%left '-' '+'
%left '*' '/'

%%

program		: cmdlist 
		;
cmdlist		: cmd';'cmdlist 
		| cmd 
		;
cmd		: LIT_INT
		| TK_ID'='LIT_INT 
		| '='exp
		;
exp		: exp'+'exp 
		| exp'-'exp
		| exp '*' exp
		| '-'exp
		| TK_ID
		| LIT_INT
		;	

%%

void InitParser()
{
	fprint(stderr, "Syntax.Error\n");
	exit(3);
}
