#ifndef INCLUDE_CONFIG_H_
#define INCLUDE_CONFIG_H_

#include <string>
#include <vector>
#include <regex>
#include "Operator.h"

/**
 * Lib configuration
 * 
 * - regex used in order to tokenize the expression
 * - allowed operator
 */
namespace Config {
    std::string numReString = "-?[0-9]?([0-9]*[.])?[0-9]+";
    std::string varReString = "[a-zA-Z][a-zA-Z0-9]*";
    std::regex numRe(numReString);
    std::regex varRe(varReString);

    std::vector<OperatorPtr> operators = {
        std::make_shared<Operator>(Operator::Type::AND),
        std::make_shared<Operator>(Operator::Type::OR),
        std::make_shared<Operator>(Operator::Type::EQ),
        std::make_shared<Operator>(Operator::Type::LT),
        std::make_shared<Operator>(Operator::Type::LTE),
        std::make_shared<Operator>(Operator::Type::GT),
        std::make_shared<Operator>(Operator::Type::GTE),
        std::make_shared<Operator>(Operator::Type::NOT)
    };
}

#endif /* INCLUDE_CONFIG_H_ */