#include<stdio.h>

int main (){

#ifndef FOO
	printf(“This should be seen”);
#else
	printf(“This should not be seen”)
#endif

#ifndef BAR
	printf(“This should be seen”)
#else
	printf(“This should not be seen”)
#endif

#ifndef BAZ
	printf(“This should be seen”);
#else
	printf(“This should not be seen”);
#endif
}
