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

constexpr static const double DOUBLE_MAX_VALUE = std::numeric_limits<double>::max(); // 1.79769e+308
constexpr static const double DOUBLE_MIN_VALUE = -std::numeric_limits<double>::max();// 2.22507e-308, so we use -max as min value
constexpr double NA_VALUE = -999999999;
// #define NA_VALUE 999999999

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
inline void printTree(NodePtr root, Trunk *prev, bool isLeft, bool showValue=false)
{
    if (root == nullptr)
        return;
    
    std::string prev_str = "    ";
    Trunk *trunk = new Trunk(prev, prev_str);

    printTree(root->getLeftChild(), trunk, true, showValue);

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
    if (showValue)
    {
        std::cout << root->getSymbol() << " V(" << root->getValue() << ")" << std::endl;
    }
    else
    {
        std::cout << root->getSymbol() << " D(" << root->getDepth() << ")" << std::endl;
    }

    if (prev)
        prev->str = prev_str;
    trunk->str = "   |";

    printTree(root->getRightChild(), trunk, false, showValue);
}

#endif /* INCLUDE_UTILS_H_ */