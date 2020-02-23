#include <iostream>
#include "Node.h"
#include "OperatorNode.h"
#include "OperandNode.h"

using namespace std;

Node::Node(string symbol, int depth)
{
    this->symbol = symbol;
    this->depth = depth;
}

Node::Node(string symbol, NodePtr child, int depth)
{
    this->symbol = symbol;
    this->leftChild = child;
    this->depth = depth;
}

Node::Node(string symbol, NodePtr leftChild, NodePtr rightChild, int depth)
{
    this->symbol = symbol;
    this->leftChild = leftChild;
    this->rightChild = rightChild;
    this->depth = depth;
}

string Node::getSymbol()
{
    return symbol;
}

int Node::getDepth()
{
    return depth;
}

NodePtr Node::getParent()
{
    return parent;
}

NodePtr Node::getLeftChild()
{
    return leftChild;
}

NodePtr Node::getRightChild()
{
    return rightChild;
}