// Cauã Antunes e Gabriela Pagnoncelli

int main(int argc, char **argv) {
	if (argc != 3) {
		printf( "Invalid number of arguments.\n" );
		return 1;
	} else {
		yyin = fopen(argv[1],"r");
		FILE *out = fopen(argv[2],"w");

		if(out == NULL)
			return 2;

		initMe();
		yyparse();
		print(out,ASTree);
		return 0;
	}
}
