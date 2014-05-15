/*contains hashmap implementation
*/
#define HASHVAL_MAX 0xFFFFFFFFUL //max value that can be stored in an unsigned long int
#include <string.h>
struct _element{
	char* macro;// name of defined macro
	struct _element *next;//for chaining
};

typedef struct _element element;

struct _hashtable{
	int size;//size of table
	element** table; //table elements, pointer to pointer to linked list
};
typedef struct _hashtable hashtable;

/*create hashtable
 size parameter represents the desired size of the table ie number of buckets
*/
hashtable* create_hashtable(int size)
{
	int i;
	hashtable* new_table;
	if (size<1) return NULL; //cant create a table without buckets
	if((new_table=malloc(sizeof(hashtable)))==NULL) return NULL;//if memory allocation fails then return null
	/*allocate memory for all the buckets*/
	if((new_table->table= malloc(sizeof(element*)*size))==NULL)
	{ 
		//deallocate mem allocated for newtable
		return NULL;
	}
	/*set size of table*/
	new_table->size = size;
	/*initialise the pointers in the buckets to null*/
	for(i=0;i<size;i++) new_table->table[i] =NULL;
	
	return new_table;
}

/*simple hash function, converts key to integer and then determines the bucket by modulus operation with the size of the table*/
unsigned int hash(hashtable* table, char* key)
{
	int i = 0;
	unsigned long int hashval=0;//potential bug
	
	while((hashval< HASHVAL_MAX) && (i<strlen(key))){
		hashval = hashval << 8;
		hashval += key[i];
		i++;
	}
	
	return hashval % table->size;
}
