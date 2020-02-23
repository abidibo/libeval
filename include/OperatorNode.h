#ifndef INCLUDE_OPERATORNODE_H_
#define INCLUDE_OPERATORNODE_H_

#include "Node.h"
#include "Operator.h"

class OperatorNode : public Node
{
    public:
        OperatorNode(OperatorPtr op, NodePtr leftChild, NodePtr rightChild, int depth);
        OperatorNode(OperatorPtr op, NodePtr child, int depth);
    private:
        OperatorPtr op;
};

#endif /* INCLUDE_OPERATORNODE_H_ */