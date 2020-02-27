#ifndef INCLUDE_OPERANDNODE_H_
#define INCLUDE_OPERANDNODE_H_

#include <string>
#include <regex>
#include "Utils.h"
#include "Node.h"
#include "Operand.h"

class OperandNode;
using OperandNodePtr = std::shared_ptr<OperandNode>;

/**
 * Operand node class
 * 
 * Represents the operands of the expressions, these are
 * always leaves nodes, cannot have child
 */
class OperandNode : public Node
{
    public:
        /**
         * Operand node constructor
         * @param operand: the operand instance, can be a value or a variable
         * @param depth: depth of the node in the tree
         */
        OperandNode(OperandPtr operand, int depth) : Node(operand->getSymbol(), depth)
        {
            this->operand = operand;    
            value = this->operand->getValue();
        }
        /**
         * Value setter 
         * 
         * Sets the value of the operand, valid only for VARIABLE type operands
         * @param val: the value to set
         */
        int setValue(double val)
        {
            int res = operand->setValue(val);
            value = operand->getValue();
            return value;
        }
        /**
         * Calculates the value of the node
         * Just returns the operand value
         * @return the operand value
         */
        double calc()
        {
            value = operand->getValue();
        }
    private:
        OperandPtr operand;
};

#endif /* INCLUDE_OPERANDNODE_H_ */