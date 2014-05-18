/*contatins functions that implement the comment removal step*/
#ifndef EOL
	#define EOL '\n'
#endif
int remove_comments(FILE *in);
int find_closing_quote(FILE *in,FILE *out);
int check_if_comment(FILE *in,FILE *out);
int send_to_output(unsigned int c, FILE *out);
int find_comment_end(FILE *in,FILE *out);
int find_end_of_line(FILE *in,FILE *out);

/*this is the main function of the algorithm it receives a file pointer to an opened input file and then scans it for comments*/

int removeComments(FILE *in){
	
	unsigned int c;
	FILE *out = fopen("commentless.c","w");
	if (out==NULL) return 1;//error opening file

	while((c=fgetc(in))!=EOF){
		switch (c){
			case '"':
				send_to_output(c,out);
				find_closing_quote(in,out);
				break;
			case '/':
				check_if_comment(in,out);
				break;
			default:
				send_to_output(c,out);
				break;
		}
	}	
}
int send_to_output(unsigned int c, FILE *out){
	if(fputc(c,out)!=c)
		printf("error writing to commentless file\n");

}
int find_closing_quote(FILE *in,FILE *out){
	unsigned int c;
	while((c=fgetc(in))!='"'){
		if (c==EOF){
			printf("error unexpected eof\n");
			break;
		}
		else{
			send_to_output(c,out);
		}
	}
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
			send_to_output('/',out);
			if(c!=EOF)
				send_to_output(c,out);
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
				send_to_output('*',out);
				printf("error unexpected end of input, expected */");
			}
			else{
				send_to_output('*',out);
				send_to_output(c,out);
			}
		}
		else if(c==EOF){
			printf("error unexpected end of input, expected */");
			break;
		}
		else
			send_to_output(c,out);
	}
}

int find_end_of_line(FILE *in,FILE *out){
	unsigned int c;

	while(1){
		c=fgetc(in);
		if (c==EOF) break;
		else if(c==EOL){
			send_to_output(EOL,out);
			break;
		}
	}
}
