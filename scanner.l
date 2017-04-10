%{
#include "tokens.h"
int line;
int running = 1;

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

[A-Za-z][0-9A-Za-z]* {printf("ID: %s\n",yytext);}

(<=)	{printf("LE\n");}
(>=)	{printf("GE\n");}
(==)	{printf("EQ\n");}
(!=)	{printf("NE\n");}
(&&)	{printf("AND\n");}
(\|\|)	{printf("OR\n");}
[,;:\(\)\[\]{}\+\-\*/<>=!&\$#]	{printf("%c\n",yytext[0]);}

[0-9]*\.[0-9]*	{printf("LIT_REAL\n");}
[0-9]*		{printf("LIT_INTEGER\n");}
\'.\'		{printf("LIT_CHAR\n");}
\".*\"		{printf("LIT_STRING\n");}
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
	printf("%d\n\n",yylex()); 
	return 0; 
} 
