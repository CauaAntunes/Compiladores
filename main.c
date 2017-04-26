// Cauã Antunes e Gabriela Pagnoncelli
#include "y.tab.h"

int main(void) {
	initMe();
	//printf("%d\n\n",yylex());
	yyparser();
	return 0;
}
