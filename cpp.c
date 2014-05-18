//string.h 
// stdio
//stdlib already included in hashtable.h
#include "hashtable.h"
int main(int argc,char* argv[]){
	
	hashtable* ht = create_table(5);
	printf("%d\n",ht->size);
	print_table(ht);
	add_macro(ht,"ONE");
	add_macro(ht,"ONE");
	add_macro(ht,"ONET");
	add_macro(ht,"TWO");
	add_macro(ht,"THREE");
	add_macro(ht,"FOUR");
	add_macro(ht,"FIVE");
	add_macro(ht,"SIX");
	add_macro(ht,"SEVEN");
	add_macro(ht,"EIGHT");

	print_table(ht);
	
	//remove_macro(ht,"TWO");
	remove_macro(ht,"WO");
	print_table(ht);
	remove_macro(ht,"ONET");
	print_table(ht);
	
	destroy_table(ht);
	return 0;
}
