#ifndef INCLUDE_OPERANDNODE_H_
#define INCLUDE_OPERANDNODE_H_

#include <string>
#include <regex>
#include "Utils.h"
#include "Node.h"
#include "Operand.h"

class OperandNode;
using OperandNodePtr = std::shared_ptr<OperandNode>;


class OperandNode : public Node
{
    public:
        OperandNode(OperandPtr operand, int depth) : Node(operand->getSymbol(), depth)
        {
            this->operand = operand;    
            value = this->operand->getValue();
        }
        int setValue(double val)
        {
            int res = operand->setValue(val);
            value = operand->getValue();
            return value;
        }
        double calc()
        {
            value = operand->getValue();
        }
    private:
        OperandPtr operand;
};

#endif /* INCLUDE_OPERANDNODE_H_ */