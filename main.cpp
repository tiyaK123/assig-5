#include "ThreadedBSTree.h"
#include <cassert>
#include <iostream>

using namespace std;

void test()
{
    ThreadedBSTree tree;
    tree.numbers(20);
    cout << "\n" << tree;
    tree.remove(2);
   //tree.removeEven(10);
    tree.remove(2);
    //tree.remove(4);
    //tree.display();
    cout << "\n" << tree;
    cout << "\n----------------------------" << endl;
    ThreadedBSTree copyTree (tree);
    copyTree.remove(1);
    //copyTree.display();
    cout << "contains test: " << copyTree.contains(5) << endl;
    cout<< "\n" << copyTree;
}

int main()
{
    // ThreadedBSTree *bst = new ThreadedBSTree();
    test();
    //TreeNode* root = nullptr;
    //bst->display();
    //bst.preorderTraverse(root);
    cout << "----------------------------"<<endl;
    //inorderTraverse(root);
    // cout << endl;
    // bst.postorderTraverse(root);
}
