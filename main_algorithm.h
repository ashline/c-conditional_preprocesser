#include <malloc.h>
#include "hashtable.h"
#include "remcomments.h"

unsigned int nlbp=0;// nest level being processed, used to keep track of nested conditions particularly the ones in which the condition is fulfilled
unsigned int cnl=0;// current nest level, used to keep track of nested conditions particularly the ones in which the condition is NOT fulfilled

FILE* eout=NULL;
char* cur_line=NULL;
unsigned int line_count=0; 
int dir_check=0;
size_t len = 0;
ssize_t read;

unsigned short cur_directive=0;
char* cur_macro=NULL;
enum {DEFINE,UNDEF,IFDEF,IFNDEF,ELSE,ENDIF};
int send_to_error_output(char* msg);
int find_endif();
int find_else_or_endif();
int send_to_output(FILE *out,char* msg);
int preprocess(FILE *in,char* output_file_name);
int check_line_for_directives();
/*
entrance part  of the main algorithm, it receieves an opened file pointer and performs the preprocessing on it
*/

int preprocess(FILE *in,char* output_file_name){
	FILE *commentless,*out;
	hashtable * macro_ht = create_table(10);
	remove_comments(in);
		
	if((commentless=fopen("commentless.c","r"))==NULL) return 1;//error message 	
	if((out=fopen(output_file_name,"w"))==NULL) return 1;//error message
	
	while((read=getline(&cur_line,&len,in))!= -1){//read next line
		line_count++;
		dir_check=check_line_for_directives();
		if (dir_check==0){
			switch(cur_directive){
				case DEFINE://define
					if(cur_macro!=NULL){
						add_macro(macro_ht,cur_macro);
						free(cur_macro), cur_macro=NULL;
					}
					break;
				case UNDEF://undef
					if(cur_macro!=NULL){
						remove_macro(macro_ht,cur_macro);
						free(cur_macro), cur_macro=NULL;
					}
					break;
				case IFDEF://ifdef
					if(cur_macro!=NULL){
						++nlbp;//open conditional branch
						if(lookup_macro(macro_ht,cur_macro)==1){
							find_else_or_endif(FILE *in);
						}
						free(cur_macro), cur_macro=NULL;
					}	
					break;
				case IFNDEF://ifndef
					if(cur_macro!=NULL){
						++nlbp;//open conditional branch
						if(lookup_macro(macro_ht,cur_macro)==0){
							find_else_or_endif(FILE *in);
						}
						free(cur_macro), cur_macro=NULL;
					}	
					break;
				case ELSE://else
					if(nlbp>0)//processing branch
						find_endif(FILE *in);
						--nlbp;//close branch
					}
					else{
						send_to_error_output("unexpected #else directive with no opening statement");
					}
						
					break;
				case ENDIF://endif
					if(nlbp>0){//processing branch
						--nlbp;//close branch
					}
					else{
						send_to_error_output("unexpected #endif directive with no opening statement");
					}
					break;
				}
		}
		else if(dir_check==1)
			send_to_output(cur_line,out);
		//else dont send line to output, error in directive usage
	}
	//eof	
	if(nlbp>0)//procesing branch
		send_to_error_output("unexpected end of input, expected #else or #endif");
	destroy_table(macro_ht);
	free(line);
}

int find_endif(FILE *in){
	short found =0;
	while(found==0 && (read=getline(&cur_line,&len,in))!= -1){//read next line
	line_count++;
		if (check_line_for_directives()==0){
			switch(cur_directive){
				case IFDEF://ifdef
					++cnl;
					break;
				case IFNDEF://ifndef
					++cnl;
					break;
				case ENDIF://endif
					if (cnl>0)
						--cnl;
					else
						found = 1;
					break;
			}
		}
	}
	if (read==-1)
		send_to_error_output("unexpected end of input expected #endif");
}

int find_else_or_endif(FILE *in){

	short found =0;
	while(found==0 && (read=getline(&cur_line,&len,in))!= -1){//read next line
		line_count++;
		if (check_line_for_directives()==0){
			switch(cur_directive){
				case IFDEF://ifdef
					++cnl;
					break;
				case IFNDEF://ifndef
					++cnl;
					break;
				case ELSE://else
					if(cnl==0){
						found=1;
				case ENDIF://endif
					if (cnl>0)
						--cnl;
					else
						found = 1;
					break;
			
			}
		}
	}
	if (read==-1)
		send_to_error_output("unexpected end of input expected #endif");
}
int check_line_for_directives(){
	//find start of word
	char *line_ptr=cur_line;
	int pos1=1,pos2=1,check_macro=0,i;
	char* directive=NULL;

	for(i=0;i<len;i++){
		if(*line_ptr=='\t'||*line_ptr==' '){//skip spaces and tabs 
			++line_ptr;
			++pos1;	
		}
		else 
			break;
	}

	if(i==len)
		return 1;

	if(*line_ptr=='#'){
		pos2=pos1;
		//find end position of directive
		for(;i<len;i++){
			if(*line_ptr!='\t'||*line_ptr!=' '||*line_ptr!='\n'){ 
				++line_ptr;
				++pos2;	
			}
		}
//if (pos1==pos2)//no directive here return 2// maybe not
		directive=substring(line,pos1,pos2-pos1+1);
		if (strcmp(directive,"#define")==0){
			cur_directive = DEFINE;
			check_macro=1;
			}
		else if (strcmp(directive,"#ifdef")==0){
			cur_directive = IFDEF;
			check_macro=1;
			}
		else if (strcmp(directive,"#ifndef")==0){
			cur_directive = IFNDEF;
			check_macro=1;
			}
		else if (strcmp(directive,"#undef")==0){
			cur_directive = UNDEF;
			check_macro=1;
			}
		else if (strcmp(directive,"#else")==0){
			cur_directive = ELSE;
			}
		else if (strcmp(directive,"#endif")==0){
			cur_directive = ENDIF;
			}
	}
	else
		return 1; //not directive
	if(check_macro!=0){
		pos1=pos2;
		for(;i<len;i++){
			if(*line_ptr=='\t'||*line_ptr==' '){//skip spaces and tabs 
				++line_ptr;
				++pos1;	
			}
			else 
				break;
		}
		if (i==len){
			send_to_error_output("missing macro in directive");
			return 2;
		}
		pos2=pos1;
		for(;i<len;i++){
			if(*line_ptr!='\t'||*line_ptr!=' '||*line_ptr!='\n'){ 
				++line_ptr;
				++pos2;	
			}
		}
		if(pos1==pos2){ //check if pos1 ==pos 2 if so then macro isnt there
			send_to_error_output("missing macro in directive");
		}
		else{
			cur_macro = substring(*line,pos1,pos2-pos1+1);
		}
	}
	free(directive);
	return 0;
}

char *substring(char *string, int position, int length) 
{
   char *sub;
   int c;
 
   sub = malloc(length+1);
 
   if (sub == NULL)
   {
      printf("Unable to allocate memory.\n");
      exit(1);
   }
 
   for (c = 0 ; c < position -1 ; c++) 
      string++; 
 
   for (c = 0 ; c < length ; c++)
   {
      *(sub+c) = *string;      
      string++;   
   }
 
   *(sub+c) = '\0';
 
   return sub;
}
