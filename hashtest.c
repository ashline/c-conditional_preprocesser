//string.h 
// stdio
//stdlib already included in hashtable.h
#include "hashtable.h"
int main(int argc,char* argv[]){
	
	hashtable* ht = create_table(5);
	printf("%d\n",ht->size);
	print_table(ht);
	add_macro(ht,"ONE");
	add_macro(ht,"ONE");// adding something that was already added
	add_macro(ht,"ONET");
	add_macro(ht,"TWO");
	add_macro(ht,"THREE");
	add_macro(ht,"FOUR");
	add_macro(ht,"FIVE");
	add_macro(ht,"SIX");
	add_macro(ht,"SEVEN");
	add_macro(ht,"EIGHT");
	add_macro(ht,"NINE");
	add_macro(ht,"TEN");

	print_table(ht);
	
	//remove_macro(ht,"TWO");
	remove_macro(ht,"WO");//removing something that is not in the table
	remove_macro(ht,"ONET");
	print_table(ht);
	//
	if(lookup_macro(ht,"ONE")==0)
		printf("ONE is in the table\n");	
	else
		printf("ONE is not in the table\n");	
		
	if(lookup_macro(ht,"FOO")==0)
		printf("FOO is in the table\n");	
	else
		printf("FOO is not in the table\n");	
	if(lookup_macro(ht,"ONET")==0)
		printf("ONET is in the table\n");	
	else
		printf("ONET is not in the table\n");	

	destroy_table(ht);
	return 0;
}
