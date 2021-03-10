
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
   TreeNode* copyTbst(TreeNode *other);
   void helper(TreeNode *node, TreeNode *otherNode);
   TreeNode *findNode(TreeNode *root, int &item);
   bool remove(int item);
   void enterNumber(int num);
   //void add(int item);                    // for loop for adding n number
   void insert(TreeNode *root, int item); // insert nuber in Tree
   void thread(TreeNode *root, TreeNode *newNode, int item);
   void clear(TreeNode *root);
   void display();
   bool contains(const int &item) const;
   void add(vector<int> v, int nums,int low, int high);
   void numbers( int num);
   TreeNode *getleftMostNode();
   //------------------------------------------------------------
   // Public Traversals Section.
   //------------------------------------------------------------
   //void preorderTraverse(TreeNode *root);
   void inorderTraverse(TreeNode *root); // normal inoderTraversal
   //void postorderTraverse(TreeNode *root);
   void displayTBSTreeInOrder(TreeNode *root); // Thread inordertraversal
};
