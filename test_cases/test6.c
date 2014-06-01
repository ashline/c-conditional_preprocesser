#include<stdio.h>

#define FOO

int main (){

#ifndef FOO
	printf(“This should not be seen”);
#else
	printf(“This should be seen”);
#endif

#undef FOO

#ifndef FOO
	printf(“This should be seen”);
#else
	printf(“This should not be seen”);
#endif

#define FOO

#ifndef FOO
	printf(“This should not be seen”);
#else
	printf(“This should be seen”);
#endif
}
