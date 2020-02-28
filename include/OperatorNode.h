#ifndef INCLUDE_OPERATORNODE_H_
#define INCLUDE_OPERATORNODE_H_

#include "Node.h"
#include "Operator.h"
#include <math.h>
#include "Utils.h"

/**
 * Operator Node class 
 * 
 * A class which represents a node of type operator,
 * an operation performed on children (or child if unary operator)
 */
class OperatorNode : public Node
{
    public:
        /**
         * Binary operator constructor
         * @param op: the operator instance
         * @param leftChild: the left child node
         * @param rightChild: the right child node
         * @param depth: the node depth in the tree
         */
        OperatorNode(OperatorPtr op, NodePtr leftChild, NodePtr rightChild, int depth) : Node(op->getSymbol(), leftChild, rightChild, depth)
        {
            this->op = op;
        };
        /**
         * Unary operator constructor
         * @param op: the operator instance
         * @param Child: the child node
         * @param depth: the node depth in the tree
         */
        OperatorNode(OperatorPtr op, NodePtr child, int depth) : Node(op->getSymbol(), child, depth)
        {
            this->op = op;
        };
        /**
         * Node value calculator
         * 
         * Calculates the node value, stores, and returns it.
         * Calculation is done following at first the less deep branch,
         * because in same cases the computation can end before resolving
         * all the nodes, i.e AND false, OR true
         * @return the calculated node value
         */
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
                    res = op->calc(in1);
                    if(isnan(res))
                    {
                        double in2 = rightChild->calc();
                        value = op->calc(in1, in2);
                    }
                    else value = res;
                }
                else
                {
                    double in2 = rightChild->calc();
                    res = op->calc(in2);
                    if(isnan(res))
                    {
                        double in1 = leftChild->calc();
                        value = op->calc(in1, in2);
                    }
                    else value = res;
                }
            }

            return value;
        }

        /**
         * The node updates its value reconsidering only the new
         * infected child value and then looks at its new value:
         * - if changed returns 1
         * - if not changed returns 0
         */
        int update()
        {
            double newValue = rightChild
                ? op->calc(leftChild->getValue(), rightChild->getValue())
                : op->calc(leftChild->getValue());
            if (newValue != value) {
                value = newValue;
                return 1;
            }
            return 0;
        }
    private:
        OperatorPtr op;
};

#endif /* INCLUDE_OPERATORNODE_H_ */