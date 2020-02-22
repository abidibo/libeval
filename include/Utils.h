#ifndef INCLUDE_UTILS_H_
#define INCLUDE_UTILS_H_

#include <iostream>
#include <string>
#include "Node.h"

using namespace std;

#ifdef DEBUG_BUILD
#  define DEBUG(x) cerr << x << endl
#else
#  define DEBUG(x) do {} while (0)
#endif

struct Trunk
{
    Trunk *prev;
    string str;

    Trunk(Trunk *prev, string str)
    {
        this->prev = prev;
        this->str = str;
    }
};

// Helper function to print branches of the binary tree
inline void showTrunks(Trunk *p)
{
    if (p == nullptr)
        return;

    showTrunks(p->prev);

    cout << p->str;
}

// Recursive function to print binary tree
// It uses inorder traversal
inline void printTree(NodePtr root, Trunk *prev, bool isLeft)
{
    if (root == nullptr)
        return;
    
    string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);

    printTree(root->getLeftChild(), trunk, true);

    if (!prev)
        trunk->str = "---";
    else if (isLeft)
    {
        trunk->str = ".---";
        prev_str = "   |";
    }
    else
    {
        trunk->str = "`---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    cout << root->getSymbol() << endl;

    if (prev)
        prev->str = prev_str;
    trunk->str = "   |";

    printTree(root->getRightChild(), trunk, false);
}

#endif /* INCLUDE_UTILS_H_ */