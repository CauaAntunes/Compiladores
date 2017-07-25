// Cauã Antunes e Gabriela Pagnoncelli

int main(int argc, char **argv) {
	if (argc < 3) {
		printf( "Invalid number of arguments.\n" );
		return 1;
	} else {
		yyin = fopen(argv[1],"r");

		if(yyin == NULL){
			printf("File not found.\n");
			return 2;
		}

		initMe();
		if(yyparse() != 0) return 3;
		checkDeclarations(ASTree);
		TAC *TACList = makeTAC(ASTree);
		//printTAC(TACList);

		FILE *fout = fopen(argv[2], "w");
		makeASM(TACList, fout);
		return 0;
	}
}
