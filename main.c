// Cauã Antunes e Gabriela Pagnoncelli

int main(int argc, char **argv) {
	if ( argc == 2 ) {
		printf( "Argumentos:\n" );
                for ( i = 1; i < argc; ++i ) {
                        printf( "  %d. %s\n", i, argv[i] );
        } else {
                printf( "No arguments were passed.\n" );
               }
        }
	yyin = fopen(argv[1],"r");
	initMe();
	yyparse();
	return 0;
}
