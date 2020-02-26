#ifndef INCLUDE_OPERAND_H_
#define INCLUDE_OPERAND_H_

#include <string>
#include <memory>
#include <regex>
#include "Exceptions.h"
#include "Config.h"

class Operand;
using OperandPtr = std::shared_ptr<Operand>;

class Operand
{
public:
    enum class Type
    {
        NUMBER,
        BOOLEAN,
        VARIABLE
    };
    Operand(const std::string& symbol)
    {
        this->symbol = symbol;
        if (symbol == "true" or symbol == "false")
        {
            type = Type::BOOLEAN;
        }
        else if (std::regex_match(symbol, Config::numRe))
        {
            type = Type::NUMBER;
        }
        else if (std::regex_match(symbol, Config::varRe))
        {
            type = Type::VARIABLE;
        }
        else
        {
            DEBUG("Unrecognized token: " << symbol);
            throw InvalidExpression();
        }
        
    };

    bool isVariable()
    {
        return type == Type::VARIABLE;
    }

    std::string getSymbol()
    {
        return symbol;
    };

private:
    Type type;
    std::string symbol;
        
};

#endif /* INCLUDE_OPERAND_H_ */