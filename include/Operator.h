#ifndef INCLUDE_OPERATOR_H_
#define INCLUDE_OPERATOR_H_

#include <string>
#include <memory>

class Operator;
using OperatorPtr = std::shared_ptr<Operator>;

class Operator
{
    public:
        Operator(std::string symbol, bool rightAssociative, short precedence, bool unary);
        std::string getSymbol();
        bool isUnary();
        bool isRightAssociative();
        int getPrecedence();
        short comparePrecendence(OperatorPtr op2);
    private:
        std::string symbol;
        bool rightAssociative;
        int precedence;
        bool unary;
        
};

#endif /* INCLUDE_OPERATOR_H_ */