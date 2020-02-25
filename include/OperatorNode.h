#ifndef INCLUDE_OPERATORNODE_H_
#define INCLUDE_OPERATORNODE_H_

#include "Node.h"
#include "Operator.h"

class OperatorNode : public Node
{
    public:
        OperatorNode(OperatorPtr op, NodePtr leftChild, NodePtr rightChild, int depth) : Node(op->getSymbol(), leftChild, rightChild, depth)
        {
            this->op = op;
        }
        OperatorNode(OperatorPtr op, NodePtr child, int depth) : Node(op->getSymbol(), child, depth)
        {
            this->op = op;
        }
    private:
        OperatorPtr op;
};

#endif /* INCLUDE_OPERATORNODE_H_ */