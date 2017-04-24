int main(void) { 
	ht = ht_create(100);
	//printf("%d\n\n",yylex());
	yyparser(); 
	return 0; 
} 
