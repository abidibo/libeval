#ifndef INCLUDE_SHUNTINGYARD_H_
#define INCLUDE_SHUNTINGYARD_H_

#include <algorithm>
#include <vector>
#include <memory>
#include <map>
#include <unordered_map>
#include <stack>
#include "Exceptions.h"
#include "Utils.h"
#include "Operator.h"
#include "Operand.h"
#include "Node.h"
#include "OperatorNode.h"
#include "OperandNode.h"

class ShuntingYard
{
public:
    ShuntingYard(std::vector<OperatorPtr> operators)
    {
        for (auto op: operators)
        {
            operatorsMap[op->getSymbol()] = op;
        }
    }
    NodePtr infixToTree(std::vector<std::string>& infix, std::unordered_map<std::string, std::vector<NodePtr>>& deps)
    {
        std::stack<std::string> operatorStack;
        std::stack<NodePtr> operandStack;
        for (auto token: infix)
        {
            std::string popped;
            if (token == "(")
            {
                operatorStack.push(token);
            }
            else if (token == ")")
            {
                bool err = true;
                while(!operatorStack.empty())
                {
                    popped = operatorStack.top();
                    operatorStack.pop();
                    if (popped == "(")
                    {
                        err = false;
                        break;
                    }
                    else
                    {
                        addNode(operandStack, popped);
                    }
                }
                if (err)
                {
                    DEBUG("Unbalanced right parantheses");
                    throw InvalidExpression();
                }
            }
            else if (isOperator(token))
            {
                OperatorPtr op = operatorsMap[token];
                OperatorPtr op2;
                while (!operatorStack.empty())
                {
                    if (isOperator(operatorStack.top()))
                    {
                        op2 = operatorsMap[operatorStack.top()];
                    }
                    else break;
                    // pop all operators with greater precedence
                    if ((!op->isRightAssociative() and 0 == op->comparePrecendence(op2)) or op->comparePrecendence(op2) < 0)
                    {
                        operatorStack.pop();
                        addNode(operandStack, op2->getSymbol());
                    }
                    else break;
                }
                operatorStack.push(op->getSymbol());
            }
            else
            {
                OperandPtr operand = std::make_shared<Operand>(token);
                NodePtr operandNode = std::make_shared<OperandNode>(operand, 1);
                if (operand->isVariable())
                {
                    DEBUG("Found variable " << token);
                    deps[token].push_back(operandNode);
                }
                operandStack.push(operandNode);
            }
        }

        // now consider all remaining operators in stack
        while (!operatorStack.empty())
        {
            addNode(operandStack, operatorStack.top());
            operatorStack.pop();
        }

        return operandStack.top();
    }
private:
    std::unordered_map<std::string, OperatorPtr> operatorsMap;
    void addNode(std::stack<NodePtr>& stack, std::string op)
    {
        if (operatorsMap[op]->isUnary())
        {
            NodePtr leftChild = stack.top();
            stack.pop();
            stack.push(std::make_shared<OperatorNode>(operatorsMap[op], leftChild, nullptr, leftChild->getDepth() + 1));
        }
        else
        {
            NodePtr rightChild = stack.top();
            stack.pop();
            NodePtr leftChild = stack.top();
            stack.pop();
            int depth = std::max(rightChild->getDepth(), leftChild->getDepth()) + 1;
            stack.push(std::make_shared<OperatorNode>(operatorsMap[op], leftChild, rightChild, depth));
        }
    }
    bool isOperator(std::string str)
    {
        return operatorsMap.find(str) != operatorsMap.end();
    }
};

#endif /* INCLUDE_SHUNTINGYARD_H_ */