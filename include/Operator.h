#ifndef INCLUDE_OPERATOR_H_
#define INCLUDE_OPERATOR_H_

#include <string>
#include <memory>
#include "Exceptions.h"
#include "Utils.h"

class Operator;
using OperatorPtr = std::shared_ptr<Operator>;

class Operator
{
public:
    enum class Type
    {
        AND,
        OR,
        EQ,
        GT,
        GTE,
        LT,
        LTE,
        NOT
    };
    Operator(Type type)
    {
        this->type = type;
        rightAssociative = false;
        unary = false;
        precedence = 1;
        switch (this->type)
        {
            case Type::AND:
                symbol = "&&";
                break;
            case Type::OR:
                symbol = "||";
                break;
            case Type::EQ:
                symbol = "==";
                precedence = 2;
                break;
            case Type::GT:
                symbol = ">";
                precedence = 2;
                break;
            case Type::GTE:
                symbol = ">=";
                precedence = 2;
                break;
            case Type::LT:
                symbol = "<";
                precedence = 2;
                break;
            case Type::LTE:
                symbol = "<=";
                precedence = 2;
                break;
            case Type::NOT:
                symbol = "!";
                precedence = 3;
                unary = true;
                break;
            default:
                throw InvalidOperation();
        }
    };

    std::string getSymbol()
    {
        return symbol;
    };

    bool isUnary()
    {
        return unary;
    };

    bool isRightAssociative()
    {
        return rightAssociative;
    };

    int getPrecedence()
    {
        return precedence;
    };

    short comparePrecendence(OperatorPtr op2)
    {
        return precedence > op2->getPrecedence()
            ? 1
            : (precedence == op2->getPrecedence() ? 0 : -1);
    };

    double calc(double in1, double in2)
    {
        switch (this->type)
        {
            case Type::AND:
                return in1 && in2;
            case Type::OR:
                return in1 or in2;
            case Type::EQ:
                return in1 == in2;
            case Type::GT:
                return in1 > in2;
            case Type::GTE:
                return in1 >= in2;
            case Type::LT:
                return in1 < in2;
            case Type::LTE:
                return in1 <= in2;
            case Type::NOT:
            default:
                throw InvalidOperation();
        };
    };

    double calc(double in, bool throw_=false)
    {
        switch (this->type)
        {
            case Type::NOT:
                return !in;
            case Type::AND:
                if (!in)
                {
                    return 0;
                }
                return NA_VALUE;
            case Type::OR:
                if (in)
                {
                    return 1;
                }
                return NA_VALUE;
            case Type::EQ:
            case Type::GT:
            case Type::GTE:
            case Type::LT:
            case Type::LTE:
            default:
                if (throw_) throw InvalidOperation();
                else return NA_VALUE;
        };
    };

    std::string quotedSymbol()
    {
        switch (this->type)
        {
            case Type::AND:
            case Type::EQ:
            case Type::GT:
            case Type::GTE:
            case Type::LT:
            case Type::LTE:
                return symbol;
            case Type::OR:
                return "\\|\\|";
            case Type::NOT:
                return "\\!";
            default:
                throw InvalidOperation();
        };
    };
private:
    Type type;
    std::string symbol;
    bool rightAssociative;
    int precedence;
    bool unary;
        
};

#endif /* INCLUDE_OPERATOR_H_ */