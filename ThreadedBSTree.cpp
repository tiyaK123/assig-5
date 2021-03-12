/**
 * Threaded Binary Tree
 * --------------------
 * ThreadedBSTree.cpp
 * --------------------
 * Threaded Binary Tree  both left and right NULL pointers are made to
 *  point to inorder predecessor and inorder successor respectively.
 *  The threads makes fast accessing ancestors of a node.
 * 
 * Date: Date: 2/23/2021
 * Strudent: Ting-Shiuan Chen and Tiya Adugna 
 * **/
#include "ThreadedBSTree.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>
using namespace std;

// Overload the operator and displays inorder traversals  
ostream &operator<<(std::ostream &out, const ThreadedBSTree &bts)
 {
	TreeNode *curr = bts.root;
	 while (!curr->lThread)
	 {
		 curr = curr->leftChild;
	 }
	 while (curr != nullptr)
	 {
		 out << curr->data << " ";
		 if (curr->rThread)
		 {
			 curr = curr->rightChild;
		 }
		 else
		 {
			 curr = curr->rightChild;
			 while (!curr->lThread)
			 {
				 curr = curr->leftChild;
			 }
		 }
	 }
	 
	 return out;
 } 

 // constructor sets root to null
ThreadedBSTree::ThreadedBSTree()
{
	root = nullptr;
}

// destructor will delete individual nodes
ThreadedBSTree::~ThreadedBSTree()
{
	clear(root);
}

// copy constructor 
ThreadedBSTree::ThreadedBSTree(const ThreadedBSTree &other)
{
	if (other.root == nullptr)
	{
		this->root = nullptr;
	}
	else
	{
		this->root = new TreeNode(other.root->data);
		TreeNode *copyFrom = other.root;
		while (!copyFrom->lThread)
		{
			copyFrom = copyFrom->leftChild;
		}
		insert(this->root, copyFrom->data);
		while (copyFrom->rightChild != nullptr)
		{
			if (copyFrom->rThread)
			{
				copyFrom = copyFrom->rightChild;
				insert(this->root, copyFrom->data);
			}
			else
			{
				copyFrom = copyFrom->rightChild;
				insert(this->root, copyFrom->data);
				while (!copyFrom->lThread)
				{
					copyFrom = copyFrom->leftChild;
					insert(this->root, copyFrom->data);
				}
			}
		}
	}
}

// helper method deletes individual nodes
void ThreadedBSTree::clear(TreeNode *root)
{
	TreeNode *curr = root;
	while (!curr->lThread)
	{
		curr = curr->leftChild;
	}

	while (curr != nullptr)
	{
		TreeNode *del = curr;
		if (curr->rThread)
		{
			curr = curr->rightChild;
		}
		else
		{
			curr = curr->rightChild;
			while (!curr->lThread)
			{
				curr = curr->leftChild;
			}
		}
		delete del;
		del = nullptr;
	}
}

/** constructor sets leftchild and rightChild to null 
 * and lThread and rThread to true
 **/
TreeNode::TreeNode()
{
	leftChild = nullptr;
	rightChild = nullptr;
	lThread = true;
	rThread = true;
}

// constructor take nodeItem, left, and right as parameters
TreeNode::TreeNode(const int &nodeItem, TreeNode *left, TreeNode *right)
{
	data = nodeItem;
	leftChild = left;
	rightChild = right;
}

// constructor take item  as parameters
TreeNode::TreeNode(int item)
{
	data = item;
	leftChild = nullptr;
	rightChild = nullptr;
	lThread = true;
	rThread = true;
}

/**
 * removes even numbers in the TBST
 * pre-con: none 
 * post-con:none
 * **/
void ThreadedBSTree::removeEven(int number)
{
	for (int i = 1; i <= number; i++)
	{
		if (i % 2 == 0)
		{
			if(contains(i))
			remove(i);
		}
	}
}

/**
 * return true if the node of the item is found
 * pre-con: the number has to be in the TBST
 * post-con: if the number exist it calls the 
 * 			 helper method removeSearch to get the node
 * **/ 
bool ThreadedBSTree::remove(int item)
{
	TreeNode *parent = nullptr;
	if(contains(item))
	{
		return removeSearch(parent, root, item);
	}
	return false;
}

/**
 * returns true if the item is found and removed from TBST
 * pre-con: the item has to be in the TBST
 * post-con: go through the TBST recursively and when found calls
 * 			 removeNode method to delete the node from tree and 
 * 		     returns true
 * **/
bool ThreadedBSTree::removeSearch(TreeNode *parent, TreeNode *tr, int &item)
{
	if (tr == nullptr)
	{
		root = nullptr;
		return false;
	}
	else
	{
		if (tr->data == item)
		{
			removeNode(tr, parent);
			return true;
		}
		parent = tr;
		if (item < tr->data)
		{
			tr = tr->leftChild;
			removeSearch(parent, tr, item);
		}
		else
		{
			tr = tr->rightChild;
			removeSearch(parent, tr, item);
		}
	}
	return false;
}

/**
 * removes the node from TBST
 * pre-con: the node to be removed has to be in thr TBST
 * post-con: 
 * **/
void ThreadedBSTree::removeNode(TreeNode *node, TreeNode *parent)
{
	if (node->lThread && node->rThread)
	{
		if (parent == nullptr)
		{
			root = nullptr;
		}
		else if (node == parent->leftChild)
		{
			parent->lThread = true;
			parent->leftChild = node->leftChild;
		}
		else
		{
			parent->rThread = true;
			parent->rightChild = node->rightChild;
		}
		delete node;
		node = nullptr;
	}
	else if (!node->lThread && !node->rThread)
	{
		int newNodeValue;
		TreeNode *parentSucc = node;	   //parent Successor]
		TreeNode *succ = node->rightChild; //successor
		newNodeValue = removeLeftMostNode(node->rightChild);
		node->data = newNodeValue; // Put replacement value in node N
		removeNode(succ, parentSucc);
		//return node;
	}
	else
	{
		// node has only one child
		TreeNode *nodeToConnect;
		TreeNode *threadNode;
		if (node->rThread)
		{
			nodeToConnect = node->leftChild;
		}
		else
		{
			nodeToConnect = node->rightChild;
		}
		// connect parent and node->nextNode
		TreeNode *ptrThreadNode; // the Node that point to delete node threadNode
		if (parent == nullptr)
		{
			root = nodeToConnect;
		}
		else if (node == parent->leftChild) // Node is left child of its parent.
		{
			parent->leftChild = nodeToConnect;
		}
		else
		{ // Node is right Child of its parents
			parent->rightChild = nodeToConnect;
		}

		if (node->lThread)
		{
			threadNode = node->leftChild;
			ptrThreadNode = nodeToConnect;
			while (!ptrThreadNode->lThread)
			{
				ptrThreadNode = ptrThreadNode->leftChild;
			}
			ptrThreadNode->leftChild = threadNode;
		}
		else
		{
			threadNode = node->rightChild;
			ptrThreadNode = nodeToConnect;
			while (!ptrThreadNode->rThread)
			{
				ptrThreadNode = ptrThreadNode->rightChild;
			}
			ptrThreadNode->rightChild = threadNode;
		}

		delete node;
		node = nullptr;
	}
}

/**
 * 
 * pre-con:
 * post-con:
 * **/
int ThreadedBSTree::removeLeftMostNode(TreeNode *node)
{
	if (node->lThread)
	{
		return node->data;
	}
	else
	{
		return removeLeftMostNode(node->leftChild);
	}
}

/**
 * inserts numbers from the vector to the TBST in a 
 * balnced manner 
 * pre-con: the vector should have elements in a sorted manner
 * post-con: inserts numbers in TBST in a balanced manner from 
 * 			 vector by insering the midpoint (n/2)
 * **/
void ThreadedBSTree::add(vector<int> v, int start, int end)
{
	if (start > end)
	{
		return;
	}
	int mid = start + (end - start) / 2;
	int check = v[mid];
	insert(root, check);
	add(v, start, mid - 1);
	add(v, mid + 1, end);
}

/**
 * adds the numbers to the vector in a sorted manner
 * pre-con: none
 * post-con: none
 * **/
void ThreadedBSTree::numbers(int num)
{
	vector<int> vec;
	int numbers = 1;
	for (int i = 0; i < num; i++)
	{

		vec.push_back(numbers);
		numbers++;
	}
	int last = vec.size() - 1;
	add(vec, 0, last);
}

/**
 * adds the item and calls thread method if the node is a leaf
 * pre-con: the item must not be in the TBST
 * post-con: creats new node and adds item and calls 
 * 			 thread method if its the leaf 
 * **/
void ThreadedBSTree::insert(TreeNode *tr, int item)
{
	if (root == nullptr)
	{
		root = new TreeNode;
		root->data = item;
		root->lThread = true;
		root->rThread = true;
	}
	else
	{
		if (contains(item))
		{
			return;
		}
		if (item < tr->data)
		{
			if (!tr->lThread)
			{
				insert(tr->leftChild, item);
			}
			else
			{
				auto *nNode = new TreeNode;
				nNode->data = item;
				tr->lThread = false;
				thread(tr, nNode, item);
			}
		}
		else
		{
			if (!tr->rThread)
			{
				insert(tr->rightChild, item);
			}
			else
			{
				auto *nNode = new TreeNode;
				nNode->data = item;
				tr->rThread = false;
				thread(tr, nNode, item);
			}
		}
	}
}

/**
 * 
 * pre-con: 
 * post-con:
 * **/
void ThreadedBSTree::thread(TreeNode *tr, TreeNode *nNode, int item)
{

	TreeNode *curr = nNode;
	TreeNode *ptr = tr;
	if (item < ptr->data)
	{
		if (!ptr->lThread)
		{
			curr->rightChild = ptr;
			curr->leftChild = ptr->leftChild;
			ptr->leftChild = curr;
		}
	}
	else if (item > ptr->data)
	{
		if (!ptr->rThread)
		{
			curr->rightChild = ptr->rightChild;
			curr->leftChild = ptr;
			ptr->rightChild = curr;
		}
	}
}

/**
 * returns true if item is in the TBST
 * pre-con: none
 * post-con: goes through the TBST and checks if item 
 * 			 is in tree
 * **/
bool ThreadedBSTree::contains(const int &item) const
{
	if (root == nullptr)
	{
		return false;
	}
	TreeNode *temp = root;
	while (temp != nullptr)
	{
		if (item == temp->data)
		{
			return true;
		}
		if (item < temp->data)
		{
			if (!temp->lThread)
			{
				temp = temp->leftChild;
			}
			else
			{
				return false;
			}
		}
		else if (item > temp->data)
		{
			if (!temp->rThread)
			{
				temp = temp->rightChild;
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

