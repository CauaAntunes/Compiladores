// Cauã Antunes e Gabriela Pagnoncelli

int main(int argc, char **argv) {
	if (argc != 2) {
               printf( "Invalid number of arguments.\n" );
        } else {
		yyin = fopen(argv[1],"r");
		initMe();
		yyparse();
		print(stdout,ASTree);
	}
	return 0;
}
