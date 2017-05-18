// Cauã Antunes e Gabriela Pagnoncelli

int main(int argc, char **argv) {
	if (argc != 3) {
               printf( "Invalid number of arguments.\n" );
        } else {
		yyin = fopen(argv[1],"r");
		FILE *out = fopen(argv[2],"w");
		initMe();
		yyparse();
		print(out,ASTree);
	}
	return 0;
}
