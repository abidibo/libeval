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

/**
 * Operand class
 * 
 * Operands can be values (all converted to double), or variables
 * which needs to be set
 */
class Operand
{
public:
    enum class Type
    {
        VALUE,
        VARIABLE
    };
    /**
     * Constructor
     * 
     * Constructs the instance and detects the operand type
     * @param symbol: the operand symbol (token)
     */
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
            value = NAN;
        }
        else
        {
            DEBUG("Unrecognized token: " << symbol);
            throw InvalidExpression();
        }
    };

    /**
     * Check if the operand is of type variable
     * @return true if it's a variable, false otherwise
     */
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

    /**
     * Sets the operand value
     * 
     * This method is intended to be called upon variable operands,
     * throws an exception if called on value operands
     * @param val: the value to set
     * @return 0 if the value is unchanged
     *         1 if the value is changed
     * @throw InvalidAssignment if called on a value operand
     */
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