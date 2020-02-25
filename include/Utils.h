#ifndef INCLUDE_UTILS_H_
#define INCLUDE_UTILS_H_

#include <iostream>
#include <string>
#include "Node.h"

#ifdef DEBUG_BUILD
#  define DEBUG(x) std::cerr << x << std::endl
#else
#  define DEBUG(x) do {} while (0)
#endif

struct Trunk
{
    Trunk *prev;
    std::string str;

    Trunk(Trunk *prev, std::string str)
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

    std::cout << p->str;
}

// Recursive function to print binary tree
// It uses inorder traversal
inline void printTree(NodePtr root, Trunk *prev, bool isLeft)
{
    if (root == nullptr)
        return;
    
    std::string prev_str = "    ";
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
    std::cout << root->getSymbol() << " " << root->getDepth() << std::endl;

    if (prev)
        prev->str = prev_str;
    trunk->str = "   |";

    printTree(root->getRightChild(), trunk, false);
}

#endif /* INCLUDE_UTILS_H_ */