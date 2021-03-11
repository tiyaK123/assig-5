#include "ThreadedBSTree.h"
#include <iostream>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

/*  ostream &operator<<(std::ostream &out, const ThreadedBSTree &bts)
 {
	 TreeNode *curr = bts.root;
	 while (curr->lThread == false)
	 {
		 curr = curr->leftChild;
	 }

	 while (curr != nullptr)
	 {
		 out << curr->data << " ";
		 if (curr->rThread == true)
		 {
			 curr = curr->rightChild;
		 }
		 else
		 {
			 curr = curr->rightChild;
			 while (curr->lThread == false)
			 {
				 curr = curr->leftChild;
			 }
		 }
	 }
	 return out;
 } */
ThreadedBSTree::ThreadedBSTree()
{
	root = nullptr;
}
ThreadedBSTree::~ThreadedBSTree()
{
	clear(root);
}

ThreadedBSTree::ThreadedBSTree(const ThreadedBSTree &other)
{
	if (other.root == nullptr)
	{
		this->root = /* new TreeNode */ nullptr;
	}
	else
	{
		this->root = new TreeNode(other.root->data);
		TreeNode *copy_from = other.root;
		while (copy_from->lThread == false)
		{
			copy_from = copy_from->leftChild;
		}
		insert(this->root, copy_from->data);
		while (copy_from->rightChild != NULL)
		{
			if (copy_from->rThread == true)
			{
				copy_from = copy_from->rightChild;
				insert(this->root, copy_from->data);
			}
			else
			{
				copy_from = copy_from->rightChild;
				insert(this->root, copy_from->data);
				while (copy_from->lThread == false)
				{
					copy_from = copy_from->leftChild;
					insert(this->root, copy_from->data);
				}
			}
		}
	}
}

void ThreadedBSTree::helper(TreeNode *&to, const TreeNode *from)
{
	if (from == NULL)
	{
		to = nullptr;
	}
	else
	{
		to = new TreeNode;
		to->data = from->data;
		helper(to->leftChild, from->leftChild);
		helper(to->rightChild, from->rightChild);
	}
}

void ThreadedBSTree::clear(TreeNode *root)
{
	TreeNode *curr = root;
	while (curr->lThread == false)
	{
		curr = curr->leftChild;
	}

	while (curr != nullptr)
	{
		TreeNode *del = curr;
		if (curr->rThread == true)
		{
			curr = curr->rightChild;
		}
		else
		{
			curr = curr->rightChild;
			while (curr->lThread == false)
			{
				curr = curr->leftChild;
			}
		}
		delete del;
		del = NULL;
	}
}

TreeNode::TreeNode()
{
	leftChild = nullptr;
	rightChild = nullptr;
	lThread = true;
	rThread = true;
}
TreeNode::TreeNode(const int &nodeItem, TreeNode *left, TreeNode *right)
{
	data = nodeItem;
	leftChild = left;
	rightChild = right;
}
TreeNode::TreeNode(int item)
{
	// TreeNode *node = new TreeNode();
	data = item;
	leftChild = nullptr;
	rightChild = nullptr;
	lThread = true;
	rThread = true;
}

// retrieve Node
// not sure do we need this methods
TreeNode *ThreadedBSTree::findNode(TreeNode *root, int &item)
{
	//return treenode;
	if (root == nullptr)
	{
		return nullptr;
	}
	if (root->data == item)
	{
		return root;
	}
	else if (item > root->data)
	{
		if (!root->rThread)
		{
			return findNode(root->rightChild, item);
		}
	}
	else if (item < root->data)
	{
		if (!root->lThread)
		{
			return findNode(root->leftChild, item);
		}
	}
	return nullptr;
}

void ThreadedBSTree::removeEven(int number)
{
	for (int i = 1; i <= number; i++)
	{
		if (i % 2 == 0)
		{
			remove(i);
		}
	}
}

bool ThreadedBSTree::remove(int item)
{
	TreeNode *parent = NULL;
	return removeSearch(parent, root, item);
}

bool ThreadedBSTree::removeSearch(TreeNode *parent, TreeNode *tr, int &item)
{
	// TreeNode *parent;
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

void ThreadedBSTree::removeNode(TreeNode *node, TreeNode *parent)
{
	if (node->lThread && node->rThread)
	{
		//node has no child
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
		//return node;
	}
	else if (!node->lThread && !node->rThread)
	{
		// node has two child
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
		if (parent == NULL)
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
		//return nodeToConnect;
	}
}

int ThreadedBSTree::removeLeftMostNode(TreeNode *node)
{
	if (node->lThread)
	{
		// replaceNodeData = node->data;
		return node->data;
	}
	else
	{
		return removeLeftMostNode(node->leftChild);
	}
}

// this method is for reading input number from user
void ThreadedBSTree::enterNumber(int num)
{
	if (num <= 0)
	{
		cout << "Number can't be negative number and 0.";
		cout << " Please enter vaild number.";
		cout << endl;
	}
	else
	{
		cout << "Correct Number." << endl;
		// add(num);
	}
}

//
void ThreadedBSTree::add(vector<int> v, int nums, int low, int high)
{
	if (low > high)
	{
		return;
	}
	int mid = low + (high - low) / 2;
	int check = v[mid];

	insert(root, check);
	cout << check << " ";
	add(v, nums, low, mid - 1);

	add(v, nums, mid + 1, high);
}
void ThreadedBSTree::numbers(int num)
{
	vector<int> v;
	int x = 1;
	for (int i = 0; i < num; i++)
	{

		v.push_back(x);
		x++;
	}
	int end = v.size() - 1;
	cout << end << "-end\n";
	add(v, num, 0, end);
}
//
void ThreadedBSTree::insert(TreeNode *tr, int item)
{
	if (root == nullptr)
	{
		root = new TreeNode;
		root->data = item;
		root->lThread = true;
		root->rThread = true;
		// thread(root, item);
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
				TreeNode *nNode = new TreeNode;
				nNode->data = item;
				// thread after
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
				TreeNode *nNode = new TreeNode;
				nNode->data = item;
				// thread after
				tr->rThread = false;
				thread(tr, nNode, item);
			}
		}
	}
}

void ThreadedBSTree::thread(TreeNode *tr, TreeNode *nNode, int item)
{

	TreeNode *curr = nNode;
	TreeNode *ptr = tr;
	if (item < ptr->data)
	{
		if (ptr->lThread == false)
		{
			curr->rightChild = ptr;
			curr->leftChild = ptr->leftChild;
			ptr->leftChild = curr;
		}
	}
	else if (item > ptr->data)
	{
		if (ptr->rThread == false)
		{
			curr->rightChild = ptr->rightChild;
			curr->leftChild = ptr;
			ptr->rightChild = curr;
		}
	}
}
void ThreadedBSTree::display()
{
	cout << "Preorder: ";
	// preorderTraverse(root);
	cout << "\nInOrder: ";
	// inorderTraverse(root);
	cout << "\nPostorder: ";
	// postorderTraverse(root);
	cout << "\nInOrder TBST: ";
	displayTBSTreeInOrder(root);
}

bool ThreadedBSTree::contains(const int &anEntry) const
{
	if (root == nullptr)
	{
		return false;
	}
	TreeNode *temp = root;
	while (temp != nullptr)
	{
		if (anEntry == temp->data)
		{
			return true;
		}
		if (anEntry < temp->data)
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
		else if (anEntry > temp->data)
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

//------------------------------------------------------------
// Public Traversals Section.
//------------------------------------------------------------

void ThreadedBSTree::displayTBSTreeInOrder(TreeNode *root)
{
	TreeNode *curr = root;
	while (curr->lThread == false)
	{
		curr = curr->leftChild;
	}

	while (curr != nullptr)
	{
		cout << curr->data << " ";
		if (curr->rThread == true)
		{
			curr = curr->rightChild;
		}
		else
		{
			curr = curr->rightChild;
			while (curr->lThread == false)
			{
				curr = curr->leftChild;
			}
		}
	}
}
