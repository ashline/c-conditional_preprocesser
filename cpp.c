#include "main_algorithm.h"
int main(int argc,char* argv[]){
	FILE* in;	
	if(argc<2){
		fprintf(stderr,"Error, insufficient number of arguments:\n\tUsage: cpp [input_file_name] {output_file_name}\n");
		exit(1);
		}

		input_file_name = argv[1];
	if(argc>2){
		output_file_name = argv[2];
		}
	
	if((in=fopen(input_file_name,"r"))==NULL){
		fprintf(stderr,"Could not open input file: %s\n",input_file_name);
		exit(1);
	}

	preprocess(in);
	fclose(in);
	exit(0);
}	
