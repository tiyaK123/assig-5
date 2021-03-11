#include "ThreadedBSTree.h"
#include <iostream>
using namespace std;

void test()
{
    ThreadedBSTree tree;
    // list of data :{1, 5, 8, 11, 15, 18, 20, 23, 26, 28, 30}
    tree.numbers(10);
    // tree.add(15);
    // tree.add(20);
    // tree.display();
    // tree.removeEven(10);
    //tree.display();
    ThreadedBSTree copyTree(tree);
    tree.display();
    cout << "copyTree: " << endl;
    copyTree.display();
    // tree.removeEven(10);
    // tree.remove(5);
    //tree.display();
    cout << endl;
    // cout << "copyTree: after delete: " << endl;
    // copyTree.display();
}

int main()
{
    // ThreadedBSTree *bst = new ThreadedBSTree();
    test();
    //TreeNode* root = nullptr;
    //bst->display();
    //bst.preorderTraverse(root);
    cout << endl;
    //inorderTraverse(root);
    // cout << endl;
    // bst.postorderTraverse(root);
}
