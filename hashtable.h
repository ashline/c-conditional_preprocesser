/*contains hashmap implementation
*/
#define HASHVAL_MAX 0xFFFFFFFFUL //max value that can be stored in an unsigned long int
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
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

/*functions in this header file*/
hashtable* create_table(int size);
int lookup_macro(hashtable* h_table, char* macro);
unsigned int hash(hashtable* h_table, char* key);
int add_macro(hashtable* h_table,char* new_macro);
int remove_macro(hashtable* h_table,char *target_macro);
int destroy_table(hashtable* h_table);
int print_table(hashtable* h_table);

/*create hashtable
 size parameter represents the desired size of the table ie number of buckets
*/
hashtable* create_table(int size){
	int i;
	hashtable* new_table;
	if (size<1) return NULL; //cant create a table without buckets
	if((new_table=malloc(sizeof(hashtable)))==NULL){//if memory allocation fails then return null
		printf("Unable to allocate memory.\n");
		exit(1);
   	}
	/*allocate memory for all the buckets*/
	if((new_table->table= malloc(sizeof(element*)*size))==NULL){ 
		//deallocate mem allocated for newtable
		free(new_table);
      		printf("Unable to allocate memory.\n");
      		exit(1);
	}
	/*set size of table*/
	new_table->size = size;
	/*initialise the pointers in the buckets to null*/
	for(i=0;i<size;i++) new_table->table[i] =NULL;
	
	return new_table;
}

/*simple hash function, converts key to integer and then determines the bucket by modulus operation with the size of the table*/
unsigned int hash(hashtable* h_table, char* key){
	int i = 0;
	unsigned long int hashval=0;//potential bug
	
	while((hashval< HASHVAL_MAX) && (i<strlen(key))){
		hashval = hashval << 8;
		hashval += key[i];
		i++;
	}
	
	return hashval % h_table->size;
}
/*look for macro in table, return 0 if found else return 1
*/
int lookup_macro(hashtable* h_table, char* macro){
	int bucket= 0;
	element* cur;
	bucket = hash(h_table,macro);
	for(cur= h_table->table[bucket];cur!=NULL;cur=cur->next){
		if(strcmp(macro,cur->macro)==0) return 0;
	}
	return 1;
}

int add_macro(hashtable* h_table,char* new_macro){

	element *new_element=NULL;
	element *cur=NULL;
	element *prev=NULL;

	int bucket = hash(h_table,new_macro);
	
	if((new_element=malloc(sizeof(element)))==NULL){
      		printf("Unable to allocate memory.\n");
      		exit(1);
   	}
	
	if(lookup_macro(h_table,new_macro)==0) return 0;

	
	cur = h_table->table[bucket];
	new_element->macro = strdup(new_macro);
	new_element->next=NULL;

	if(cur==NULL){// if there is nothing in the bucket
		h_table->table[bucket]= new_element;
	}
	else{
		//check if the first element is greater than the new one
		if(strcmp(cur->macro, new_macro)>0){
			new_element->next=cur;
			h_table->table[bucket]=new_element;	
		}
		else{//insert the new element into appropriate place , sorted list
			prev = cur;
			cur= cur->next;
			while(cur!=NULL && (strcmp(cur->macro,new_macro)<0)){
				prev= cur;
				cur= cur->next;
			}
			prev->next= new_element;
			new_element->next=cur;
		}
	}
	return 0;
}

int remove_macro(hashtable* h_table,char *target_macro){

	element* prev=NULL;
	element* cur=NULL;
	int bucket = hash(h_table,target_macro);
	
	if(lookup_macro(h_table,target_macro)) return 0; //if the macro is not in the table
	
	cur= h_table->table[bucket];	
	
	if(strcmp(cur->macro,target_macro)==0){//if the first element is the target
		h_table->table[bucket] = cur->next;
	}
	else{
		prev=cur;
		cur= cur->next;
		while(strcmp(cur->macro,target_macro)!=0){
			prev= cur;
			cur = cur->next;
		}
		
		//it is certain that cur != NULL since the macro is in the table
		prev->next= cur->next;
	}

	free(cur->macro);
	free(cur);
	
}
/*
free memory used by the table
*/
int destroy_table(hashtable* h_table){
	int i=0;
	element* cur=NULL;
	element* tmp=NULL;
	if(h_table ==NULL) return 1;
	
	for(i=0;i<h_table->size;i++){
		cur = h_table->table[i];
		tmp= cur;
		while(cur!=NULL){
			tmp=cur->next;
			free(cur->macro);
			free(cur);
			cur= tmp;
		}
	}

	free(h_table->table);
	free(h_table);
}

/*print all the contents of the table*/
int print_table(hashtable* h_table){
	int i=0;
	element* cur= NULL;

	if(h_table==NULL) return 1;
	printf("\nContents of hashtable\n");
	printf("============================================================\n");
	printf("Bucket\t\tContents\n");
	printf("============================================================\n");
	
	for(i=1;i<=h_table->size;i++){
		printf("%d.\t\t",i);
		cur=h_table->table[i-1];
		
		while(cur!=NULL){
			if(cur->next==NULL)
				printf("%s",cur->macro);
			else
				printf("%s, ",cur->macro);
			cur=cur->next;
		}
	printf("\n------------------------------------------------------------\n");
	}
}
