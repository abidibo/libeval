#include <iostream>
#include "Node.h"
#include "OperatorNode.h"
#include "OperandNode.h"

using namespace std;

Node::Node(string symbol)
{
    this->symbol = symbol;
}

Node::Node(string symbol, NodePtr child)
{
    this->symbol = symbol;
    this->leftChild = child;
}

Node::Node(string symbol, NodePtr leftChild, NodePtr rightChild)
{
    this->symbol = symbol;
    this->leftChild = leftChild;
    this->rightChild = rightChild;
}

string Node::getSymbol()
{
    return symbol;
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