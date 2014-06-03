#include<stdio.h>

int main (){

#ifdef 
	printf(“This should not be seen”);
#else
	printf(“This should not be seen”)
#endif

#ifndef BAR
	printf(“This should be seen”)
#else
	printf(“This should not be seen”)
#endif

#ifndef 
	printf(“This should not be seen”);
#else
	printf(“This should not be seen”);
#endif
}
