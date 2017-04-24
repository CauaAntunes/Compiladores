%{
#include "scanner.l"
#include "parser.h"
#include "errors.h"

void yyerror(const char *msg);

%}

%token LIT_INTEGER
%token TK_IDENTIFIER

%%

program		: cmdlist
		;
cmdlist		: cmd';'cmdlist | cmd
		;
cmd		: LIT_INTEGER | TK_IDENTIFIER'='LIT_INTEGER | '='expr
		;
expr		: expr','expr|'('expr')'|LIT_INTEGER|TK_IDENTIFIER
		;	

%%

void InitParser()
{
	fprint(stderr, "Syntax.Error\n");
	exit(3);
}
