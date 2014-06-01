#include<stdio.h>

#define FOO

#define BAR

#define BAZ

int main (){

#ifdef FOO
	printf(“This should be seen”);
#else
	printf(“This should not be seen”);
#endif

#ifdef BAR
	printf(“This should be seen”);
#else
	printf(“This should not be seen”);
#endif

#ifdef BAZ
	printf(“This should be seen”);
#else
	printf(“This should not be seen”);
#endif
}
