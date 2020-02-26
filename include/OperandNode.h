#ifndef INCLUDE_OPERANDNODE_H_
#define INCLUDE_OPERANDNODE_H_

#include <string>
#include <regex>
#include "Node.h"
#include "Operand.h"


class OperandNode : public Node
{
    public:
        OperandNode(OperandPtr operand, int depth) : Node(operand->getSymbol(), depth)
        {
            this->operand = operand;    
        }
    private:
        OperandPtr operand;
};

#endif /* INCLUDE_OPERANDNODE_H_ */