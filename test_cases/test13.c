#include<stdio.h>

#define FOO

int main (){

#ifndef FOO
	printf(“This should not be seen”);
#else
	printf(“This should be seen”);

}
