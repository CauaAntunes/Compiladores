%{
#include "tokens.h"
#include "hash.c"
int line;
int running = 1;

hashtable_t *ht;

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
byte	{printf("BYTE\n");}
short	{printf("SHORT\n");}
long	{printf("LONG\n");}
float	{printf("FLOAT\n");}
double	{printf("DOUBLE\n");}
when	{printf("WHEN\n");}
then	{printf("THEN\n");}
else	{printf("ELSE\n");}
while	{printf("WHILE\n");}
for	{printf("FOR\n");}
read	{printf("READ\n");}
print	{printf("PRINT\n");}
return	{printf("RETURN\n");}

[A-Za-z][0-9A-Za-z]* {ht_set(ht, yytext,yytext); printf("ID: %s %d	%s\n",yytext,ht_hash(ht,yytext),ht_get(ht,yytext));}

(<=)	{printf("LE\n");}
(>=)	{printf("GE\n");}
(==)	{printf("EQ\n");}
(!=)	{printf("NE\n");}
(&&)	{printf("AND\n");}
(\|\|)	{printf("OR\n");}
[,;:\(\)\[\]{}\+\-\*/<>=!&\$#]	{printf("%c\n",yytext[0]);}

[0-9]*\.[0-9]*	{ht_set(ht, yytext,yytext); printf("LIT_REAL: %d	%s\n",ht_hash(ht,yytext),ht_get(ht,yytext));}
[0-9]*		{ht_set(ht, yytext,yytext); printf("LIT_INTEGER: %d	%s\n",ht_hash(ht,yytext),ht_get(ht,yytext));}
\'.\'		{ht_set(ht, yytext,yytext); printf("LIT_CHAR: %d	%s\n",ht_hash(ht,yytext),ht_get(ht,yytext));}
\".*\"		{ht_set(ht, yytext,yytext); printf("LIT_STRING: %d	%s\n",ht_hash(ht,yytext),ht_get(ht,yytext));}
"//".*
"/*"		{BEGIN COMMENT;}

<COMMENT>"*/"	{BEGIN 0;}
<COMMENT>\n	{line++;}
<COMMENT>.

<<EOF>>		{running = 0; printf("EOF\n"); return 0;}
[ \t\n]+

.	{printf("ERROR\n");}

%%
int yywrap(void) {
	return 1;
}
int main(void) { 
	ht = ht_create(100);
	printf("%d\n\n",yylex()); 
	return 0; 
} 
