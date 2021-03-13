/**
 * Threaded Binary Tree
 * --------------------
 * ThreadedBSTree.h
 * --------------------
 * Threaded Binary Tree  both left and right NULL pointers are made to
 *  point to inorder predecessor and inorder successor respectively.
 *  The threads makes fast accessing ancestors of a node.
 *  It includes the TreeNode class that is created a Node for Threaded BSTree
 *  class. Also, it includes methods such as remove, add, insert, contains,
 *  clear, thread, and inorder Traversal for helping to build TBSTree
 *  and using TBStree.
 * Date: Date: 2/12/2021
 * Strudent: Ting-Shiuan Chen and Tiya Adugna
 * **/

// #ifdef ASS5_TBST_H
// #define ASS5_TBST_H

#include <iostream>
#include <ostream>
#include <vector>
using namespace std;

class ThreadedBSTree;
class TreeNode {
  friend class ThreadedBSTree;
  // Overload the operator and displays inorder traversals
  friend ostream &operator<<(ostream &out, const ThreadedBSTree &bts);

private:
  int data;
  TreeNode *leftChild;
  TreeNode *rightChild;
  bool lThread;
  bool rThread;

public:
  /** constructor sets leftchild and rightChild to null
   * and lThread and rThread to true
   **/
  TreeNode();
  // constructor take add as parameters
  TreeNode(int item);
  // constructor take nodeItem, left, and right as parameters
  TreeNode(const int &nodeItem, TreeNode *left, TreeNode *right);
};

class ThreadedBSTree {
  friend class TreeNode;
  // Overload the operator and displays inorder traversals
  friend ostream &operator<<(ostream &out, const ThreadedBSTree &bts);

private:
  TreeNode *root;
  // helper method deletes individual nodes
  void clear(TreeNode *root);
  /**
   * returns true if the item is found and removed from TBST
   * pre-con: the item has to be in the TBST
   * post-con: go through the TBST recursively and when found calls
   * 			 removeNode method to delete the node from tree and
   * 		     returns true
   * **/
  bool removeSearch(TreeNode *parent, TreeNode *tr, const int &item);
  /**
   * removes the node from TBST
   * pre-con: the node to be removed has to be in thr TBST
   * post-con: true, the node successfully removed
   * 			false, the node not in the TBST
   * **/
  void removeNode(TreeNode *node, TreeNode *parent);

public:
  // constructor sets root to null
  ThreadedBSTree();
  // destructor will delete individual nodes
  ~ThreadedBSTree();
  // copy constructor
  ThreadedBSTree(const ThreadedBSTree &other);
  /**
   * removes even numbers in the TBST
   * pre-con: none
   * post-con:none
   * **/
  void removeEven(int number);
  /**
   * return true if the node of the item is found
   * pre-con: the number has to be in the TBST
   * post-con: if the number exist it calls the
   * 			 helper method removeSearch to get the node
   * **/
  bool remove(int item);
  /**
   * adds the item and calls thread method if the node is a leaf
   * pre-con: the item must not be in the TBST
   * post-con: creats new node and adds item and calls
   * 			 thread method if its the leaf
   * **/
  void insert(TreeNode *tr, int item);
  /**
   * This is a method for connecting to be ThreadBST
   * pre-con: there is a parent node and nNode that have to connect
   * together.
   * post-con: two node are connect together and both are connect
   * like ThreadBST
   * **/
  void thread(TreeNode *tr, TreeNode *nNode, int item);
  /**
   * returns true if item is in the TBST
   * pre-con: none
   * post-con: goes through the TBST and checks if item
   * 			 is in tree
   * **/
  bool contains(const int &item) const;
  /**
   * inserts numbers from the vector to the TBST in a
   * balnced manner
   * pre-con: the vector should have elements in a sorted manner
   * post-con: inserts numbers in TBST in a balanced manner from
   * 			 vector by insering the midpoint (n/2)
   * **/
  void add(vector<int> v, int start, int end);
  /**
   * adds the numbers to the vector in a sorted manner
   * pre-con: none
   * post-con: none
   * **/
  void numbers(int num);
  // Copy assignment operator
  ThreadedBSTree &operator=(const ThreadedBSTree &other) = delete;

  // move constructor
  ThreadedBSTree(ThreadedBSTree &&other) = default;

  // move assignment operator
  ThreadedBSTree &operator=(ThreadedBSTree &&other) = delete;
};
//#endif //ASS5_TBST_H
