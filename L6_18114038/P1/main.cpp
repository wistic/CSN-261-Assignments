/**
 * @file main.cpp
 * @author Prathamesh Katkar
 * @brief main file for problem 1
 * @version 0.1
 * @date 2019-10-09
 *
 * @copyright Copyright (c) 2019
 *
 */
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

/**
 * @brief Vector class implementation without stl
 *
 * @tparam T
 */
template <class T>
class Vector
{
public:
	T *array;
	int count;
	int capacity;

	Vector<T>(int t = 10) : count(0), capacity(t), array(new T[t]) {}
	void resize(int newCap)
	{
		T *newArray = new T[newCap];
		for (int i = 0; i < min(capacity, newCap); i++)
		{
			newArray[i] = array[i];
		}
		delete[] array;
		array = newArray;
		capacity = newCap;
		count = min(capacity, count);
	}
	/**
	 * @brief Push elements to vector
	 *
	 * @param adj
	 */
	void push(T adj)
	{
		if (count == capacity)
			resize(capacity * 2);
		array[count] = adj;
		count++;
	}
	T &operator[](int i) { return array[i]; }
};

/**
 * @brief Node class for tree
 *
 */
class Node
{
public:
	string name;
	Vector<Node *> adjacent;
	bool visited;
	int distance;

	Node() : name(""), adjacent(10), visited(false) {}
	Node(string s) : name(s), adjacent(10), visited(false) {}
	/**
	 * @brief Connect two nodes
	 *
	 * @param n
	 */
	void connect(Node *n) { adjacent.push(n); }
	void reset()
	{
		visited = false;
		distance = (~1u >> 1);
	}
};

/**
 * @brief find node of particular name
 *
 * @param name
 * @param nodes
 * @return Node*
 */
Node *findNode(string name, Vector<Node> &nodes)
{
	for (int i = 0; i < nodes.count; i++)
	{
		if (nodes[i].name == name)
			return &nodes[i];
	}
	return nullptr;
}

/**
 * @brief reset all the nodes
 *
 * @param nodes
 */
void resetNodes(Vector<Node> &nodes)
{
	for (int i = 0; i < nodes.count; i++)
	{
		nodes[i].reset();
	}
}

/**
 * @brief Finds the loop in graph
 *
 * @param root
 * @param parent
 * @return true
 * @return false
 */
bool recursiveLoopFind(Node *root, Node *parent)
{
	if (root->visited)
		return true;
	root->visited = true;
	for (int i = 0; i < root->adjacent.count; i++)
	{
		if (root->adjacent[i] != parent)
			if (recursiveLoopFind(root->adjacent[i], root))
			{
				return true;
			}
	}
	return false;
}

/**
 * @brief Print the BFS of graph
 *
 * @param root
 */
void printBFS(Node *root)
{
	cout << "BFS: ";
	Vector<Node *> queue;
	queue.push(root);
	root->visited = true;
	int start = 0;
	while (start != queue.count)
	{
		Node *s = queue[start];
		start++;
		cout << s->name << " ";
		for (int i = 0; i < s->adjacent.count; ++i)
		{
			if (!s->adjacent[i]->visited)
			{
				s->adjacent[i]->visited = true;
				queue.push(s->adjacent[i]);
			}
		}
	}
}

/**
 * @brief Travel through the graph
 *
 * @param root
 * @param distance
 */
void travel(Node *root, int distance)
{
	if (root->distance >= distance)
	{
		root->distance = distance;
		for (int i = 0; i < root->adjacent.count; i++)
		{
			travel(root->adjacent[i], distance + 1);
		}
	}
}

/**
 * @brief find maximum distance in the graph
 *
 * @param nodes
 * @return int
 */
int findMaxDistance(Vector<Node> &nodes)
{
	if (nodes.count == 0)
		return 0;
	int maxx = nodes[0].distance;
	for (int i = 0; i < nodes.count; i++)
	{
		maxx = max(maxx, nodes[i].distance);
	}
	return maxx;
}

/**
 * @brief prints the diameter of graph
 *
 * @param nodes
 */
void printDiameter(Vector<Node> &nodes)
{
	int diameter = 0;
	for (int i = 0; i < nodes.count; i++)
	{
		resetNodes(nodes);
		travel(&nodes[i], 0);
		diameter = max(findMaxDistance(nodes), diameter);
	}
	cout << "diameter: " << diameter << endl;
}
/**
 * @brief Prints the DFS of graph
 *
 * @param root
 */
void printDFS(Node *root)
{
	root->visited = true;
	cout << " " << root->name;
	for (int i = 0; i < root->adjacent.count; i++)
	{
		if (!root->adjacent[i]->visited)
		{
			printDFS(root->adjacent[i]);
		}
	}
}
/**
 * @brief Parse the input file
 *
 * @param file
 * @param nodes
 */
void parseFile(ifstream &file, Vector<Node> &nodes)
{
	string line;
	while (getline(file, line))
	{
		std::stringstream stream(line);
		std::string a, b;
		stream >> a >> b;
		Node *aa = findNode(a, nodes);
		Node *bb = findNode(b, nodes);
		if (!aa)
		{
			nodes.push(Node(a));
			aa = &nodes[nodes.count - 1];
		}
		if (!bb)
		{
			nodes.push(Node(b));
			bb = &nodes[nodes.count - 1];
		}
		aa->connect(bb);
		bb->connect(aa);
	}
}
/**
 * @brief main function
 *
 * @param argc
 * @param argv
 * @return int
 */
int main(int argc, char *argv[])
{
	if (argc != 2)
		return -1;
	string fileName = string(argv[1]);
	ifstream in;
	in.open(fileName);
	if (!in)
	{
		cout << "can't open file";
		return -1;
	}
	Vector<Node> nodes(10);
	parseFile(in, nodes);
	in.close();
	resetNodes(nodes);
	cout << "cycle:" << (recursiveLoopFind(&nodes[0], nullptr) ? "yes" : "no")
		 << endl;
	resetNodes(nodes);
	printBFS(&nodes[0]);
	cout << endl;
	resetNodes(nodes);
	cout << "DFS:";
	printDFS(&nodes[0]);
	cout << endl;
	printDiameter(nodes);
	return 0;
}
