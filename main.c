// Cauã Antunes e Gabriela Pagnoncelli
int main(void) {
	initMe();
	while(isRunning())
		printf("%d\n",yylex());

	return 0;
}
