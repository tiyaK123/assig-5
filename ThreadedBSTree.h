//
//created by Ting-Shiuan Chen and Tiya Adugna on 3/1/21
//
// This is a Threaded Binary Search Tree class.
// It includes the TreeNode class that is created a Node for Threaded BSTree
// class.
// Also, it includes methods such as findNode, remove, add, insert, contains,
// clear, display, thread, and inorder Traversal for helping to build TBSTree
// and using TBStree.

// #ifdef ASS5_TBST_H
// #define ASS5_TBST_H

#include <iostream>
#include <ostream>
#include <vector>
using namespace std;

class ThreadedBSTree;
class TreeNode
{
   friend class ThreadedBSTree;
   friend ostream &operator<<(ostream &out, const ThreadedBSTree &bts);

private:
   int data;
   TreeNode *leftChild;
   TreeNode *rightChild;
   bool lThread;
   bool rThread;

public:
   TreeNode();
   TreeNode(int data); // NOLINT
   TreeNode(const int &nodeItem, TreeNode *left, TreeNode *right);
};

class ThreadedBSTree
{
   friend class TreeNode;
   friend ostream &operator<<(ostream &out, const ThreadedBSTree &bts);

private:
   TreeNode *root;
   void clear(TreeNode *root);
   bool removeSearch(TreeNode *parent, TreeNode *tr, const int &item);
   void removeNode(TreeNode *node, TreeNode *parent);
   int removeLeftMostNode(TreeNode *node);

public:
   ThreadedBSTree();
   ~ThreadedBSTree();
   ThreadedBSTree(const ThreadedBSTree &other);
   void removeEven(int number);
   bool remove(int item);
   void insert(TreeNode *tr, int item);
   void thread(TreeNode *tr, TreeNode *nNode, int item);
   /**
 * returns true if item is in the TBST
 * pre-con: none
 * post-con: goes through the TBST and checks if item 
 * 			 is in tree
 * **/
   bool contains(const int &item) const;

   void add(vector<int> v, int start, int end);
   void numbers(int num);
   // Copy assignment operator
   ThreadedBSTree &operator=(const ThreadedBSTree &other) = delete;

   // move constructor
   ThreadedBSTree(ThreadedBSTree &&other) = default;

   // move assignment operator
   ThreadedBSTree &operator=(ThreadedBSTree &&other) = delete;
};
//#endif //ASS5_TBST_H
