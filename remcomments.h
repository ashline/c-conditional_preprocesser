/*contatins functions that implement the comment removal step*/
#include "globals.h"
#ifndef EOL
	#define EOL '\n'
#endif
int remove_comments(FILE *in);
int find_closing_quote(FILE *in,FILE *out);
int check_if_comment(FILE *in,FILE *out);
int send_to_commentless(unsigned int c, FILE *out);
int find_comment_end(FILE *in,FILE *out);
int find_end_of_line(FILE *in,FILE *out);
int write_to_error_output(char* msg); 
/*this is the main function of the algorithm it receives a file pointer to an opened input file and then scans it for comments*/

int remove_comments(FILE *in){
	unsigned int c;
	
	FILE *out = fopen("commentless.c","w");
	if (out==NULL){
		fprintf(stderr,"Error opening comment remover output file\n");
		 exit(1);//error opening file
	}
	eout = fopen("error_log","w");
	if (eout==NULL){
		fprintf(stderr,"Error opening comment remover output file\n");
		 exit(1);//error opening file
	}
	while((c=fgetc(in))!=EOF){
		switch (c){
			case '"':
				send_to_commentless(c,out);
				find_closing_quote(in,out);
				break;
			case '/':
				check_if_comment(in,out);
				break;
			default:
				send_to_commentless(c,out);
				break;
		}
	}	

	fclose(out);
}

int send_to_commentless(unsigned int c, FILE *out){
	if(fputc(c,out)!=c){
		fprintf(stderr,"error writing to commentless file\n");
		exit(1);
	}

}

int find_closing_quote(FILE *in,FILE *out){
	unsigned int c;
	while((c=fgetc(in))!='"'){
		if (c==EOF){
			write_to_error_output("error unexpected eof");
			break;
		}
		else{
			send_to_commentless(c,out);
		}
	}
	send_to_commentless('"',out);
}

int check_if_comment(FILE *in,FILE *out){
	unsigned int c;
	c=fgetc(in);
	switch(c){
		case '*':
			find_comment_end(in,out);
			break;
		case '/':
			find_end_of_line(in,out);
			break;
		default:
			send_to_commentless('/',out);
			if(c!=EOF)
				send_to_commentless(c,out);
			break;
	}
}

int find_comment_end(FILE *in,FILE *out){
	unsigned int c;
	while(1){
		c=fgetc(in);
		if(c=='*'){
			c=fgetc(in);
			if(c=='/')
				break;
			else if(c==EOF){
			//	send_to_commentless('*',out);
				write_to_error_output("error unexpected end of input, expected */");
				break;
			}
		//	else{
			//	send_to_commentless('*',out);
			//	send_to_commentless(c,out);
			//}
		}
		else if(c==EOF){
			write_to_error_output("error unexpected end of input, expected */");
			break;
		}
	}
}

int find_end_of_line(FILE *in,FILE *out){
	unsigned int c;
	while(1){
		c=fgetc(in);
		if (c==EOF) break;
		else if(c==EOL){
			send_to_commentless(EOL,out);
			break;
		}
	}
}

int write_to_error_output(char* msg){
        if(fprintf(eout,"%s::%s\n",input_file_name,msg)<0){
                fprintf(stderr,"error writing to error output file\n");
                exit(1);
        }
}

