// Cauã Antunes e Gabriela Pagnoncelli

int main(int argc, char **argv) {
	yyin = fopen(argv[1],"r");
	initMe();
	yyparse();
	return 0;
}
