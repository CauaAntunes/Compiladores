// Cauã Antunes e Gabriela Pagnoncelli

int main(int argc, char **argv) {
	if (argc < 2) {
		printf( "Invalid number of arguments.\n" );
		return 1;
	} else {
		yyin = fopen(argv[1],"r");

		if(yyin == NULL){
			printf("File not found.\n");
			return 2;
		}

		initMe();
		yyparse();
		checkDeclarations(ASTree);
		TAC *TACList = makeTAC(ASTree);
		//printTAC(TACList);
		makeASM(TACList);
		return 0;
	}
}
