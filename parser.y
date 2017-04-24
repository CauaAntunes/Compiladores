%{
#include <studio.h>
#include "scanner.l"
#include "errors.h"

void yyerror(const char *msg);

%}

%token <intergerConstant> LIT_INTEGER
%token <identifier> TK_IDENTIFIER

%%

program		: cmdlist {  }
		;
cmdlist		: cmd';'cmdlist { } 
		| cmd { }
		;
cmd		: LIT_INTEGER { }
		| TK_IDENTIFIER'='LIT_INTEGER { } 
		| '='expr { }
		;
expr		: expr'+'expr { }
		|'('expr')'|LIT_INTEGER { } 
		| TK_IDENTIFIER { }
		;	

%%

void InitParser()
{
	fprint(stderr, "Syntax.Error\n");
	exit(3);
}
