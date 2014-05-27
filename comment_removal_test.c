#include<stdio.h>
#include "remcomments.h"

int main(){

	FILE *in = fopen("testcomments.c","r");
	remove_comments(in);
	fclose(in);
	return 0;
}
