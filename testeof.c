#include <stdio.h>

int main(){

	unsigned int c;
	FILE *in = fopen("testfile","r");

	while((c=fgetc(in))!=EOF) 
		printf("%c",(char)c);
	
	c= fgetc(in);	
	if (c==EOF)
		printf("hmm end of file baba \n");
	else 
		printf("hmm zvirikumbofamba sei baba \n");

	c= fgetc(in);	
	if (c==EOF)
		printf("hmm end of file baba \n");
	else 
		printf("hmm zvirikumbofamba sei baba \n");
	fclose(in);
	return 0;
}
