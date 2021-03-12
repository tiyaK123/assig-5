/**
 * Threaded Binary Tree
 * --------------------
 * main.cpp
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
#include "ThreadedBSTree.h"
#include <cassert>
#include <iostream>

using namespace std;
// Prints inorder traversal tests constructor, remove, add, and contains
void test()
{
    ThreadedBSTree tree;
    int num = 11;
    int num1 = 5;
    tree.numbers(num);
    cout << " Inorder traversal: " << tree << endl;
    tree.removeEven(num);
    cout << " Remove even: " << tree << endl;
    if(tree.contains(num1)){
        cout <<  " Contains test: " << num1 << endl;
    }
    
}

// Prints inorder traversal tests copy constructor, remove, add, and contains
void test2()
{
    ThreadedBSTree tree;
    ThreadedBSTree copyTree (tree);
    int num = 11;
    int num1 = 5;
    tree.numbers(num);
    cout << " Inorder traversal: " << copyTree << endl;
    copyTree.removeEven(num);
    cout << " Remove even: " <<copyTree<< endl;
    if(copyTree.contains(num1)){
        cout << " Contains test: " << num1 << endl;
    }
    
 }
int main()
{
     cout << "\nTest 1" << endl;
     test();
     cout << "\n----------------------------\n" << endl;
     cout << "Test 2" << endl;
     test();
     cout << "\n----------------------------\n" << endl;
}
