#
# UFRGS - Compiladores B - Cauã Antunes e Gabriela Pereira - 2017/1 - Etapa 5
#

etapa5: y.tab.o lex.yy.c
	gcc y.tab.o -o etapa5 lex.yy.c -w

y.tab.o: y.tab.c
	gcc -c y.tab.c -w

y.tab.c: parser.y
	yacc -d parser.y

lex.yy.c: scanner.l
	lex scanner.l

clean:
	rm etapa5 lex.yy.c *.o y.tab.c y.tab.h
