#include<stdio.h>

#define FOO

int main (){

#ifndef FOO
	printf(“This should not be seen”);
	#ifdef FOO
		printf(“This should not be seen”);
	 #else

 		printf(“This should not be seen”);
	#endif
#else
	printf(“This should be seen”);
	#ifdef BAR
		printf(“This should not be seen”);
	#else
		printf(“This should be seen”);
	#endif
#endif
}
