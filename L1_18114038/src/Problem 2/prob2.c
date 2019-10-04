/**
* @file prob2.c
* @brief This C file is a program to manage the data of students with the help of data structures.
*
* @author Prathamesh Katkar
*
* @date 31/07/2019
*/

#include <stdio.h>
#include <stdlib.h>

typedef enum {Front,Rear} side; //defined enum side to represent the two sides of the deque
/**
* This struct represents the deque.
* @date 31/7/2019
*/
struct Deque
{
	int front,rear;
	unsigned int size,capacity;
	int* array;
};
/**
* This method createDeque() will be used to create the Deque.
* @param unsigned int capacity
* @date 31/7/2019
*/
struct Deque* createDeque(unsigned int capacity)
{
	struct Deque* deque =(struct Deque*)malloc(sizeof(struct Deque));
	deque->capacity = capacity;
	deque->front=-1;
	deque->rear=-1;
	deque->size=0;
	deque->array=(int*)malloc(deque->capacity*sizeof(int)); //dynamic allocation
	if (deque==NULL)
	{
		printf("Memory allocation error.\n");
	}
	return deque;

}
/**
* This method printDeque() will be used to print the entries of the deque.
* @param struct Deque* deque
* @date 31/7/2019
*/
void printDeque(struct Deque* deque)
{
	if(deque->size==0){
		printf("Deque is empty\n");
	}
	else
	{
		for (int i=0;i<(deque->size);i++)
			{
				printf("%d ", deque->array[((deque->front+i)%deque->capacity)]);
			}
			printf("\n");
	}
}
/**
* This method reallocate() will be used to change the size of the deque.
* @param struct Deque* deque
* @date 31/7/2019
*/
struct Deque* reallocate(struct Deque* deque)
{
	int mid=(deque->capacity+1)/2;
	int initial=deque->capacity;
	if (initial==0)
	{
		deque->array=(int*)realloc(deque->array,sizeof(int));
		deque->capacity=1;
		return deque;
	}
	deque->array=(int*)realloc(deque->array,2*initial*sizeof(int));
	deque->capacity=2*initial;
	if(deque->array==NULL)
	{
		printf("Memory reallocation error.\n");
	}
	if ((deque->rear)>=(deque->front))
	{
		return deque;
	}
	else
	{
		if ((deque->front)<=mid)
		{
			for (int i=0;i<=(deque->rear);i++)
			{
				deque->array[initial+i]=deque->array[i]; //rearranging the deque after increasing size
			}
			deque->rear=deque->rear+initial;
			return deque;
		}
		else
		{
			for (int i=deque->front;i<initial;i++)
			{
				deque->array[initial+i]=deque->array[i]; //rearranging the deque after increasing size
			}
			deque->front=deque->front+initial;
			return deque;
		}
	}
}
/**
* This method isFull() will be used to check if deque is full.
* @param struct Deque* deque
* @date 31/7/2019
*/
int isFull(struct Deque* deque)
{
	return (deque->size==deque->capacity);
}
/**
* This method insert() will be used to insert entries into the deque.
* @param struct Deque* deque, side s,int parameter
* @date 31/7/2019
*/
void insert(struct Deque* deque, side s,int parameter)
{

	if (isFull(deque)==0)
	{
		if (deque->size==0)
		{
			deque->front=0;
			deque->rear=0;
			deque->size=1;
			deque->array[0]=parameter;
		}
		else if(s==Front) //inserting data from Front side
		{
			deque->front=(deque->capacity+deque->front-1)%deque->capacity;
			deque->size=deque->size+1;
			deque->array[deque->front]=parameter;
		}
		else if(s==Rear) //inserting data from Rear side
		{
			deque->rear=(deque->rear+1)%deque->capacity;
			deque->size=deque->size+1;
			deque->array[deque->rear]=parameter;
		}
		else
		{
			;
		}
	}
	else
	{
		deque=reallocate(deque);
		insert(deque,s,parameter);
	}
}
/**
* This method delete() will be used to delete entries from the deque.
* @param struct Deque* deque, side s
* @date 31/7/2019
*/
void delete(struct Deque* deque,side s)
{
	if (deque->size==0)
	{
		printf("Deque is already empty.\n");
	}
	else if (deque->size==1)
	{
		deque->front=-1;
		deque->rear=-1;
		deque->size=0;
		deque->capacity=0;
		free(deque->array);
	}
	else
	{
		if (s==Front) //Deleting from front side
		{
			deque->front=(deque->front+1)%(deque->capacity);
			deque->size=deque->size-1;			
		}
		else if (s==Rear) //Deleting from rear side
		{
			deque->rear=(deque->capacity+deque->rear-1)%(deque->capacity);
			deque->size=deque->size-1;
		}
		else
		{
			;
		}

		if ((2*deque->size)<=deque->capacity)  //reducing size of deque
		{
			int* tmp=(int*)malloc((deque->size)*sizeof(int));
			for (int i=0;i<(deque->size);i++)
			{
				tmp[i]=deque->array[((deque->front+i)%(deque->capacity))];
			}
			free(deque->array);
			deque->array=tmp;
			deque->front=0;
			deque->rear=deque->size-1;
			deque->capacity=deque->capacity/2;
		}
	}
}


int main(){
	//Driver program
	printf("Enter the initial capacity of deque.\n");
	unsigned int initial_capacity;
	scanf("%d",&initial_capacity);
	printf("\n");
	struct Deque* deque=createDeque(initial_capacity);
	delete(deque,Rear);
	insert(deque,Rear,15);
	printf("Deque after rear insertion:\n");
	printDeque(deque);
	printf("\n");
	insert(deque,Front,21);
	printf("Deque after front insertion:\n");
	printDeque(deque);
	printf("\n");
	insert(deque,Rear,19);
	printf("Deque after rear insertion:\n");
	printDeque(deque);
	insert(deque,Rear,41);
	printf("Deque after rear insertion:\n");
	printDeque(deque);
	insert(deque,Front,39);
	printf("Deque after rear insertion:\n");
	printDeque(deque);
	printf("%d\n", deque->size);
	printf("%d\n", deque->capacity);
	printf("\n");
	insert(deque,Front,21);
	printf("Deque after front insertion:\n");
	printDeque(deque);
	printf("\n");
	insert(deque,Rear,19);
	printf("Deque after rear insertion:\n");
	printDeque(deque);
	insert(deque,Rear,41);
	printf("Deque after rear insertion:\n");
	printDeque(deque);
	insert(deque,Front,39);
	printf("Deque after rear insertion:\n");
	printDeque(deque);
	printf("%d\n", deque->size);
	printf("%d\n", deque->capacity);
	delete(deque,Front);
	printf("Deque after front deletion:\n");
	printDeque(deque);
	printf("%d\n", deque->size);
	printf("%d\n", deque->capacity);
	delete(deque,Front);
	printf("%d\n", deque->size);
	printf("%d\n", deque->capacity);
	return 0;
}