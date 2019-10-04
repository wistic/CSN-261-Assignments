/**
* @file prob1.c
* @brief This C file is a program to manage the data of students with the help of data structures.
*
* @author Prathamesh Katkar
*
* @date 31/07/2019
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

typedef enum {Name,DOB,Address,Roll_no,Phone_no} search_type; //defined search_type to use for recognizing which data to process
typedef enum {Basic, All} details; //defined details to decide which entries are to be printed
/**
* This struct represents one student.
* @date 31/7/2019
*/
struct Node
{
	unsigned int roll_no;
	char name[50];
	char date[50];
	char address[250];
	unsigned long int phone_no;
	struct Node* next;
	struct Node* previous;
};
/**
* This struct manages the deleted entries.
* @date 31/7/2019
*/
struct Queue
{
	int front;
	int rear;
	unsigned int size,capacity;
	int* array;
};
/**
* This struct is the Student Management System.
* @date 31/7/2019
*/
struct SMS
{
	struct Node* head;
	int no_of_nodes;
	struct Queue* queue;
};
/**
* This method createQueue() will be used to create the Queue for managing deleted entries.
* @param unsigned int capacity
* @date 31/7/2019
*/
struct Queue* createQueue(unsigned int capacity){
	struct Queue* queue=(struct Queue*)malloc(sizeof(struct Queue));
	queue->front=-1;
	queue->rear=-1;
	queue->size=0;
	queue->capacity=capacity;
	int* array=(int*)malloc(capacity*sizeof(int));
	queue->array=array;
	return queue;
}
/**
* This method createSMS() will be used to create the Student Management System.
* @param unsigned int capacity
* @date 31/7/2019
*/
struct SMS* createSMS(unsigned int capacity){
	struct SMS* sms=(struct SMS*)malloc(sizeof(struct SMS));
	sms->head=NULL;
	sms->no_of_nodes=0;
	sms->queue=(struct Queue*)createQueue(capacity);
	return sms;

}
/**
* This method createSMS() will be used to create a node in the Student Management System.
* @param struct SMS* sms, int entry_no
* @date 31/7/2019
*/

struct Node* createNode(struct SMS* sms,int entry_no)
{
	FILE* file_pointer=fopen("../../Resources/StudentData.csv","r"); // Creates a pointer to the CSV file
	if (file_pointer==NULL)
	{
		printf("Error in opening file.\n" );
		return NULL;
	}
	struct Node* node=(struct Node*)malloc(sizeof(struct Node));
	if (sms->queue==NULL)
	{
		printf("Queue unusedRollNo doesn't exist.\n");
		return NULL;
	}
	char trash[1024];
	entry_no++;
	while(entry_no--!=0){
		fgets(trash,1024,file_pointer); //Fetched a line
	}
	char* entry=strtok(trash,",");
	char* varname=strtok(NULL,","); //Getting the corresponding values from the fetched line
	strcpy(node->name,varname);
	char* vardate=strtok(NULL,",");
	strcpy(node->date,vardate);
	char* varaddress=strtok(NULL,"\"");
	strcpy(node->address,varaddress);
	char* phone=strtok(NULL,",");
	node->phone_no=strtol(phone,NULL,10);
	//checking the queue
	if (sms->queue->size>1)
	{
	node->roll_no=sms->queue->array[sms->queue->front];
	sms->queue->front=(sms->queue->front+1)%sms->queue->capacity;
	sms->queue->size=sms->queue->size-1;
	node->previous=NULL;
	node->next=NULL;
	}
	else if (sms->queue->size==0){
	node->roll_no=sms->no_of_nodes+101;
	node->previous=NULL;
	node->next=NULL;
	}
	else if (sms->queue->size==1){
	node->roll_no=sms->queue->array[sms->queue->front];
	sms->queue->front=-1;
	sms->queue->rear=-1;
	sms->queue->size=sms->queue->size-1;
	node->previous=NULL;
	node->next=NULL;
	}
	fclose(file_pointer); //Closed the file pointer
	return node;
}
/**
* This method partition() will be used for partitioning the array for QuickSort.
* @param struct node arr[], int low, int high,search_type st
* @date 31/7/2019
*/
int partition (struct Node* arr[], int low, int high,search_type st) 
{ 
    struct Node* pivot = arr[high];    // pivot 
    int i = (low - 1);  // Index of smaller element 
  	if (st==Roll_no){
	    for (int j = low; j <= high- 1; j++) 
	        { 
	        // If current element is smaller than or 
	        // equal to pivot 
	        if ((arr[j]->roll_no) <= (pivot->roll_no)) 
	        { 
	            i++;    // increment index of smaller element 
	            struct Node* data=arr[i];
	            arr[i]=arr[j];
	            arr[j]=data;
	        } 
	    } 
	}
	else if (st==Name){
		for (int j = low; j <= high- 1; j++) 
	    { 
	        // If current element is smaller than or 
	        // equal to pivot 
	        if (strcmp(arr[j]->name,pivot->name)<=0) 
	        { 
	            i++;    // increment index of smaller element 
	            struct Node* data=arr[i];
	            arr[i]=arr[j];
	            arr[j]=data; 
	        } 
	    }
	}
	struct Node* vardata=arr[high];
	arr[high]=arr[i+1];
	arr[i+1]=vardata;
    return (i + 1); 
} 
/**
* This method quickSort() will be used for sorting the array by Quicksort algorithm.
* @param struct Node* arr[], int low, int high,search_type st
* @date 31/7/2019
*/
void quickSort(struct Node* arr[], int low, int high,search_type st) 
{ 
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
           at right place */
        int pi = partition(arr, low, high,st); 

  
        // Separately sort elements before 
        // partition and after partition 
        quickSort(arr, low, pi - 1,st); 
        quickSort(arr, pi + 1, high,st); 
    } 
}
/**
* This method sort() will be used for sorting the array.
* @param struct SMS* sms,search_type st
* @date 31/7/2019
*/
void sort(struct SMS* sms,search_type st){
	if (sms->head==NULL){
		printf("Nothing to sort.\n");
		return;
	}
	struct Node* temp=sms->head;
	struct Node* pointer_array[sms->no_of_nodes];
	int i=0;
	while(i<(sms->no_of_nodes)){
		pointer_array[i]=temp;
		temp=temp->next;
		i++;
	}
	if (st==Roll_no){
		quickSort(pointer_array,0,sms->no_of_nodes-1,st); //Sort by Roll no
	}
	else if (st==Name){
		quickSort(pointer_array,0,sms->no_of_nodes-1,st); //Sort by Name
	}
	sms->head=pointer_array[0];
	int var=0;
	while(var<(sms->no_of_nodes)){
		pointer_array[var]->next=pointer_array[(var+1)%sms->no_of_nodes];
		pointer_array[var]->previous=pointer_array[(var-1+sms->no_of_nodes)%sms->no_of_nodes];
		var++;
	}
}
/**
* This method insert() will be used for inserting a node in the Student Management System.
* @param struct SMS* sms,int entry_no
* @date 31/7/2019
*/
void insert(struct SMS* sms,int entry_no)
{
	struct Node* node=(struct Node*)createNode(sms,entry_no);
	if (node==NULL)
	{
		printf("Error in creating node.\n");
		return;
	}
	if (sms->no_of_nodes==0)
	{
		sms->head=node;
		node->next=node;
		node->previous=node;
	}
	else
	{
		node->previous=sms->head->previous; //rearranging the pointers
		node->previous->next=node;
		node->next=sms->head;
		sms->head->previous=node;

	}
	sms->no_of_nodes=sms->no_of_nodes+1;
	sort(sms,Roll_no);
	return;

}
/**
* This method delete() will be used for deleting a node from the Student Management System.
* @param struct SMS* sms,int roll_no
* @date 31/7/2019
*/
void delete(struct SMS* sms,int roll_no){
	if (sms->head==NULL){
		printf("Nothing to delete.\n");
		return;
	}
	if (sms->queue==NULL){
		printf("Queue doesn't exist.");
	}
	struct Node* temp=sms->head;
	while((temp->roll_no!=roll_no) && (temp->next!=sms->head))
	{
		temp=temp->next;
	}
	if ((temp->roll_no!=roll_no) && (temp->next==sms->head))
	{
		printf("Roll no doesn't exist.\n");
		return;
	}
	if (sms->queue->size==0){
		sms->queue->size=1;
		sms->queue->front=0;
		sms->queue->rear=0;
		if (sms->queue->array==NULL)
			printf("Queue is defective.\n");
		sms->queue->array[sms->queue->rear]=temp->roll_no;
	}
	else
	{
		sms->queue->size=sms->queue->size+1;
		sms->queue->rear=(sms->queue->rear+1)%sms->queue->capacity;
		sms->queue->array[sms->queue->rear]=temp->roll_no;
	}
	if (temp==sms->head){
		sms->head=sms->head->next;
	}
	temp->next->previous=temp->previous;
	temp->previous->next=temp->next;
	free(temp);
	sms->no_of_nodes=sms->no_of_nodes-1;
	return;
}
/**
* This method search() will be used for searching a node in the Student Management System with given parameters.
* @param struct SMS* sms,search_type st and the value of the parameter
* @date 31/7/2019
*/
int search(struct SMS* sms,search_type st,...) //This is a variadic function
{
	if (sms->head==NULL){
		printf("Nothing to search in.\n");
		return 0;
	}
	struct Node* temp=sms->head;
	va_list listPointer;
	va_start(listPointer,st);
	if (st==Roll_no) //Search by Roll no
	{
		int roll_no=va_arg( listPointer, int );
		while((temp->roll_no!=roll_no) && (temp->next!=sms->head))
		{
			temp=temp->next;
		}
		if ((temp->roll_no!=roll_no) && (temp->next==sms->head))
		{
			printf("Roll no doesn't exist.\n");
			return 0;
		}
		return temp->roll_no; 
	}
	else if (st==Name){//Search by Name
		const char* varname=va_arg( listPointer, const char* );
		while((strcmp(temp->name,varname)!=0) && (temp->next!=sms->head))
		{
			temp=temp->next;
		}
		if ((strcmp(temp->name,varname)!=0) && (temp->next==sms->head))
		{
			printf("Roll no doesn't exist.\n");
			return 0;
		}
		return temp->roll_no;
	}
	else if (st==DOB){  //Search by DOB
		const char* vardate=va_arg( listPointer, const char* );
		while((strcmp(temp->date,vardate)!=0) && (temp->next!=sms->head))
		{
			temp=temp->next;
		}
		if ((strcmp(temp->name,vardate)!=0) && (temp->next==sms->head))
		{
			printf("Roll no doesn't exist.\n");
			return 0;
		}
		return temp->roll_no;
	}
	else if (st==Address){  //Search by address
		const char* varaddress=va_arg( listPointer, const char* );
		while((strcmp(temp->address,varaddress)!=0) && (temp->next!=sms->head))
		{
			temp=temp->next;
		}
		if ((strcmp(temp->name,varaddress)!=0) && (temp->next==sms->head))
		{
			printf("Roll no doesn't exist.\n");
			return 0;
		}
		return temp->roll_no;
	}
	else if (st==Phone_no){  //Search by Phone no
		unsigned long int phone=va_arg( listPointer, unsigned long int );
		while((temp->phone_no!=phone) && (temp->next!=sms->head))
		{
			temp=temp->next;
		}
		if ((temp->phone_no!=phone) && (temp->next==sms->head))
		{
			printf("Roll no doesn't exist.\n");
			return 0;
		}
		return temp->roll_no;
	}
	va_end(listPointer);

}
/**
* This method modify() will be used for modifying the value of a node in the Student Management System with given parameters.
* @param struct SMS* sms,int roll_no,search_type st and the value of the parameter
* @date 31/7/2019
*/
void modify(struct SMS* sms,int roll_no,search_type st,...){
	if (sms->head==NULL){
		printf("Nothing to modify.\n");
		return;
	}
	struct Node* temp=sms->head;
	while((temp->roll_no!=roll_no) && (temp->next!=sms->head))
	{
		temp=temp->next;
	}
	if ((temp->roll_no!=roll_no) && (temp->next==sms->head))
	{
		printf("Roll no doesn't exist.\n");
		return;
	}
	va_list listPointer;
	va_start(listPointer,st);
	if (st==Name){ //modify Name
		char* varname=va_arg( listPointer,char* );
		strcpy(temp->name,varname);
	}
	else if (st==DOB){ //modify DOB
		char* vardate=va_arg( listPointer,char* );
		strcpy(temp->date,vardate);
	}
	else if (st==Address){ //modify Address
		char* varaddress=va_arg( listPointer,char* );
		strcpy(temp->address,varaddress);
	}
	else if (st==Phone_no){ //modify Phone no
		unsigned long int phone=va_arg( listPointer, unsigned long int );
		temp->phone_no=phone;	
	}
	va_end(listPointer);
}
/**
* This method print() will be used for printing the entries of the Student Management System with given parameters.
* @param struct SMS* sms,details dt
* @date 31/7/2019
*/
void print(struct SMS* sms,details dt){
	if (sms->head==NULL){
		printf("Nothing to print.\n");
		return;
	}
	struct Node* temp=sms->head;
	if (sms->no_of_nodes==1){
		if (dt==Basic){
			printf("Roll_no = %d\nName = %s\nDate of Birth = %s\n", sms->head->roll_no,sms->head->name,sms->head->date);
		}
		else if (dt==All){
			printf("Roll_no = %d\nName = %s\nDate of Birth = %s\nAddress = %s\nPhone no. = %ld\n", sms->head->roll_no,sms->head->name,sms->head->date,sms->head->address,sms->head->phone_no);
		}
		return;
	}
	else
	{
		while(temp->next!=sms->head){
			if (dt==Basic){
			printf("Roll_no = %d\nName = %s\nDate of Birth = %s\n", temp->roll_no,temp->name,temp->date);
			}
			else if (dt==All){
				printf("Roll_no = %d\nName = %s\nDate of Birth = %s\nAddress = %s\nPhone no. = %ld\n", temp->roll_no,temp->name,temp->date,temp->address,temp->phone_no);
			}
			temp=temp->next;
		}
		if (dt==Basic){
			printf("Roll_no = %d\nName = %s\nDate of Birth = %s\n", temp->roll_no,temp->name,temp->date);
		}
		else if (dt==All){
			printf("Roll_no = %d\nName = %s\nDate of Birth = %s\nAddress = %s\nPhone no. = %ld\n", temp->roll_no,temp->name,temp->date,temp->address,temp->phone_no);
		}
		return;
	}
}

int main(int argc, char const *argv[])
{
	//Driver program
	struct SMS* sms=(struct SMS*)createSMS(15);
	delete(sms,108); //delete (roll number 108) - delete the student node with roll number 108 
	print(sms,Basic);
	printf("\n");
	insert(sms,1);  //insert - insert first student data from the “StudentData.xlsx” file (Row2) 
	print(sms,Basic);
	printf("\n");
	insert(sms,2); //insert - insert second student data from the “StudentData.xlsx” file (Row3) 
	print(sms,Basic);
	printf("\n");
	insert(sms,3);  // insert - insert 3rd student data from the “StudentData.xlsx” file (Row4)
	print(sms,Basic);
	printf("\n");
	insert(sms,4); //insert - insert 4th student data from the “StudentData.xlsx” file (Row5) 
	print(sms,Basic);
	printf("\n");
	delete(sms,102); //delete (roll number 102) - delete the student node with roll number 102 
	print(sms,Basic);
	printf("\n");
	delete(sms,101); //delete (roll number 101) - delete the student node with roll number 101 
	print(sms,Basic);
	printf("\n");
	insert(sms,5);  //insert - insert 5th student data from the “StudentData.xlsx” file (Row6) 
	print(sms,Basic);
	printf("\n");
	insert(sms,6);  //insert - insert 6th student data from the “StudentData.xlsx” file (Row7
	print(sms,Basic);
	printf("\n");
	insert(sms,7);  //insert - insert 7th student data from the “StudentData.xlsx” file (Row8) 
	print(sms,Basic); //. print - print the linked list with the roll number, name and D.O.B 
	printf("\n");
	sort(sms,Name);  //  sort (name) - sort the name according to student names 
	print(sms,All); // print - print the linked list with the roll number, name and D.O.B 
	printf("\n");
	modify(sms,103,Phone_no,9876543210);  //. modify (roll number 103) - modify the student node having roll number 103 
	print(sms,All);
	printf("\n");
	printf("%d\n",search(sms,DOB,"17 Sep 95"));
	print(sms,All); // print - print the linked list with all the records for each student 
	return 0;
}

