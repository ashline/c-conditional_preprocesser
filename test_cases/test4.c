#include<stdio.h>

#define FOO

int main (){

#ifdef FOO
	printf(“This should be seen”);
#endif

#ifdef BAR
	printf(“This should not be seen”);
#endif

#ifndef FOO
	printf(“This should not be seen”);
#endif

#ifndef BAR
	printf(“This should be seen”);
#endif
}
