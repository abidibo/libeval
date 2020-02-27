#ifndef INCLUDE_OPERATOR_H_
#define INCLUDE_OPERATOR_H_

#include <string>
#include <memory>
#include "Exceptions.h"
#include "Utils.h"

class Operator;
using OperatorPtr = std::shared_ptr<Operator>;

/**
 * Operator class
 * 
 * This is class is used to actually perform calculations
 * An operator can be of many types, defined in the enum Type
 */
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
    /**
     * Construct an operator instance of Type type
     * 
     * Operators can be:
     * - unary/binary
     * - right/left/both associative
     * - have different precedence
     * 
     * @param type
     * @throw InvalidOperation if a wrong type is passed
     */
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

    /**
     * Compares the precedence of this operator agains the given one
     * @param op2: the operator to compare
     */
    short comparePrecendence(OperatorPtr op2)
    {
        return precedence > op2->getPrecedence()
            ? 1
            : (precedence == op2->getPrecedence() ? 0 : -1);
    };

    /**
     * Performs the calculation of a binary operator
     * @param in1 left input
     * @param in2 right input
     * @return operation result
     * @throw InvalidOperation
     */
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

    /**
     * Performs the calculation of a unary or binary operator
     * 
     * If called on a binary operator it tryes to calculate the result with 
     * just one operand if possible, i.e. AND false, OR true.
     * If it cannot calculate the result, NAN is returned.
     * 
     * @param in input
     * @return operation result
     * @throw InvalidOperation
     */
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
                return NAN;
            case Type::OR:
                if (in)
                {
                    return 1;
                }
                return NAN;
            case Type::EQ:
            case Type::GT:
            case Type::GTE:
            case Type::LT:
            case Type::LTE:
            default:
                if (throw_) throw InvalidOperation();
                else return NAN;
        };
    };

    /**
     * Returns a quoted string of the operator symbol to be used 
     * in a regex
     * @return quoted symbol
     */
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