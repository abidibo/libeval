#ifndef INCLUDE_UTILS_H_
#define INCLUDE_UTILS_H_

#include <iostream>
#include <string>
#include <limits>
#include "Console.h"

constexpr double DOUBLE_MAX_VALUE = std::numeric_limits<double>::max(); // 1.79769e+308
constexpr double DOUBLE_MIN_VALUE = -std::numeric_limits<double>::max();// 2.22507e-308, so we use -max as min value
constexpr double NA_VALUE = DOUBLE_MIN_VALUE; // @TODO check wrong comparison
constexpr double NAN = std::numeric_limits<double>::quiet_NaN();

// naeed NAN before this
#include "Node.h"

#ifdef DEBUG_BUILD
#  define DEBUG(x) std::cerr << x << std::endl
#else
#  define DEBUG(x) do {} while (0)
#endif


// starting from here just stuff used to log the AST to console
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

Color::Modifier red(Color::FG_RED);
Color::Modifier green(Color::FG_GREEN);
Color::Modifier blue(Color::FG_BLUE);
Color::Modifier def(Color::FG_DEFAULT);

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
    std::cout << red << root->getSymbol() << def << " " << root->id << def << blue << " (" << root->getDepth() << ") " << green << root->getValue() << def << std::endl;

    if (prev)
        prev->str = prev_str;
    trunk->str = "   |";

    printTree(root->getRightChild(), trunk, false, showValue);
}

#endif /* INCLUDE_UTILS_H_ */
