/**
 * @file main.cpp
 * @author Prathamesh Katkar
 * @brief main file for p2
 * @version 0.1
 * @date 2019-10-09
 *
 * @copyright Copyright (c) 2019
 *
 */

#include <fstream>
#include <iostream>

const int maxRank = 100000;
using namespace std;

/**
 * @brief custom vector implementation
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
		for (int i = 0; i < (capacity < newCap ? capacity : newCap); i++)
		{
			newArray[i] = array[i];
		}
		delete[] array;
		array = newArray;
		capacity = newCap;
		count = (capacity < count ? capacity : count);
	}
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
 * @brief custom node class for tree
 *
 */
class Node
{
public:
	int data;
	Vector<Node *> childs;

	Node(int d) : data(d), childs(Vector<Node *>(10)) {}
};

/**
 * @brief plants the tree in forest
 *
 * @param node
 * @param list
 */
void plant(Node *node, Node **list)
{
	if (!node)
		return;
	int rank = node->childs.count;
	if (list[rank])
	{
		Node *parent = list[rank];
		list[rank] = nullptr;
		if (parent->data < node->data)
			parent->childs.push(node);
		else
		{
			node->childs.push(parent);
			parent = node;
		}
		plant(parent, list);
	}
	else
	{
		list[rank] = node;
	}
}

/**
 * @brief prints the tree
 *
 * @param root
 */
void print(Node *root)
{
	cout << root->data << " ";
	for (int i = 0; i < root->childs.count; i++)
	{
		print(root->childs[i]);
	}
}

/**
 * @brief prints the graph in dot lang
 *
 * @param file
 * @param root
 */
void printGraph(ofstream &file, Node *root)
{
	for (int i = 0; i < root->childs.count; i++)
	{
		file << '\t' << root->data << " -- " << root->childs[i]->data << ";\n";
		printGraph(file, root->childs[i]);
	}
}
/**
 * @brief header of dot lang
 *
 * @param file
 * @param root
 */
void printGraphStart(ofstream &file, Node *root)
{
	file << "subgraph order" << root->childs.count << "{\n";
	if (root->childs.count == 0)
	{
		file << '\t' << root->data << ";\n";
	}
	printGraph(file, root);
	file << "}\n";
}
/**
 * @brief main function
 *
 * @return int
 */
int main()
{
	int total;
	cin >> total;

	Node **array = new Node *[maxRank];
	for (int i = 0; i < maxRank; i++)
	{
		array[i] = nullptr;
	}
	for (int i = 0; i < total; i++)
	{
		int in;
		cin >> in;
		plant(new Node(in), array);
	}
	cout << '\n';
	ofstream file;
	file.open("output.dot");
	file << "graph parent{\n";
	for (int i = 0; i < maxRank; i++)
	{
		if (array[i])
		{
			cout << "order:" << i << " : ";
			print(array[i]);
			cout << endl;
			printGraphStart(file, array[i]);
		}
	}
	file << "}";
	file.close();
	cout << "saved as output.dot\n";
	return 0;
}
