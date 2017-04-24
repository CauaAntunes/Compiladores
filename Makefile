#
# UFRGS - Compiladores B - Cauã Antunes e Gabriela Pereira - 2017/1 - Etapa 2
#
# Makefile for single compiler call
# All source files must be included from code embedded in scanner.l
# In our case, you probably need #include "hash.c" at the beginning
# and #include "main.c" in the last part of the scanner.l
#

etapa1: y.tab.o lex.yy.c
	cc y.tab.o gcc -o etapa1 lex.yy.c

y.tab.o: y.tab.c
	 cc -c y.tab.c

y.tab.c: parser.y
	 yacc -d parser.y

lex.yy.c: scanner.l
	lex scanner.l

clean:
	rm etapa1 lex.yy.c *.o ytab.c y.tab.h
