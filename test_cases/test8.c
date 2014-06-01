#include<stdio.h>

int main (){

#ifdef FOO
	printf(“This should not be seen”);
#else
	printf(“This should be seen”);
#endif

#ifdef BAR
	printf(“This should not be seen”);
#else
	printf(“This should be seen”);
#endif

#ifdef BAZ
	printf(“This should not be seen”);
#else
	printf(“This should be seen”);
#endif
}
