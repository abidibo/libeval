#include <algorithm>
#include "ShuntingYard.h"
#include "Exceptions.h"
#include "OperatorNode.h"
#include "OperandNode.h"
#include "Utils.h"
using namespace std;

ShuntingYard::ShuntingYard(vector<OperatorPtr> operators)
{
    for (auto op: operators)
    {
        operatorsMap[op->getSymbol()] = op;
    }
}

void ShuntingYard::addNode(stack<NodePtr>& stack, string op)
{
    if (operatorsMap[op]->isUnary())
    {
        NodePtr leftChild = stack.top();
        stack.pop();
        stack.push(make_shared<OperatorNode>(operatorsMap[op], leftChild, nullptr, leftChild->getDepth() + 1));
    }
    else
    {
        NodePtr rightChild = stack.top();
        stack.pop();
        NodePtr leftChild = stack.top();
        stack.pop();
        int depth = max(rightChild->getDepth(), leftChild->getDepth()) + 1;
        stack.push(make_shared<OperatorNode>(operatorsMap[op], leftChild, rightChild, depth));
    }
}

bool ShuntingYard::isOperator(string str)
{
    return operatorsMap.find(str) != operatorsMap.end();
}

NodePtr ShuntingYard::infixToTree(vector<string> infix)
{
    stack<string> operatorStack;
    stack<NodePtr> operandStack;
    for (auto token: infix)
    {
        string popped;
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
                throw invalid_expression();
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
            operandStack.push(make_shared<OperandNode>(token, nullptr, nullptr, 1)) ;
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