/**
* @file inverseTranspose.c
* @brief This C file is a program used to perform a simple transposition cipher decryption.
*
* @author Prathamesh Katkar
*
* @date 07/08/2019
*/

/**
* This method decrypt() will be used to decrypt the given encrypted input data from a file and print the decrypted data to an output file..
* @param FILE* input_file,int n,int a,int b
* @date 07/08/2019
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE* decrypt(FILE* input_file,int n,int a,int b){
	char storage[10000];
	char buffer[1024];
	while(fgets(buffer,1024,input_file)){ // Reading line by line from the encrypted file
		strcat(storage,buffer);
	}
	system("touch ../../Generated_output_files/decryptedOutputfile.txt");  //Creating an empty file
	FILE* output_file=fopen("../../Generated_output_files/decryptedOutputfile.txt","w");
	if (output_file==NULL){
		printf("Unable to create output file\n");
		return NULL;
	}
	int c=n-(strlen(storage)%n);
	while(c--!=0){
		storage[strlen(storage)]='*';  //Using * to represent NULL characters instead of \0 for sake of convenience
	}
	char decryptedText[10000];
	int length=strlen(storage);
	int no_of_sets=length/n;
	while(no_of_sets--!=0){
		for (int i=(n*no_of_sets);i<(n*(no_of_sets+1));i++){
			decryptedText[(((a*i)+b)%n)+(n*no_of_sets)]=storage[i];  //Block by block transposition
		}
	}
	for (int i=0;i<strlen(decryptedText);i++){
		if (decryptedText[i]=='*')
			decryptedText[i]='\0';
	}
	fprintf(output_file,"%s",decryptedText);
	return output_file;
}
int main(int argc, char const *argv[])
{
	//Driver program
	if (argc<4)
	{
		printf("All arguments have not been provided.\n"); //Checking if all command line arguments have been given
		return 1;
	}
	else
	{
		int n=atoi(argv[1]);
		int a=atoi(argv[2]);
		int b=atoi(argv[3]);
		if (n<1)
		{
			printf("Value of n is not incompatible.\n");
			return 2;
		}
		else
		{
			while (a<0)
				{
					a=a+n;  // Shifting values of a or b by n will not change the output
				}
			while (b<0)
				{
					b=b+n;
				}
			if (a==0){
				printf("Key is not suitable for decryption.\n");
				return 0;
			}
			else
			{
				if (b==0){
					printf("No decryption will take place as input will be same as output.\n");
					return 0;
				}
				else
				{
					FILE* fp=fopen("../../Generated_output_files/outputfile.txt","r");  //Opening the encrypted input file
					if (fp==NULL){
						printf("Error in reading file.\n");
						return 0;
					}
					else
					{
						FILE* op=decrypt(fp,n,a,b);  //Calling the decrypt method
						if (op==NULL)
							printf("Error in decrypting the given file.\n");
						else
							printf("File has been decrypted and output file has been produced.\n");
					}
				}
			}
		}
	}
}