
//
//created by Ting-Shiuan Chen and Tiya Adugna on 3/1/21
//
// This is a Threaded Binary Search Tree class.
// It includes the TreeNode class that is created a Node for Threaded BSTree
// class.
// Also, it includes methods such as findNode, remove, add, insert, contains,
// clear, display, thread, and inorder Traversal for helping to build TBSTree
// and using TBStree.

// #ifndef ASS4_SKIPLIST_H
// #define ASS4_SKIPLIST_H

#include <iostream>
#include <ostream>
#include <vector>
using namespace std;

class ThreadedBSTree;
class TreeNode
{
   friend class ThreadedBSTree;
   //friend std::ostream& operator<<(std::ostream& out, const TreeNode& bts);
private:
   int data;
   TreeNode *leftChild;
   TreeNode *rightChild;
   bool lThread;
   bool rThread;

public:
   TreeNode();
   TreeNode(int data);
   TreeNode(const int &nodeItem, TreeNode *left, TreeNode *right);
   //TreeNode* add(TreeNode* root, int item);
};
class ThreadedBSTree
{
   friend class TreeNode;
   friend std::ostream &operator<<(std::ostream &out, const ThreadedBSTree &bts);

private:
   TreeNode *root;

public:
   ThreadedBSTree();
   ~ThreadedBSTree();
   ThreadedBSTree(const ThreadedBSTree &tbst);
   TreeNode *copyTbst(TreeNode *other);
   void helper(TreeNode *&node, const TreeNode *therNode);
   TreeNode *findNode(TreeNode *root, int &item);
   void removeEven(int number);
   bool remove(int item);
   bool removeSearch(TreeNode *parent, TreeNode *tr, int &item);
   void removeNode(TreeNode *node, TreeNode *parent);
   int removeLeftMostNode(TreeNode *node);
   void enterNumber(int num);
   //void add(int item);                    // for loop for adding n number
   void insert(TreeNode *root, int item); // insert nuber in Tree
   void thread(TreeNode *root, TreeNode *newNode, int item);
   void clear(TreeNode *root);
   void display();
   bool contains(const int &item) const;
   void add(vector<int> v, int nums, int low, int high);
   void numbers(int num);
   //------------------------------------------------------------
   // Public Traversals Section.
   //------------------------------------------------------------

   void displayTBSTreeInOrder(TreeNode *root); // Thread inordertraversal
};
