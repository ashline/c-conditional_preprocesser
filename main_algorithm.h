#include "hashmap.h"
#include "remcomments.h"

unsigned short cur_directive=0;
char* cur_macro=NULL;

int send_to_error_output();
int find_endif();
int find_else_or_endif();
int send_to_output();
int preprocess(FILE *in);

/*
entrance part  of the main algorithm, it receieves an opened file pointer and performs the preprocessing on it
*/

int preprocess(FILE *in,char* output_file_name){
	char* cur_line=NULL;
	unsigned int line_count=0; 
	size_t len = 0;
	ssize_t read;
	FILE *commentless,*out;
	hashtable * macro_ht = create_table(10);
	remove_comments(in);
		
	if((commentless=fopen("commentless.c","r"))==NULL) return 1;//error message 	
	if((out=fopen(output_file_name,"w"))==NULL) return 1;//error message
	
	while((read=getline(&cur_line,&len,in))!= -1){//read next line
		if (check_line_for_directives(cur_line)==0){
			switch(cur_directive){
				case 1://define
					if(cur_macro!=NULL)
						add_macro(cur_macro);
					else
						send_to_error_output("missing macro in macro definition");
					break;
				case 2://undefine
					if(cur_macro!=NULL)
						remove_macro(cur_macro);
					else
						send_to_error_output("missing macro in macro undefinition");
					break;
				case 3://ifdef
					if(cur_macro!=NULL){
						//open conditional branch
						if(lookup_macro()==1){
							find_else_or_endif();
						}
					}	
					else
						send_to_error_output("missing macro in macro definition");
					break;
				case 4://ifndef
					if(cur_macro!=NULL){
						//open conditional branch
						if(lookup_macro()==0){
							find_else_or_endif();
						}
					}	
					else
						send_to_error_output("missing macro in macro definition");
					break;
				case 5://else
					if(/*processing branch*/){
						find_endif();
						//close branch
					}
					else{
						send_to_error_output("unexpected #else directive with no opening statement");
					}
						
					break;
				case 6://endif
					if(/*processing branch*/){
						//close branch
					}
					else{
						send_to_error_output("unexpected #endif directive with no opening statement");
					}
					break;
				}
		}
		else
			send_to_output(cur_line,out);
	}
	//eof	
	if(/*processing branch*/)
		send_to_error_output("unexpected end of input, expected #else or #endif");
	
	free(line);
}
