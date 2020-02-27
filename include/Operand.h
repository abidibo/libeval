#ifndef INCLUDE_OPERAND_H_
#define INCLUDE_OPERAND_H_

#include <string>
#include <memory>
#include <regex>
#include "Exceptions.h"
#include "Config.h"
#include "Utils.h"

class Operand;
using OperandPtr = std::shared_ptr<Operand>;

class Operand
{
public:
    enum class Type
    {
        VALUE,
        VARIABLE
    };
    Operand(const std::string& symbol)
    {
        this->symbol = symbol;
        if (symbol == "true" or symbol == "false")
        {
            type = Type::VALUE;
            value = symbol == "true" ? 1 : 0;
        }
        else if (std::regex_match(symbol, Config::numRe))
        {
            type = Type::VALUE;
            value = std::stod(symbol);
        }
        else if (std::regex_match(symbol, Config::varRe))
        {
            type = Type::VARIABLE;
            value = NA_VALUE;
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

    double getValue()
    {
        return value;
    }

    int setValue(double val)
    {
        if (!isVariable())
        {
            DEBUG("Cannot set a number operand " << symbol << " to a new value" << val);
            throw InvalidAssignment();
        }
        DEBUG("Setting variable value " << symbol << " = " << val);
        if (val == value) return 0;
        value = val;
        return 1;
    }

private:
    Type type;
    std::string symbol;
    double value;
        
};

#endif /* INCLUDE_OPERAND_H_ */