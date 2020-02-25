#ifndef INCLUDE_OPERATOR_H_
#define INCLUDE_OPERATOR_H_

#include <string>
#include <memory>

class Operator;
using OperatorPtr = std::shared_ptr<Operator>;

class Operator
{
public:
    Operator(std::string symbol, bool rightAssociative, short precedence, bool unary)
    {
        this->symbol = symbol;
        this->rightAssociative = rightAssociative;
        this->precedence = precedence;
        this->unary = unary;
    }
    std::string getSymbol()
    {
        return symbol;
    }
    bool isUnary()
    {
        return unary;
    }
    bool isRightAssociative()
    {
        return rightAssociative;
    }
    int getPrecedence()
    {
        return precedence;
    }
    short comparePrecendence(OperatorPtr op2)
    {
        return precedence > op2->getPrecedence()
            ? 1
            : (precedence == op2->getPrecedence() ? 0 : -1);
    }
private:
    std::string symbol;
    bool rightAssociative;
    int precedence;
    bool unary;
        
};

#endif /* INCLUDE_OPERATOR_H_ */