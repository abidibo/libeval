#include "Operator.h"

using namespace std;

Operator::Operator(string symbol, bool rightAssociative, short precedence, bool unary)
{
    this->symbol = symbol;
    this->rightAssociative = rightAssociative;
    this->precedence = precedence;
    this->unary = unary;
}

string Operator::getSymbol()
{
    return symbol;
}

bool Operator::isRightAssociative()
{
    return rightAssociative;
}

int Operator::getPrecedence()
{
    return precedence;
}

bool Operator::isUnary()
{
    return unary;
}

short Operator::comparePrecendence(OperatorPtr op2)
{
    return precedence > op2->getPrecedence()
        ? 1
        : (precedence == op2->getPrecedence() ? 0 : -1);
}