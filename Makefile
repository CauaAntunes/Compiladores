#
# UFRGS - Compiladores B - Cauã Antunes e Gabriela Pereira - 2017/1 - Etapa 2
#
# Makefile for single compiler call
# All source files must be included from code embedded in scanner.l
# In our case, you probably need #include "hash.c" at the beginning
# and #include "main.c" in the last part of the scanner.l
#

etapa3: y.tab.o lex.yy.c
	cc y.tab.o -o etapa3 lex.yy.c

y.tab.o: y.tab.c
	cc -c y.tab.c -w

y.tab.c: parser.y
	yacc -d parser.y

lex.yy.c: scanner.l
	lex scanner.l

clean:
	rm etapa3 lex.yy.c *.o y.tab.c y.tab.h
