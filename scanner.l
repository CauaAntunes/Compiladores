%{
//Cauã Antunes e Gabriela Pagnoncelli
#include "tokens.h"
#include "hash.c"
int line;
int running = 1;

hashtable_t *ht;

void initMe(){
    ht = ht_create(100);
}

int getLineNumber(){
	return line;
}

int isRunning(){
	return running;
}
%}

%x COMMENT

%%
\n	{line++;}
byte	{return KW_BYTE;}
short	{return KW_SHORT;}
long	{return KW_LONG;/*lol*/}
float	{return KW_FLOAT;}
double	{return KW_DOUBLE;}
when	{return KW_WHEN;}
then	{return KW_THEN;}
else	{return KW_ELSE;}
while	{return KW_WHILE;}
for	{return KW_FOR;}
read	{return KW_READ;}
print	{return KW_PRINT;}
return	{return KW_RETURN;}

[A-Za-z][0-9A-Za-z]* {ht = ht_set(ht, yytext,yytext); return TK_IDENTIFIER;}

(<=)	{return OPERATOR_LE;}
(>=)	{return OPERATOR_GE;}
(==)	{return OPERATOR_EQ;}
(!=)	{return OPERATOR_NE;}
(&&)	{return OPERATOR_AND;}
(\|\|)	{return OPERATOR_OR;}
[,;:\(\)\[\]{}\+\-\*/<>=!&\$#]	{return yytext[0];}

[0-9]*\.[0-9]*	{ht = ht_set(ht, yytext,yytext); return LIT_REAL;}
[0-9]*		{ht = ht_set(ht, yytext,yytext); return LIT_INTEGER;}
\'.\'		{ht = ht_set(ht, yytext,yytext); return LIT_CHAR;}
\".*\"		{ht = ht_set(ht, yytext,yytext); return LIT_STRING;}
"//".*
"/*"		{BEGIN COMMENT;}

<COMMENT>"*/"	{BEGIN 0;}
<COMMENT>\n	{line++;}
<COMMENT>.

<<EOF>>		{running = 0; printf("EOF\n"); return 0;}
[ \t\n]+

.	{return TOKEN_ERROR;}

%%
int yywrap(void) {
	return 1;
}
#include "main.c"
