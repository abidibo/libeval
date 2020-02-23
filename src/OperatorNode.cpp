#include "OperatorNode.h"
#include <iostream>

OperatorNode::OperatorNode(OperatorPtr op, NodePtr leftChild, NodePtr rightChild, int depth) : Node(op->getSymbol(), leftChild, rightChild, depth)
{
    this->op = op;
}

OperatorNode::OperatorNode(OperatorPtr op, NodePtr child, int depth) : Node(op->getSymbol(), child, depth)
{
    this->op = op;
}