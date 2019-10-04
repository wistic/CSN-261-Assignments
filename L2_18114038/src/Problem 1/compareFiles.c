/**
* @file compareFiles.c
* @brief This C file is a program used to compare the decrypted output file with the initial input.
*
* @author Prathamesh Katkar
*
* @date 07/08/2019
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
	if (argc<3)
	{
		printf("All arguments have not been provided.\n");   //Checking if all command line arguments have been given
		return 1;
	}
	else
	{
		const char* file_input=argv[1];
		const char* file_output=argv[2];
		FILE* input_file=fopen(file_input,"r");  //Opening the two files
		FILE* output_file=fopen(file_output,"r");
		if ((input_file==NULL) || (output_file==NULL))
			{
				printf("Error in reading files.\n");
				return 1;
			}
		char storage1[10000];
		char buffer1[1024];
		while(fgets(buffer1,1024,input_file)){  //Reading line by line
			strcat(storage1,buffer1);
		}
		char storage2[10000];
		char buffer2[1024];
		while(fgets(buffer2,1024,output_file)){
			strcat(storage2,buffer2);
		}
		if(strcmp(storage1,storage2)==0)   //Comparing the files
			printf("Files are identical.\n");
		else
			printf("Files are not identical\n");
	}
	return 0;
}
