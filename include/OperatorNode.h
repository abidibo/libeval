#ifndef INCLUDE_OPERATORNODE_H_
#define INCLUDE_OPERATORNODE_H_

#include "Node.h"
#include "Operator.h"
#include "Utils.h"

class OperatorNode : public Node
{
    public:
        OperatorNode(OperatorPtr op, NodePtr leftChild, NodePtr rightChild, int depth) : Node(op->getSymbol(), leftChild, rightChild, depth)
        {
            this->op = op;
        };

        OperatorNode(OperatorPtr op, NodePtr child, int depth) : Node(op->getSymbol(), child, depth)
        {
            this->op = op;
        };

        double calc ()
        {
            if (!rightChild)
            {
                double in = leftChild->calc();   
                value = op->calc(in);
            }
            else
            {
                double res;
                if (leftChild->getDepth() <= rightChild->getDepth())
                {
                    double in1 = leftChild->calc();
                    if((res = op->calc(in1)) == NA_VALUE)
                    {
                        double in2 = rightChild->calc();
                        value = op->calc(in1, in2);
                    }
                    else value = res;
                }
                else
                {
                    double in2 = rightChild->calc();
                    int res = op->calc(in2);
                    if((res = op->calc(in2)) == NA_VALUE)
                    {
                        double in1 = leftChild->calc();
                        value = op->calc(in1, in2);
                    }
                    else value = res;
                }
            }

            return value;
        }
    private:
        OperatorPtr op;
};

#endif /* INCLUDE_OPERATORNODE_H_ */