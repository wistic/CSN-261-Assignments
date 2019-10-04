/**
* @file MAT.c
* @brief This C file is a program to generate a Quadtree of a region with the help of Medieval Axis Transformation.
*
* @author Prathamesh Katkar
*
* @date 07/08/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef enum {TRUE,FALSE} boolean; //Defining a boolean datatype
/**
* This struct represents one Leaf or a Node of a Quadtree.
* @date 07/08/2019
*/
struct Leaf
{
	int bit_value; //Represents bit value of the node
	int level;
	int index;
	int x;
	int y;
	struct Leaf* branch1; //For division into four parts
	struct Leaf* branch2;
	struct Leaf* branch3;
	struct Leaf* branch4;
};
/**
* This struct represents the Quadtree.
* @date 07/08/2019
*/
struct Quadtree
{
	struct Leaf* root;
	int size_of_array;
	int no_of_nodes;
	int* MaximalArray;
};
/**
* This method createLeaf() will be used to create a Leaf which is a part of the Quadtree.
* @param int bit_value,int level,int x,int y,struct Quadtree* tree
* @date 07/08/2019
*/
struct Leaf* createLeaf(int bit_value,int level,int x,int y,struct Quadtree* tree){
	struct Leaf* leaf=(struct Leaf*)malloc(sizeof(struct Leaf));
	leaf->bit_value=bit_value;
	leaf->level=level;
	tree->no_of_nodes=tree->no_of_nodes+1;
	leaf->index=tree->no_of_nodes;
	leaf->x=x;
	leaf->y=y;
	leaf->branch1=NULL;
	leaf->branch2=NULL;
	leaf->branch3=NULL;
	leaf->branch4=NULL;
	return leaf;
}
/**
* This method createQuadtree() will be used to make a Quadtree for the data representation.
* @param none
* @date 07/08/2019
*/
struct Quadtree* createQuadtree(){
	struct Quadtree* tree=(struct Quadtree*)malloc(sizeof(struct Quadtree));
	tree->no_of_nodes=0;
	tree->root=createLeaf(0,0,0,0,tree);
	tree->size_of_array=0;
	tree->MaximalArray=NULL;
	return tree;
}
/**
* This method check() will be used to check whether the given Leaf has all bit values same or if it is to be broken into smaller Leaves.
* @param struct Quadtree* tree,struct Leaf* leaf,int* storage
* @date 07/08/2019
*/
void check(struct Quadtree* tree,struct Leaf* leaf,int* storage){
	if (tree==NULL)
		printf("Quadtree pointer is invalid.\n");
	else{
		if (leaf==NULL)
			printf("Leaf pointer is invalid.\n");
		else{
			if (storage==NULL)
				printf("Storage pointer is invalid.\n");
			else{
				boolean bl=TRUE;
				int t=storage[(leaf->x*tree->size_of_array)+leaf->y];
				int leafsize=(tree->size_of_array)/((int)pow(2,leaf->level));
				for (int i=leaf->x;i<(leaf->x+leafsize);i++)
				{
					for (int j=leaf->y;j<(leaf->y+leafsize);j++)
					{
						if (storage[(i*tree->size_of_array)+j]!=t){ //Checking the whole Leaf
							bl=FALSE;
							break;
						}
					}
				}
				if (bl==TRUE){
					leaf->bit_value=t;
					for (int i=leaf->x;i<(leaf->x+leafsize);i++)
					{
						for (int j=leaf->y;j<(leaf->y+leafsize);j++)
						{
							tree->MaximalArray[(i*tree->size_of_array)+j]=leaf->index;
						}
					}
				}
				else{
					tree->no_of_nodes=tree->no_of_nodes-1;
					leaf->index=-1;
					leaf->bit_value=-1;
					leaf->branch1=createLeaf(0,leaf->level+1,leaf->x,leaf->y,tree); //Division of Leaf into four parts
					check(tree,leaf->branch1,storage);
					leaf->branch2=createLeaf(0,leaf->level+1,leaf->x,leaf->y+(leafsize/2),tree);
					check(tree,leaf->branch2,storage);
					leaf->branch3=createLeaf(0,leaf->level+1,leaf->x+(leafsize/2),leaf->y,tree);
					check(tree,leaf->branch3,storage);
					leaf->branch4=createLeaf(0,leaf->level+1,leaf->x+(leafsize/2),leaf->y+(leafsize/2),tree);
					check(tree,leaf->branch4,storage);
				}
			}
		}
	}
}
/**
* This method generateMaximalArray() will be used to generate the Maximal Array which represents the pixels with help of index numbers of the corresponding Leaves.
* @param struct Quadtree* tree
* @date 07/08/2019
*/
void generateMaximalArray(struct Quadtree* tree){
	if (tree==NULL){
		printf("Quadtree not given.\n");
	}
	FILE* input_file=fopen("../../Resources/L2_P2_inputsample1.txt","r");
	if (input_file==NULL){
		printf("Unable to open input file.\n");
	}
	int buffer[65536];
	int b=0;
	while(fscanf(input_file,"%d",&buffer[b])!=EOF){
		b++;
	}
	int size=1;
	int tempsize=(int)sqrt((double)b);
	while(size<tempsize){
		size=size*2;
	}
	tree->size_of_array=size;
	int tsize=size*size;
	int storage[tsize];
	for(int i=0;i<size;i++){
		if (i>=size-tempsize){
			for(int j=0;j<size;j++){
				if (j>=size-tempsize){
					storage[i*size+j]=buffer[(i+tempsize-size)*tempsize+(j+tempsize-size)];  //Transforming the input to an array of suitable size
				}
				else
				{
					storage[i*size+j]=0;
				}
			}
		}
		else
		{
			for (int j=0;j<size;j++){
				storage[i*size+j]=0;
			}
		}
	}
	// for (int i=0;i<tree->size_of_array;i++){
	// 			for (int j=0;j<tree->size_of_array;j++){
	// 				printf("%d\t", storage[(i*tree->size_of_array)+j]);
	// 			}
	// 			printf("\n\n");
	// 		}
	tree->MaximalArray=(int*)malloc(tsize*sizeof(int));
	check(tree,tree->root,storage);
}
/**
* This method printMaximalArray() will be used to print the Maximal Array.
* @param struct Quadtree* tree
* @date 07/08/2019
*/
void printMaximalArray(struct Quadtree* tree){
	if (tree==NULL)
		printf("Quadtree pointer not given properly.\n");
	else{
		if (tree->no_of_nodes==0)
			printf("Nothing to print.\n");
		else{
			printf("The MaximalArray is:\n\n");
			for (int i=0;i<tree->size_of_array;i++){
				for (int j=0;j<tree->size_of_array;j++){
					printf("%d\t", tree->MaximalArray[(i*tree->size_of_array)+j]);
				}
				printf("\n\n");
			}
		}
	}
}
/**
* This method printLeaf() will be used to print the index no,bit value and the level of the given Leaf and its subordinates.
* @param struct Leaf* leaf
* @date 07/08/2019
*/
void printLeaf(struct Leaf* leaf){
	if (leaf->index==-1){
		printLeaf(leaf->branch1);
		printLeaf(leaf->branch2);
		printLeaf(leaf->branch3);
		printLeaf(leaf->branch4);
	}
	else
	{
		printf("(%d,%d,%d)\n",leaf->index,leaf->bit_value,leaf->level );
	}
}
/**
* This method printQuadtree() will be used to print the whole Quad tree as a formatted output.
* @param struct Quadtree* tree
* @date 07/08/2019
*/
void printQuadtree(struct Quadtree* tree){
	printf("The Quadtree representation is as follows:\n\n");
	printLeaf(tree->root);
}

int main(int argc, char const *argv[])
{
	//Driver program
	struct Quadtree* tree=createQuadtree();
	generateMaximalArray(tree);
	printMaximalArray(tree);
	printQuadtree(tree);
	return 0;
}