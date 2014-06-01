#include<stdio.h>

#define FOO

int main (){
	printf(“This should be seen”);
#else
	printf(“This should be seen”);
#endif
}
