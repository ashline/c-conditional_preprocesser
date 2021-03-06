#include <malloc.h>
#include "hashtable.h"
#include "remcomments.h"
unsigned int nlbp=0;// nest level being processed, used to keep track of nested conditions particularly the ones in which the condition is fulfilled
unsigned int cnl=0;// current nest level, used to keep track of nested conditions particularly the ones in which the condition is NOT fulfilled

char* cur_line=NULL;
char* output_file_name =NULL;
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
int preprocess(FILE *in);
int check_line_for_directives();
char *substring(char *string, int position, int length);
/*
entrance part  of the main algorithm, it receieves an opened file pointer and performs the preprocessing on it
*/

int preprocess(FILE *in){
	FILE *commentless,*out;
	hashtable * macro_ht = create_table(10);
	remove_comments(in);
	if((commentless=fopen("commentless.c","r"))==NULL){ 
		fprintf(stderr,"Error, could not open commentless.c for reading\n");
		return 1;
	} 	
	if((out=fopen(output_file_name,"w"))==NULL){
		fprintf(stderr,"Error, could not open file %s for writing\n",output_file_name);
		return 1;
	}
	if((eout = fopen("error_log","a"))==NULL){
		fprintf(stderr,"error opening error output file\n");
		return 1;
	}
	
	while((read=getline(&cur_line,&len,commentless))!= -1){//read next line
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
							if(find_else_or_endif(commentless)==2)//endif
							--nlbp;//close branch after #endif found
						}
						free(cur_macro), cur_macro=NULL;
					}	
					break;
				case IFNDEF://ifndef
					if(cur_macro!=NULL){
						++nlbp;//open conditional branch
						if(lookup_macro(macro_ht,cur_macro)==0){
							if(find_else_or_endif(commentless)==2)//endif
								--nlbp;//close branch after #endif found
						}
						free(cur_macro), cur_macro=NULL;
					}	
					break;
				case ELSE://else
					if(nlbp>0){//processing branch
						find_endif(commentless);
						--nlbp;//close branch after #endif found
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
			send_to_output(out,cur_line);
		//else dont send line to output, error in directive usage
		else if(dir_check==2)
			find_endif(commentless);
	}
	//eof	
#ifdef DBUG
	printf("[%d] nlbp \n",nlbp);
#endif
	if(nlbp>0)//procesing branch
		send_to_error_output("unexpected end of input, expected #else or #endif");
	//clean_up
	fclose(out);
	fclose(commentless);
	if(eout !=NULL)
		fclose(eout), eout=NULL;
	destroy_table(macro_ht);
	free(cur_line);
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

	while((read=getline(&cur_line,&len,in))!= -1){//read next line
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
					if(cnl==0)
						return(1);
					break;
				case ENDIF://endif
					if (cnl>0)
						--cnl;
					else
						return(2);
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
			if(*line_ptr!='\t'&&*line_ptr!=' '&&*line_ptr!='\n'){ 
				++line_ptr;
				++pos2;	
			}
		}
//if (pos1==pos2)//no directive here return 2// maybe no
		directive=substring(cur_line,pos1,(pos2-pos1));
#ifdef DBUG
	printf("[%s] directive found on line:%d\n",directive,line_count);
#endif
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
		for(i=pos1;i<len;i++){
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
			if(*line_ptr!='\t'&&*line_ptr!=' '&&*line_ptr!='\n'){ 
				++line_ptr;
				++pos2;	
			}
		}
		if(pos1==pos2){ //check if pos1 ==pos 2 if so then macro isnt there
			send_to_error_output("missing macro in directive");
			return 2;
		}
		else{
			cur_macro = substring(cur_line,pos1,pos2-pos1);
#ifdef DBUG
	printf("[%s] macro found on line:%d\n",cur_macro,line_count);
#endif
		}
	}
	free(directive);
	return 0;
}

char *substring(char *string, int position, int length){
   char *sub;
   int c;
 
   sub = malloc(length+1);
 
   if (sub == NULL)
   {
      fprintf(stderr,"Unable to allocate memory.\n");
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

int send_to_output(FILE *out,char* msg){
	if(fputs(msg,out)<0){
		fprintf(stderr,"error writing to output file\n");	
      		exit(1);
	}
}

int send_to_error_output(char* msg){
	if(fprintf(eout,"%s::%d::%s \n",input_file_name,line_count,msg)<0){
		fprintf(stderr,"error writing to error output file\n");
      		exit(1);
	}
}
