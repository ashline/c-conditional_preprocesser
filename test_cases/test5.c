#include<stdio.h>

#define FOO

int main (){

#ifdef FOO
	printf(“This should be seen”);
#else
	printf(“This should not be seen”);
#endif

#undef FOO

#ifdef FOO
	printf(“This should not be seen”);
#else
	printf(“This should be seen”);
#endif

#define FOO

#ifdef FOO
	printf(“This should be seen”);
#else
	printf(“This should not be seen”);
#endif
}
