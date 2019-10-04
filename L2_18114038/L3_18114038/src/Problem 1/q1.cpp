/**
* @file q1.cpp
* @brief This Cpp file is a program to manage the data of students with the help of data structures.
*
* @author Prathamesh Katkar
*
* @date 21/08/2019
*/

#include <bits/stdc++.h>

using namespace std;
/**
* This class represents a node of Binary Search Tree.
* @date 21/08/2019
*/
class BSTnode{
	public: 
	    int data;  
	    BSTnode *left;  
	    BSTnode *right;
	    int lheight;
	    int rheight;
};
/**
* This class represents a node of AVL Tree.
* @date 21/08/2019
*/
class AVLnode{
	public: 
	    int data;  
	    AVLnode *left;  
	    AVLnode *right;
	    int lheight;
	    int rheight;
};
/**
* This class represents a node of Red Black Tree.
* @date 21/08/2019
*/
class RBTnode{
	public: 
	    int data;  
	    RBTnode *left;  
	    RBTnode *right;
	    RBTnode *parent;
	    bool isroot;
	    int colour;
	    int lheight;
	    int rheight;
};
/**
* This class represents  Binary Search Tree.
* @date 21/08/2019
*/
class BST{
	public:
		BSTnode* root;
		int no_of_nodes;

};
/**
* This class represents AVL Tree.
* @date 21/08/2019
*/
class RBT{
	public:
		RBTnode* root;
		int no_of_nodes;

};
/**
* This class represents Red Black Tree.
* @date 21/08/2019
*/
class AVL{
	public:
		AVLnode* root;
		int no_of_nodes;

};
/**
* This method createBSTNode() will be used to create the node for BST.
* @param int value
* @date 21/08/2019
*/
BSTnode* createBSTNode(int value){
	BSTnode* node=new BSTnode();
	node->data=value;
	node->left=NULL;
	node->right=NULL;
	node->lheight=0;
	node->rheight=0;
	return node;
}
/**
* This method createAVLnode() will be used to create the node for BST.
* @param int value
* @date 21/08/2019
*/
AVLnode* createAVLnode(int value){
	AVLnode* node=new AVLnode();
	node->data=value;
	node->left=NULL;
	node->right=NULL;
	node->lheight=0;
	node->rheight=0;
	return node;
}
/**
* This method createRBTnode() will be used to create the node for BST.
* @param int value
* @date 21/08/2019
*/
RBTnode* createRBTnode(int value){
	RBTnode* node=new RBTnode();
	node->data=value;
	node->left=NULL;
	node->right=NULL;
	node->parent=NULL;
	node->isroot=false;
	node->colour=1;  //Black is 0 and Red is 1
	node->lheight=0;
	node->rheight=0;
	return node;
}
/**
* This method createBST() will be used to create  BST.
* @param int value
* @date 21/08/2019
*/
BST* createBST(int value){
	BST* bst=new BST();
	bst->root=createBSTNode(value);
	bst->no_of_nodes=1;
	return bst;
}
/**
* This method createAVL() will be used to create AVL Tree.
* @param int value
* @date 21/08/2019
*/
AVL* createAVL(int value){
	AVL* avl=new AVL();
	avl->root=createAVLnode(value);
	avl->no_of_nodes=1;
	return avl;
}
/**
* This method createRBT() will be used to create  RBT.
* @param int value
* @date 21/08/2019
*/
RBT* createRBT(int value){
	RBT* rbt=new RBT();
	rbt->root=createRBTnode(value);
	rbt->root->colour=0;
	rbt->root->isroot=true;
	rbt->no_of_nodes=1;
	return rbt;
}
/**
* This method changeBSTheight() will be used to update heights of BST.
* @param BSTnode* node
* @date 21/08/2019
*/
int changeBSTheight(BSTnode* node){
	if (node->left==NULL)
	{
		if (node->right==NULL){
			node->lheight=0;
			node->rheight=0;
			return 1;
		}
		else{
			node->rheight=changeBSTheight(node->right);
			node->lheight=0;
			return node->rheight+1;
		}
	}
	else{
		if (node->right==NULL){
			node->lheight=changeBSTheight(node->left);
			node->rheight=0;
			return node->lheight+1;
		}
		else{
			node->rheight=changeBSTheight(node->right);
			node->lheight=changeBSTheight(node->left);
			return abs(node->lheight-node->rheight)+2;
		}
	}
}
/**
* This method changeAVLheight() will be used to update heights of AVL.
* @param AVLnode* node
* @date 21/08/2019
*/
int changeAVLheight(AVLnode* node){
	if (node->left==NULL)
	{
		if (node->right==NULL){
			node->lheight=0;
			node->rheight=0;
			return 1;
		}
		else{
			node->rheight=changeAVLheight(node->right);
			node->lheight=0;
			return node->rheight+1;
		}
	}
	else{
		if (node->right==NULL){
			node->lheight=changeAVLheight(node->left);
			node->rheight=0;
			return node->lheight+1;
		}
		else{
			node->rheight=changeAVLheight(node->right);
			node->lheight=changeAVLheight(node->left);
			return abs(node->lheight-node->rheight)+2;
		}
	}
}
/**
* This method changeRBTheight() will be used to update heights of RBT.
* @param RBTnode* node
* @date 21/08/2019
*/
int changeRBTheight(RBTnode* node){
	if (node->left==NULL)
	{
		if (node->right==NULL){
			node->lheight=0;
			node->rheight=0;
			return 1;
		}
		else{
			node->rheight=changeRBTheight(node->right);
			node->lheight=0;
			return node->rheight+1;
		}
	}
	else{
		if (node->right==NULL){
			node->lheight=changeRBTheight(node->left);
			node->rheight=0;
			return node->lheight+1;
		}
		else{
			node->rheight=changeRBTheight(node->right);
			node->lheight=changeRBTheight(node->left);
			return abs(node->lheight-node->rheight)+2;
		}
	}
}
/**
* This method insertNodeBST() will be used to insert  a node RBT.
* @param int value,BST* bst
* @date 21/08/2019
*/
BST* insertNodeBST(int value,BST* bst){
	if (bst==NULL){
		bst=createBST(value);
		return bst;
	}
	else{
		BSTnode* node=createBSTNode(value);
		BSTnode* temp=bst->root;
		while(true){
			if (temp==NULL)
			{
				cout<<"Enter in inserting node."<<endl;
				break;
			}
			else
			{
				
				if ((temp->data)>value)
					{
						if (temp->left==NULL)
							{
								temp->left=node;
								bst->no_of_nodes+=1;
								break;
							}
						temp=temp->left;
					}
				else
					{
					if (temp->right==NULL)
							{
								temp->right=node;
								bst->no_of_nodes+=1;
								break;
							}		
						temp=temp->right;
					}
			}
		}
		int h=changeBSTheight(bst->root);
		return bst;
	}
}
/**
* This method rightRotateAVLnode() will be used to rotate an AVL node to right..
* @param AVLnode* node
* @date 21/08/2019
*/
AVLnode* rightRotateAVLnode(AVLnode* node){
	AVLnode* x=node->left;
	AVLnode *T2 = x->right;
	x->right = node;
	node->left = T2;
	return x;
}
/**
* This method leftRotateAVLnode() will be used to rotate an AVL node to left..
* @param AVLnode* node
* @date 21/08/2019
*/
AVLnode* leftRotateAVLnode(AVLnode* node)  
{  
    AVLnode* y = node->right;  
    AVLnode* T2 = y->left;  
  
    // Perform rotation  
    y->left = node;  
    node->right = T2;  
  
    // Update heights  
  
    // Return new root  
    return y;  
}
/**
* This method reorderAVL() will be used to reorder AVL.
* @param AVLnode* node
* @date 21/08/2019
*/
AVLnode* reorderAVL(AVLnode* node){
	if (node==NULL)
		return NULL;
	int level=abs((node->lheight)-(node->rheight));
	if ((level==0) || (level==1)){
		node->left=reorderAVL(node->left);
		node->right=reorderAVL(node->right);
		return node;
	}
	else{
		if (node->lheight>node->rheight){
			if (node->left->lheight>node->left->rheight){
				node=rightRotateAVLnode(node);
				int h=changeAVLheight(node);
				return node;
			}	
			else{
				node->left=leftRotateAVLnode(node->left);
				node=rightRotateAVLnode(node);
				int h=changeAVLheight(node);
				return node;
			}
		}
		else{
			if (node->right->lheight>node->right->rheight){
				node->right=rightRotateAVLnode(node->right);
				node=leftRotateAVLnode(node);
				int h=changeAVLheight(node);
				return node;
			}
			else{
				node=leftRotateAVLnode(node);
				int h=changeAVLheight(node);
				return node;
			}
		}
	}
}
/**
* This method insertNodeAVL() will be used to insert a node in AVL.
* @param int value,AVL* avl
* @date 21/08/2019
*/
AVL* insertNodeAVL(int value,AVL* avl){
	if (avl==NULL){
		avl=createAVL(value);
		return avl;
	}
	else{
		AVLnode* node=createAVLnode(value);
		AVLnode* temp=avl->root;
		while(true){
			if (temp==NULL)
			{
				break;
			}
			else
			{
				
				if ((temp->data)>value)
					{
						if (temp->left==NULL)
							{
								temp->left=node;
								avl->no_of_nodes+=1;
								break;
							}
						temp=temp->left;
					}
				else
					{
					if (temp->right==NULL)
							{
								temp->right=node;
								avl->no_of_nodes+=1;
								break;
							}		
						temp=temp->right;
					}
			}
		}
		int h=changeAVLheight(avl->root);
		avl->root=reorderAVL(avl->root);
		h=changeAVLheight(avl->root);
		return avl;
	}
}
/**
* This method createAVLTree() will be used to create an AVL Tree from BST.
* @param AVL* avl,BSTnode* node
* @date 21/08/2019
*/
AVL* createAVLTree(AVL* avl,BSTnode* node){
	BSTnode* temp=node;
	if (temp==NULL)
			{
				cout<<"BST is empty"<<endl;
				return avl;
			}
	avl=insertNodeAVL(temp->data,avl);
	if (temp->left!=NULL)
		avl=createAVLTree(avl,temp->left);
	if (temp->right!=NULL)
		avl=createAVLTree(avl,temp->right);
	return avl;
}
/**
* This method printInOrderTraversal() will be used to print INOrder Traversal of BST.
* @param (BSTnode* temp
* @date 21/08/2019
*/
void printInOrderTraversal(BSTnode* temp){
	if (temp==NULL)
			return;
	printInOrderTraversal(temp->left);
	cout<<temp->data<<" ";
	printInOrderTraversal(temp->right);
}
/**
* This method rightRotateRBTnode() will be used to rotate an AVL node to left..
* @param RBTnode* node
* @date 21/08/2019
*/
void rightRotateRBTnode(RBTnode* node){
	RBTnode* x=node->left;
	RBTnode *T2 = x->right;
	if (node->isroot==false)
		if (node->parent->right==node)
			node->parent->right=x;
		else
			node->parent->left=x;
	x->parent=node->parent;
	if (T2!=NULL)
		T2->parent=node;
	node->parent=x;
	x->right = node;
	node->left = T2;
}
/**
* This method leftRotateRBTnode() will be used to rotate an AVL node to right..
* @param RBTnode* node
* @date 21/08/2019
*/
void leftRotateRBTnode(RBTnode* node)  
{  
    RBTnode* y = node->right;  
    RBTnode* T2 = y->left;
    if (node->isroot==false)
		if (node->parent->right==node)
			node->parent->right=y;
		else
			node->parent->left=y;  
  	y->parent=node->parent;
  	if (T2!=NULL)
  		T2->parent=node;
  	node->parent=y;
    y->left = node;  
    node->right = T2;  
  
    // Update heights  
  
    // Return new root 
}
/**
* This method fixes the violation created after insertion.
* @param RBTnode* node
* @return pointer to the root of AVLTree
* @date 21/08/2019
*/
void reorderRBT(RBTnode* node,RBT* rbt){
	RBTnode* uncle=NULL;
	RBTnode* grandparent=NULL;
	RBTnode* father=NULL;
	if (node->isroot==true){
		node->colour=0;
	}
	if ((node->isroot==false) && (node->parent->colour==1))
	{
		grandparent=node->parent->parent;
		father=node->parent;
		int ucolour;
		if (grandparent->left==NULL)
			ucolour=0;
		else if (grandparent->right==NULL)
			ucolour=0;
		else {
			if (grandparent->left==node->parent){
				ucolour=grandparent->right->colour;
				}
			else
				ucolour=grandparent->left->colour;
		}
		if ((ucolour==1)) {
			father->colour=0;
			if (grandparent->left==node->parent){
				if (grandparent->right!=NULL)
					grandparent->right->colour=0;
				}
			else{
				if (grandparent->left!=NULL)
					grandparent->left->colour=0;
			}
				grandparent->colour=1;
				reorderRBT(grandparent,rbt);
		}
		else{
			if (node->parent==grandparent->left){
				if (node==node->parent->left){
					rightRotateRBTnode(grandparent);
					father->colour=0;
					grandparent->colour=1;
					int h1=changeRBTheight(grandparent);
					if (grandparent->isroot==true)
					{
						father->isroot=true;
						rbt->root=father;
						grandparent->isroot=false;
					}
				}
				else{
					leftRotateRBTnode(father);
					rightRotateRBTnode(grandparent);
					grandparent->colour=1;
					node->colour=0;
					int h1=changeRBTheight(grandparent);
					if (grandparent->isroot==true)
					{
						node->isroot=true;
						rbt->root=node;
						grandparent->isroot=false;
					}
				}
			}
			else{
				if (node==node->parent->left){
					rightRotateRBTnode(father);
					leftRotateRBTnode(grandparent);
					grandparent->colour=1;
					node->colour=0;
					int h1=changeRBTheight(grandparent);
					if (grandparent->isroot==true)
					{
						node->isroot=true;
						rbt->root=node;
						grandparent->isroot=false;
					}
				}
				else{
					leftRotateRBTnode(grandparent);
					father->colour=0;
					grandparent->colour=1;
					int h1=changeRBTheight(grandparent);
					if (grandparent->isroot==true)
					{
						father->isroot=true;
						rbt->root=father;
						grandparent->isroot=false;
					}

				}
			}	
		}
	}
}	
/**
* This method insertNodeRBT() will be insert a node in RBT.
* @param int value,RBT* rbt
* @date 21/08/2019
*/
RBT* insertNodeRBT(int value,RBT* rbt){
	if (rbt==NULL){
		rbt=createRBT(value);
		return rbt;
	}
	else{
		RBTnode* node=createRBTnode(value);
		RBTnode* temp=rbt->root;
		RBTnode* pt=NULL;
		while(true){
			if (temp==NULL)
			{
				
				break;
			}
			else
			{
				
				if ((temp->data)>value)
					{
						if (temp->left==NULL)
							{
								temp->left=node;
								temp->left->parent=temp;
								temp=temp->left;
								rbt->no_of_nodes+=1;
								break;
							}
						temp=temp->left;
					}
				else
					{
					if (temp->right==NULL)
							{
								temp->right=node;
								temp->right->parent=temp;
								temp=temp->right;
								rbt->no_of_nodes+=1;
								break;
							}
						temp=temp->right;
					}
			}
		}
		int h2=changeRBTheight(rbt->root);
		reorderRBT(temp,rbt);
		int h3=changeRBTheight(rbt->root);
		return rbt;
	}
}
/**
* This method printBSTArray() will be used to print BSTArray.
* @param iint ints[], int len
* @date 21/08/2019
*/
void printBSTArray(int ints[], int len)  
{  
    int i;  
    for (i = 0; i < len; i++)  
    {  for (int j=i;j<len-1;j++)
        {cout << ints[j] << "->"; }
        cout<<ints[len-1]<<endl;
    } 
} 
void printBSTPathsRecur(BSTnode* node, int path[], int pathLen)  
{  
    if (node == NULL)  
        return;  
      
    /* append this node to the path array */
    path[pathLen] = node->data;  
    pathLen++;  
      
    /* it's a leaf, so print the path that led to here */
    if (node->left == NULL && node->right == NULL)  
    {  
        printBSTArray(path, pathLen);  
    }  
    else
    {  
        /* otherwise try both subtrees */
        printBSTPathsRecur(node->left, path, pathLen);  
        printBSTPathsRecur(node->right, path, pathLen);  
    }  
}
/**
* This method printBSTPath() will be used to print all possible path from root to leaf.
* @param BSTnode* node
* @date 21/08/2019
*/
void printBSTPath(BSTnode* node){
	int path[1000];  
    printBSTPathsRecur(node, path, 0); 
}
/**
* This method printAVLArray() will be used to print AVLArray.
* @param iint ints[], int len
* @date 21/08/2019
*/
void printAVLArray(int ints[], int len)  
{  
    int i;  
    for (i = 0; i < len; i++)  
    {  for (int j=i;j<len-1;j++)
        {cout << ints[j] << "->"; }
        cout<<ints[len-1]<<endl;
    } 
}
void printAVLPathsRecur(AVLnode* node, int path[], int pathLen)  
{  
    if (node == NULL)  
        return;  
      
    /* append this node to the path array */
    path[pathLen] = node->data;  
    pathLen++;  
      
    /* it's a leaf, so print the path that led to here */
    if (node->left == NULL && node->right == NULL)  
    {  
        printAVLArray(path, pathLen);  
    }  
    else
    {  
        /* otherwise try both subtrees */
        printAVLPathsRecur(node->left, path, pathLen);  
        printAVLPathsRecur(node->right, path, pathLen);  
    }  
}
/**
* This method printAVLPath() will be used to print all possible path from root to leaf.
* @param AVLnode* node
* @date 21/08/2019
*/
void printAVLPath(AVLnode* node){
	int path[1000];  
    printAVLPathsRecur(node, path, 0); 
}
/**
* This method printRBTArray() will be used to print RBTArray.
* @param int ints[], int len
* @date 21/08/2019
*/
void printRBTArray(int ints[], int len)  
{  
    int i;  
    for (i = 0; i < len; i++)  
    {  for (int j=i;j<len-1;j++)
        {cout << ints[j] << "->"; }
        cout<<ints[len-1]<<endl;
    } 
}
void printRBTPathsRecur(RBTnode* node, int path[], int pathLen)  
{  
    if (node == NULL)  
        return;  
      
    /* append this node to the path array */
    path[pathLen] = node->data;  
    pathLen++;  
      
    /* it's a leaf, so print the path that led to here */
    if (node->left == NULL && node->right == NULL)  
    {  
        printRBTArray(path, pathLen);  
    }  
    else
    {  
        /* otherwise try both subtrees */
        printRBTPathsRecur(node->left, path, pathLen);  
        printRBTPathsRecur(node->right, path, pathLen);  
    }  
}
/**
* This method printRBTPath() will be used to print all possible path from root to leaf.
* @param RBTnode* node
* @date 21/08/2019
*/
void printRBTPath(RBTnode* node){
	int path[1000];  
    printRBTPathsRecur(node, path, 0); 
}
/**
* This method printBST() will be used to print the BST.
* @param BSTnode* temp,int lev
* @date 21/08/2019
*/
void printBST(BSTnode* temp,int lev){
	if (temp==NULL)
		return;
	int templ=lev;
	while(templ!=0){
		cout<<"\t";
		templ--;
	}
	if ((temp->right==NULL) && (temp->left==NULL))
		cout<<temp->data<<endl;
	else
		cout<<temp->data<<" ["<<abs(temp->lheight-temp->rheight)<<"]"<<endl;
	printBST(temp->left,lev+1);
	printBST(temp->right,lev+1);
}
/**
* This method printAVL() will be used to print the AVl.
* @param AVLnode* temp,int lev
* @date 21/08/2019
*/
void printAVL(AVLnode* temp,int lev){
	if (temp==NULL)
		return;
	int templ=lev;
	while(templ!=0){
		cout<<"\t";
		templ--;
	}
	if ((temp->right==NULL) && (temp->left==NULL))
		cout<<temp->data<<endl;
	else
		cout<<temp->data<<" ["<<abs(temp->lheight-temp->rheight)<<"]"<<endl;
	printAVL(temp->left,lev+1);
	printAVL(temp->right,lev+1);
}
/**
* This method printRBT() will be used to print the RBT.
* @param RBTnode* temp,int lev
* @date 21/08/2019
*/
void printRBT(RBTnode* temp,int lev){
	if (temp==NULL)
		return;
	int templ=lev;
	while(templ!=0){
		cout<<"\t";
		templ--;
	}
	if ((temp->right==NULL) && (temp->left==NULL))
	{if (temp->colour==0)
			cout<<temp->data<<" [Black]"<<endl;
		else
			cout<<temp->data<<" [Red]"<<endl;}
	else
	{
		if (temp->colour==0)
			cout<<temp->data<<" ["<<abs(temp->lheight-temp->rheight)<<"]"<<" [Black]"<<endl;
		else
			cout<<temp->data<<" ["<<abs(temp->lheight-temp->rheight)<<"]"<<" [Red]"<<endl;
	}
	printRBT(temp->left,lev+1);
	printRBT(temp->right,lev+1);
}
int main(int argc, char const *argv[])
{
		//Driver Program
		BST* bst=NULL;
		RBT* rbt=NULL;
		AVL* avl=NULL;
	while(true){
		cout<<"Insert the corresponding index number to perform an action.\n"<<endl;
		cout<<"1. To insert a node in the BST and in the red-black tree "<<endl;
		cout<<"2. To create AVL tree from the inorder traversal of the BST"<<endl;
		cout<<"3. To print the inorder traversal of the BST/AVL/red-black tree"<<endl;
		cout<<"4. To display all the paths in the BST/AVL tree/red-black tree"<<endl;
		cout<<"5. To print the BST/AVL tree/red-black Tree in the terminal using level-wise indentation (print color for red-black tree) "<<endl;
		cout<<"6. Exit"<<endl;
		int a;
		int value;
		cin>>a;
		switch (a){
			case 1:{
						cout<<"Enter the value of the node."<<endl;
						cin>>value;
						bst=insertNodeBST(value,bst);
						rbt=insertNodeRBT(value,rbt);
						cout<<"Node is inserted."<<endl;
						break;
					}
			case 2:{
						avl=NULL;
						if (bst==NULL)
							cout<<"Create the BST first."<<endl;
						else{
							avl=createAVLTree(avl,bst->root);
							cout<<"AVL Tree created."<<endl;
						}
						break;
					}
			case 3:{
				printInOrderTraversal(bst->root);
				cout<<endl;
				break;
			}
			case 4:{
				cout<<"Whose paths you want to print."<<endl;
				cout<<"1. Binary Search Tree"<<endl;
				cout<<"2. AVL Tree"<<endl;
				cout<<"3. Red Black Tree"<<endl;
				int b;
				cin>>b;
				switch (b){
					case 1:{
						printBSTPath(bst->root);
						break;
					}
					case 2:{
						if (avl==NULL)
							{
								cout<<"Create the Tree first."<<endl;
								break;
							}
						printAVLPath(avl->root);
						break;
					}
					case 3:{
						printRBTPath(rbt->root);
						break;
					default:cout<<"Invalid value entered"<<endl;
					}
				}
				break;
			}
			case 5:{
				cout<<"Which you want to print."<<endl;
				cout<<"1. Binary Search Tree"<<endl;
				cout<<"2. AVL Tree"<<endl;
				cout<<"3. Red Black Tree"<<endl;
				int b;
				cin>>b;
				switch (b){
					case 1:{
						if (bst==NULL)
							cout<<"Create the BST first."<<endl;
						else
							printBST(bst->root,0);
						break;
					}
					case 2:{
						if (avl==NULL)
							cout<<"Create the AVL first."<<endl;
						else
							printAVL(avl->root,0);
						break;
					}
					case 3:{
						if (rbt==NULL)
							cout<<"Create the RBT first."<<endl;
						else
							printRBT(rbt->root,0);
						break;
					default:cout<<"Invalid value entered"<<endl;
					}
				}
				break;
			}
			case 6:exit(0);
			break;
			default:cout<<"Invalid value entered"<<endl;
		}
	}
	return 0;
}