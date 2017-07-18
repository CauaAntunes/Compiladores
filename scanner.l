%{
//Cauã Antunes e Gabriela Pagnoncelli
#include <stdio.h>
#include <stdlib.h>
#include "hash.c"
#include "ast.h"

#include "y.tab.h"
#ifndef YYSTYPE
#define YYSTYPE int
#endif

int line = 1;
int running = 1;

hashtable_t *ht;

#include "semantic.c"
#include "tac.c"

int getLineNumber(){
	return line;
}

int isRunning(){
	return running;
}

void initMe(){
	ht = ht_create(100);
}

void yyerror (char const *s) {
	fprintf (stderr, "Line %d: %s\n",getLineNumber(), s);
	exit(3);
}
%}

%x COMMENT

%%
\n	{line++;}
byte	{return KW_BYTE;}
short	{return KW_SHORT;}
long	{return KW_LONG;}
float	{return KW_FLOAT;}
double	{return KW_DOUBLE;}
when	{return KW_WHEN;}
then	{return KW_THEN;}
else	{return KW_ELSE;}
while	{return KW_WHILE;}
for	{return KW_FOR;}
to	{return KW_TO;}
read	{return KW_READ;}
print	{return KW_PRINT;}
return	{return KW_RETURN;}

[_A-Za-z][_A-Za-z0-9]* {ht = ht_set(ht, yytext,yytext);  yylval.symbol = yytext; return TK_IDENTIFIER;}

(<=)	{return OPERATOR_LE;}
(>=)	{return OPERATOR_GE;}
(==)	{return OPERATOR_EQ;}
(!=)	{return OPERATOR_NE;}
(&&)	{return OPERATOR_AND;}
(\|\|)	{return OPERATOR_OR;}
[,;:\(\)\[\]{}\+\-\*/<>=!&\$#]	{return yytext[0];}

[0-9]*\.[0-9]*	{ht = ht_set(ht, yytext,yytext); ht_get(ht, yytext)->data_type = TYPE_REAL; yylval.symbol = yytext; return LIT_REAL;}
[0-9]*		{ht = ht_set(ht, yytext,yytext); ht_get(ht, yytext)->data_type = TYPE_INT;  yylval.symbol = yytext; return LIT_INTEGER;}
\'.\'		{ht = ht_set(ht, yytext,yytext); ht_get(ht, yytext)->data_type = TYPE_INT; yylval.symbol = yytext; return LIT_CHAR;}
\"[^\"\n]*\"	{ht = ht_set(ht, yytext,yytext); ht_get(ht, yytext)->data_type = TYPE_STR;  yylval.symbol = yytext; return LIT_STRING;}
"//".*
"/*"		{BEGIN COMMENT;}

<COMMENT>"*/"	{BEGIN 0;}
<COMMENT>\n	{line++;}
<COMMENT>.

<<EOF>>		{running = 0; return 0;}
[ \t\r]+

.	{return TOKEN_ERROR;}

%%
int yywrap(void) {
	running = 0;

	return 1;
}
#include "assembly.c"
#include "main.c"
