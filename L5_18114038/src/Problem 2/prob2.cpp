/**
* @file prob2.cpp
* @brief This Cpp file is a program used to find MST of a graph using Kruskal's algorithm.
*
* @author Prathamesh Katkar
*
* @date 02/10/2019
*/
#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;
/**
* This class represents one Node in the graph.
* @date 02/10/2019
*/
class Node
{
public:
    int rank;
    char name;
    Node *parent;
};
/**
* This method createNode() will be used to create a graph Node.
* @param char name
* @date 02/10/2019
*/
Node *createNode(char name)
{
    Node *node = new Node();
    node->rank = 0;
    node->parent = node;
    node->name = name;
    return node;
}
/**
* This class represents all the nodes in the graph.
* @date 02/10/2019
*/
class NodeArray
{
public:
    int front, rear;
    unsigned int size, capacity;
    Node **array;
};
/**
* This method createNodeArray() will be used to create an array of Nodes.
* @param unsigned int capacity
* @date 02/10/2019
*/
NodeArray *createNodeArray(unsigned int capacity)
{
    NodeArray *list = new NodeArray();
    list->capacity = capacity;
    list->front = -1;
    list->rear = -1;
    list->size = 0;
    list->array = (Node **)malloc(list->capacity * sizeof(Node *));
    if (list == NULL)
    {
        printf("Memory allocation error.\n");
    }
    return list;
}
/**
* This method printNodeArray() will be used to print the array of Nodes.
* @param NodeArray *list
* @date 02/10/2019
*/
void printNodeArray(NodeArray *list)
{
    if (list->size == 0)
    {
        printf("NodeArray is empty\n");
    }
    else
    {
        for (int i = 0; i < (list->size); i++)
        {
            cout << list->array[((list->front + i) % list->capacity)]->name << " ";
        }
        cout << "" << endl;
    }
}
/**
* This method reallocate() will be used to resize the array of Nodes.
* @param NodeArray *list
* @date 02/10/2019
*/
NodeArray *reallocate(NodeArray *list)
{
    int initial = list->capacity;
    if (initial == 0)
    {
        list->array = (Node **)realloc(list->array, sizeof(Node *));
        list->capacity = 1;
        return list;
    }
    list->array = (Node **)realloc(list->array, 2 * initial * sizeof(Node *));
    list->capacity = 2 * initial;
    if (list->array == NULL)
        printf("Memory reallocation error.\n");
    return list;
}
/**
* This method isFull() will be used to check if the NodeArray is full.
* @param NodeArray *list
* @date 02/10/2019
*/
int isFull(NodeArray *list)
{
    return (list->size == list->capacity);
}
/**
* This method insertNode() will be used to insert a Node in NodeArray.
* @param NodeArray *list, char name
* @date 02/10/2019
*/
Node *insertNode(NodeArray *list, char name)
{
    Node *parameter = createNode(name);
    if (isFull(list) == 0)
    {
        if (list->size == 0)
        {
            list->front = 0;
            list->rear = 0;
            list->size = 1;
            list->array[0] = parameter;
            return parameter;
        }
        else
        {
            list->rear = (list->rear + 1) % list->capacity;
            list->size = list->size + 1;
            list->array[list->rear] = parameter;
            return parameter;
        }
    }
    else
    {
        list = reallocate(list);
        parameter = insertNode(list, name);
        return parameter;
    }
}
/**
* This class represents one Edge in the graph.
* @date 02/10/2019
*/
class Edge
{
public:
    Node *first;
    Node *second;
    bool accepted;
    int weight;
    Edge *next;
};
/**
* This method createEdge() will be used to create an Edge.
* @param NodeArray *list, char firstName, char secondName, int weight
* @date 02/10/2019
*/
Edge *createEdge(NodeArray *list, char firstName, char secondName, int weight)
{
    Edge *edge = new Edge();
    bool check = true;
    for (int i = 0; i < (list->size); i++)
    {
        if (list->array[((list->front + i) % list->capacity)]->name == firstName)
        {
            check = false;
            edge->first = list->array[((list->front + i) % list->capacity)];
        }
    }
    if (check)
    {
        edge->first = insertNode(list, firstName);
    }
    check = true;
    for (int i = 0; i < (list->size); i++)
    {
        if (list->array[((list->front + i) % list->capacity)]->name == secondName)
        {
            check = false;
            edge->second = list->array[((list->front + i) % list->capacity)];
        }
    }
    if (check)
    {
        edge->second = insertNode(list, secondName);
    }
    edge->weight = weight;
    edge->next = nullptr;
    edge->accepted = false;
    return edge;
}
/**
* This class represents all the Edges in the graph.
* @date 02/10/2019
*/
class EdgeArray
{
public:
    Edge *root;
    int no_of_edges;
};
/**
* This method createEdgeArray() will be used to create an EdgeArray.
* @param NodeArray *list, char firstName, char secondName, int weight
* @date 02/10/2019
*/
EdgeArray *createEdgeArray(NodeArray *list, char firstName, char secondName, int weight)
{
    EdgeArray *edgeArray = new EdgeArray();
    edgeArray->root = createEdge(list, firstName, secondName, weight);
    edgeArray->no_of_edges = 1;
    return edgeArray;
}
/**
* This method insertEdge() will be used to insert an Edge in EdgeArray.
* @param EdgeArray *edgeArray, NodeArray *list, char firstName, char secondName, int w
* @date 02/10/2019
*/
EdgeArray *insertEdge(EdgeArray *edgeArray, NodeArray *list, char firstName, char secondName, int w)
{
    if (edgeArray == nullptr)
    {
        edgeArray = createEdgeArray(list, firstName, secondName, w);
        return edgeArray;
    }
    else
    {
        Edge *temp = edgeArray->root;
        Edge *edge = createEdge(list, firstName, secondName, w);
        if ((temp->weight) > w)
        {
            edge->next = temp;
            edgeArray->root = edge;
        }
        else
        {
            while (true)
            {
                if (temp->next == NULL)
                    break;
                else if (temp->next->weight <= w)
                    temp = temp->next;
                else
                    break;
            }
            if (temp->next != NULL)
                edge->next = temp->next;
            temp->next = edge;
        }
        edgeArray->no_of_edges++;
        return edgeArray;
    }
}
/**
* This class represents the graph.
* @date 02/10/2019
*/
class Graph
{
public:
    EdgeArray *edgeArray;
    NodeArray *list;
    int min_MST_weight;
};
/**
* This method createGraph() will be used to generate a Graph.
* @param 
* @date 02/10/2019
*/
Graph *createGraph()
{
    Graph *graph = new Graph();
    graph->list = createNodeArray(0);
    graph->edgeArray = nullptr;
    graph->min_MST_weight = 0;
    FILE *file_pointer = fopen("../../Resources/2019_CSN_261_L5_P2.csv", "r");
    if (file_pointer == nullptr)
    {
        printf("Error in opening file.\n");
        return NULL;
    }
    char trash[1024];
    while (fgets(trash, 1024, file_pointer))
    {
        char *firstName = strtok(trash, ",");
        char *secondName = strtok(NULL, ",");
        char *w = strtok(NULL, ",");
        graph->edgeArray = insertEdge(graph->edgeArray, graph->list, firstName[0], secondName[0], atoi(w));
    }
    return graph;
}
/**
* This method printEdgeArray() will be used to print the EdgeARray.
* @param EdgeArray *edgeArray
* @date 02/10/2019
*/
void printEdgeArray(EdgeArray *edgeArray)
{
    if (edgeArray == nullptr)
    {
        cout << "No edges present" << endl;
    }
    else
    {
        if (edgeArray->root == nullptr)
            cout << "Root edge absent" << endl;
        Edge *temp = edgeArray->root;
        while (true)
        {
            cout << temp->first->name << " " << temp->second->name << " " << temp->weight << endl;
            if (temp->next == nullptr)
                break;
            temp = temp->next;
        }
    }
}
/**
* This method find() will be used to find the parent of a Node.
* @param Node *node
* @date 02/10/2019
*/
Node *find(Node *node)
{
    if (node->parent != node)
        node->parent = find(node->parent);
    return node->parent;
}
/**
* This method connectEdge() will be used to connect two Nodes.
* @param Node *firstNode, Node *secondNode
* @date 02/10/2019
*/
void connectEdge(Node *firstNode, Node *secondNode)
{
    Node *firstParent = find(firstNode);
    Node *secondParent = find(secondNode);
    if ((firstParent->rank) < (secondParent->rank))
        firstParent->parent = secondParent;
    else if ((firstParent->rank) > (secondParent->rank))
    {
        secondParent->parent = firstParent;
    }
    else
    {
        secondParent->parent = firstParent;
        firstParent->rank++;
    }
}
/**
* This method generateMST() will be used to generate the MST.
* @param Graph *graph
* @date 02/10/2019
*/
void generateMST(Graph *graph)
{
    int maxSize = graph->list->size;
    Edge *temp = graph->edgeArray->root;
    int edgeCount = 0;
    while (edgeCount < maxSize - 1)
    {
        if (temp == nullptr)
        {
            cout << "Edge is empty" << endl;
            break;
        }
        Node *firstParent = find(temp->first);
        Node *secondParent = find(temp->second);
        if (firstParent->name != secondParent->name)
        {
            edgeCount++;
            temp->accepted = true;
            graph->min_MST_weight += temp->weight;
            connectEdge(temp->first, temp->second);
        }
        if (temp->next == nullptr)
            break;
        temp = temp->next;
    }
}
/**
* This method printMST() will be used to print the MST.
* @param Graph *graph
* @date 02/10/2019
*/
void printMST(Graph *graph)
{
    if (graph->min_MST_weight == 0)
    {
        cout << "Generate the MST first" << endl;
    }
    else
    {
        Edge *temp = graph->edgeArray->root;
        cout << "The total edge weight of the MST is : " << graph->min_MST_weight << "\n"
             << endl;
        cout << "Node1\tNode2\tWeight" << endl;
        while (true)
        {
            if (temp == nullptr)
            {
                cout << "Empty edge" << endl;
                break;
            }
            if (temp->accepted)
            {
                cout << temp->first->name << "\t" << temp->second->name << "\t" << temp->weight << endl;
            }
            if (temp->next == nullptr)
                break;
            temp = temp->next;
        }
    }
}
/**
* This method generateDotFile() will be used to generate the Dot file of the MST.
* @param Graph *graph
* @date 02/10/2019
*/
void generateDotFile(Graph *graph)
{
    system("touch mst.dot");
    ofstream output_file;
    output_file.open("mst.dot");
    output_file << "graph MST {" << endl;

    if (graph->min_MST_weight == 0)
    {
        cout << "Generate the MST first" << endl;
    }
    else
    {
        Edge *temp = graph->edgeArray->root;
        while (true)
        {
            if (temp == nullptr)
            {
                cout << "Empty edge" << endl;
                break;
            }
            if (temp->accepted)
            {
                output_file << temp->first->name << "--" << temp->second->name << "[label=\"" << temp->weight << "\",weight=\"" << temp->weight << "\"];" << endl;
            }
            if (temp->next == nullptr)
                break;
            temp = temp->next;
        }
    }
    output_file << "}" << endl;
    output_file.close();
    system("neato -Tpng mst.dot -o mst.png");
    system("neato -Tpdf mst.dot -o mst.pdf");
}
int main(int argc, char const *argv[])
{
    //Driver program
    Graph *graph = createGraph();
    // printNodeArray(graph->list);
    // printEdgeArray(graph->edgeArray);
    generateMST(graph);
    printMST(graph);
    generateDotFile(graph);
    return 0;
}
