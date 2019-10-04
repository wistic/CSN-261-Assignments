/**
 * @file prob3.cpp
 * @author Prathamesh Katkar  
 * @date 02/10/2019
 */
#include <limits.h> 
#include <stdlib.h> 
#include <iostream>
#include <vector>
#include <fstream>
#include <bits/stdc++.h> 
#include <time.h>
#include <string>
#include <sstream>

using namespace std;

/**
 * @brief This keeps the note of destination and weight of particular node
  * @date 02/10/2019
 */
struct AdjListNode { 
	int dest; 
	int weight; 
	struct AdjListNode* next; 
}; 

struct AdjList { 
	struct AdjListNode* head;
}; 

/**
 * @brief This is single Graph node
  * @date 02/10/2019 
 */
struct Graph { 
	int V; 
	struct AdjList* array; 
}; 

/**
 * @brief This function creates the edge between two nodes with its weight
 * @date 02/10/2019
 * @param dest 
 * @param weight 
 * @return struct AdjListNode* 
 */
struct AdjListNode* newAdjListNode(int dest, int weight) 
{ 
	struct AdjListNode* newNode = (struct AdjListNode*)malloc(sizeof(struct AdjListNode)); 
	newNode->dest = dest; 
	newNode->weight = weight; 
	newNode->next = NULL; 
	return newNode; 
} 

/**
 * @brief Create a Graph object
  * @date 02/10/2019 
 * @param V 
 * @return struct Graph* 
 */
struct Graph* createGraph(int V) 
{ 
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph)); 
	graph->V = V; 

	graph->array = (struct AdjList*)malloc(V * sizeof(struct AdjList)); 

	for (int i = 0; i < V; ++i) 
		graph->array[i].head = NULL; 

	return graph; 
} 

/**
 * @brief This function adds an edge to the graph
  * @date 02/10/2019
 * @param graph 
 * @param src 
 * @param dest 
 * @param weight 
 */
void addEdge(struct Graph* graph, int src, int dest, int weight) 
{ 

	struct AdjListNode* newNode = newAdjListNode(dest, weight); 
	newNode->next = graph->array[src].head; 
	graph->array[src].head = newNode; 

	newNode = newAdjListNode(src, weight); 
	newNode->next = graph->array[dest].head; 
	graph->array[dest].head = newNode; 
} 

/**
 * @brief This is node for min heap
  * @date 02/10/2019
 */
struct MinHeapNode { 
	int v; 
	int key; 
}; 

/**
 * @brief This nodes keeps the parameters for the min heap
 * @date 02/10/2019
 */
struct MinHeap { 
	int size;
	int capacity;
	int* pos;
	struct MinHeapNode** array; 
}; 

/**
 * @brief This node creates the new min heap node
  * @date 02/10/2019
 * @param v 
 * @param key 
 * @return struct MinHeapNode* 
 */
struct MinHeapNode* newMinHeapNode(int v, int key) 
{ 
	struct MinHeapNode* minHeapNode = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode)); 
	minHeapNode->v = v; 
	minHeapNode->key = key; 
	return minHeapNode; 
} 

struct MinHeap* createMinHeap(int capacity) 
{ 
	struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap)); 
	minHeap->pos = (int*)malloc(capacity * sizeof(int)); 
	minHeap->size = 0; 
	minHeap->capacity = capacity; 
	minHeap->array = (struct MinHeapNode**)malloc(capacity * sizeof(struct MinHeapNode*)); 
	return minHeap; 
} 


/**
 * @brief This function swaps the nodes of min heap
 * @date 02/10/2019
 * @param a 
 * @param b 
 */
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) 
{ 
	struct MinHeapNode* t = *a; 
	*a = *b; 
	*b = t; 
} 


/**
 * @brief This functions performs the heapify method
  * @date 02/10/2019
 * @param minHeap 
 * @param idx 
 */
void minHeapify(struct MinHeap* minHeap, int idx) 
{ 
	int smallest, left, right; 
	smallest = idx; 
	left = 2 * idx + 1; 
	right = 2 * idx + 2; 

	if (left < minHeap->size && minHeap->array[left]->key < minHeap->array[smallest]->key) 
		smallest = left; 

	if (right < minHeap->size && minHeap->array[right]->key < minHeap->array[smallest]->key) 
		smallest = right; 

	if (smallest != idx) { 
		
		MinHeapNode* smallestNode = minHeap->array[smallest]; 
		MinHeapNode* idxNode = minHeap->array[idx]; 

		minHeap->pos[smallestNode->v] = idx; 
		minHeap->pos[idxNode->v] = smallest; 

		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]); 

		minHeapify(minHeap, smallest); 
	} 
} 


/**
 * @brief This function checks whether min heap is empty or not
  * @date 02/10/2019
 * @param minHeap 
 * @return int 
 */
int isEmpty(struct MinHeap* minHeap) 
{ 
	return minHeap->size == 0; 
} 


/**
 * @brief This function extracts the minimum from the min heap
  * @date 02/10/2019
 * @param minHeap 
 * @return struct MinHeapNode* 
 */
struct MinHeapNode* extractMin(struct MinHeap* minHeap) 
{ 
	if (isEmpty(minHeap)) 
		return NULL; 

	struct MinHeapNode* root = minHeap->array[0]; 

	struct MinHeapNode* lastNode = minHeap->array[minHeap->size - 1]; 
	minHeap->array[0] = lastNode; 

	minHeap->pos[root->v] = minHeap->size - 1; 
	minHeap->pos[lastNode->v] = 0; 

	--minHeap->size; 
	minHeapify(minHeap, 0); 

	return root; 
} 


/**
 * @brief This function decreases the key from heap
  * @date 02/10/2019
 * @param minHeap , number to be removed, the key
 */
void decreaseKey(struct MinHeap* minHeap, int v, int key) 
{ 
	int i = minHeap->pos[v]; 

	minHeap->array[i]->key = key; 

	while (i && minHeap->array[i]->key < minHeap->array[(i - 1) / 2]->key) { 

		minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2; 
		minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i; 
		swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]); 

		i = (i - 1) / 2; 
	} 
} 


/**
 * @brief This function checks whether the node is in min heap or not
  * @date 02/10/2019
 * @param minHeap 
 * @param v 
 * @return true 
 * @return false 
 */
bool isInMinHeap(struct MinHeap* minHeap, int v) 
{ 
	if (minHeap->pos[v] < minHeap->size) 
		return true; 
	return false; 
} 


/**
 * @brief This function prints the minimum spanning tree using Prim's algorithm
 * @date 02/10/2019 
 * @param node 
 * @param weight 
 * @param n 
 */
void printArr(int node[], int weight[], int n) 
{ 
  string out;
  out = "graph output {\n";

  for (int i = 1; i < n; ++i) {
    char start = (char) (node[i]+65);
    char end = (char) (i+65);
    out += start + string(" -- ") + end + string("[label=\"") + to_string(weight[i]) + string("\"];\n");
    }

  out += "}";

  int k = out.length();
  char char_array_out[k + 1];
  strcpy(char_array_out, out.c_str()); 

  FILE *fptr;
    fptr = fopen("secondgraph.dot","w");

    if(fptr == NULL)
    {
      printf("Error!");   
      exit(1);             
    }

    fprintf(fptr,"%s",char_array_out);
    fclose(fptr);

    int totalweight = 0;
	for (int i = 1; i < n; ++i){
        totalweight += weight[i];
        char start = (char) (node[i]+65);
        char end = (char) (i+65);
        if(node[i] > i){
            cout<<end<<" "<<start<<" "<<weight[i]<<endl;
        }else{
            cout<<start<<" "<<end<<" "<<weight[i]<<endl;
        }
        
    }

    cout<<"Total weight is : "<<totalweight<<endl;
} 

/**
 * @brief This function performs the prim's algorithm
 * @date 02/10/2019
 * @param graph 
 */
void PrimMST(struct Graph* graph) 
{ 
	int V = graph->V;
	int parent[V];
	int key[V];

	struct MinHeap* minHeap = createMinHeap(V); 

	for (int v = 1; v < V; ++v) { 
		parent[v] = -1; 
		key[v] = INT_MAX; 
		minHeap->array[v] = newMinHeapNode(v, key[v]); 
		minHeap->pos[v] = v; 
	} 

	key[0] = 0; 
	minHeap->array[0] = newMinHeapNode(0, key[0]); 
	minHeap->pos[0] = 0; 

	minHeap->size = V; 

	while (!isEmpty(minHeap)) { 

		struct MinHeapNode* minHeapNode = extractMin(minHeap); 
		int u = minHeapNode->v;

		struct AdjListNode* pCrawl = graph->array[u].head; 
		while (pCrawl != NULL) { 
			int v = pCrawl->dest; 

			if (isInMinHeap(minHeap, v) && pCrawl->weight < key[v]) { 
				key[v] = pCrawl->weight; 
				parent[v] = u; 
				decreaseKey(minHeap, v, key[v]); 
			} 
			pCrawl = pCrawl->next; 
		} 
	} 
    cout<<"The final MST obtained is : "<<endl;
	printArr(parent, key, V); 
} 

/**
 * @brief This function takes input from the file and executes different functions to find the MST Tree using Prim's algorithm
 * @date 02/10/2019 
 * @return int 
 */
int main() 
{ 
  clock_t start, end;
  double cpu_time_used;
  start = clock();
  
	int V = 6; 
	struct Graph* graph = createGraph(V); 

    ifstream fin; 
	fin.open("../../Resources/2019_CSN_261_L5_P2.csv"); 
	string line,s;
	vector<string> words;
    getline(fin, line);
	string max="";

    while (fin) {
        vector<string> words;
        stringstream ss(line); 
        string tok;
        while(getline(ss, tok, ',')) {
            words.push_back(tok);
        }
  		s = words[0]+words[1];
  		max = (max>s)?max:(words[0]>words[1]?words[0]:words[1]);
  		

        int start = (int) words[0][0] - 65;
        int end = (int) words[1][0] - 65;
        int weight = stoi(words[2]);

        addEdge(graph, start, end, weight);

		getline(fin, line);
    } 

	PrimMST(graph); 

  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  cout<<"Time Taken : "<<cpu_time_used<<endl;

	return 0; 
} 
