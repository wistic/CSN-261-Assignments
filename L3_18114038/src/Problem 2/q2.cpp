/**
 * @file q2.cpp
 * @author Prathamesh
 * @brief print out triplets in an array
 * @version 0.1
 * @date 2019-08-20
 *
 * @copyright Copyright (c) 2019
 *
 */
#include <bits/stdc++.h>

using namespace std;
/**
 * @brief datastructure Node of linked list
 *
 */
class Node
{
public:
	int index_no;
	int cumulative_xor;
	Node *next;
};
/**
 * @brief datastructure linked list
 *
 */
class MyLinkedList
{
public:
	Node *root;
	int no_of_nodes;
};
/**
 * @brief create a node of linked list
 *
 * @param index of the XOR value in main array
 * @param XOR value to be inserted
 * @return pointer to the node
 */
Node *createNode(int index, int cxor)
{
	Node *node = new Node();
	node->index_no = index;
	node->cumulative_xor = cxor;
	node->next = NULL;
	return node;
}
/**
 * @brief create a the LinkedList
 *
 * @param value to be inserted
 * @return pointer to the LinkedList
 */
MyLinkedList *createMyLinkedList(int value)
{
	MyLinkedList *ll = new MyLinkedList();
	ll->root = createNode(0, value);
	ll->no_of_nodes = 1;
	return ll;
}
/**
 * @brief inserta a node in  the LinkedList
 *
 * @param MyLinkedList* list,int index,int value
 * @return pointer to the LinkedList
 */
MyLinkedList *insertLNode(MyLinkedList *list, int index, int value)
{
	if (index == 0)
	{
		list = createMyLinkedList(value);
		return list;
	}
	else
	{
		if (list == NULL)
		{
			cout << "List is Empty." << endl;
			return list;
		}
		Node *temp = list->root;
		while (true)
		{
			if (temp->index_no == (index - 1))
				break;
			if (temp->next == NULL)
				break;
			temp = temp->next;
		}
		int cvalue = (temp->cumulative_xor) ^ value;
		Node *node = createNode(index, cvalue);
		Node *ntemp = list->root;
		if (ntemp->cumulative_xor > cvalue)
		{
			node->next = ntemp;
			list->root = node;
		}
		else
		{
			while (true)
			{
				if (ntemp->next == NULL)
					break;
				else if (ntemp->next->cumulative_xor <= cvalue)
					ntemp = ntemp->next;
				else
					break;
			}
			if (ntemp->next != NULL)
				node->next = ntemp->next;
			ntemp->next = node;
		}
		list->no_of_nodes = list->no_of_nodes + 1;
		return list;
	}
}
int main(int argc, char const *argv[])
{
	//Driver Program
	cout << "Enter the number of positive integers N." << endl;
	int n;
	MyLinkedList *ll = NULL;
	cin >> n;
	int index = 0;
	while (n != 0)
	{
		int a;
		cin >> a;
		ll = insertLNode(ll, index, a);
		index++;
		n--;
	}
	Node *node = createNode(-1, 0);
	if (ll->root != NULL)
		node->next = ll->root;
	ll->root = node;
	ll->no_of_nodes += 1;
	// Node* ltemp=ll->root;
	// for (int i=0;i<ll->no_of_nodes;i++){
	// 	cout<<ltemp->cumulative_xor<<endl;
	// 	ltemp=ltemp->next;
	// }
	int count = 0;
	if (ll->root == NULL)
		cout << "List Empty" << endl;
	else
	{
		Node *temp1 = ll->root;
		if (temp1->next != NULL)
		{
			Node *temp2 = temp1->next;
			stringstream sstm;
			while (true)
			{
				if (temp1->cumulative_xor == temp2->cumulative_xor)
				{
					count += (temp2->index_no - temp1->index_no - 1);
					for (int k = temp1->index_no + 3; k <= temp2->index_no + 1; k++)
						sstm << "(" << temp1->index_no + 2 << "," << k << "," << temp2->index_no + 1 << ")\n";
					if (temp2->next != NULL)
						temp2 = temp2->next;
					else
						break;
				}
				else
				{
					temp1 = temp2;
					if (temp2->next != NULL)
						temp2 = temp1->next;
					else
						break;
				}
			}
			cout << count << endl;
			string result = sstm.str();
			cout << result;
		}
	}
	return 0;
}