#ifndef INCLUDE_TOKENIZER_H_
#define INCLUDE_TOKENIZER_H_

#include <string>
#include <vector>
#include <regex>
#include "Operator.h"
#include "Config.h"

class Tokenizer
{
public:
    int tokenize(const std::string& infix, std::vector<OperatorPtr> operators, std::vector<std::string>& tokens)
    {
        // std::regex words_regex("[a-zA-Z][a-zA-Z0-9]*|[0-9]?([0-9]*[.])?[0-9]+|&&|\\|\\||==|<=|>=|[<>\\!\\(\\)]"); 
        std::string re;
        re += Config::varReString;
        re += "|"; // or
        re += Config::numReString;
        re += "|"; // or
        re += "[//(//)]"; // open or close parenthesis
        for (auto op: operators)
        {
            re += "|"; // or
            re += op->quotedSymbol(); // all operators
        }
        std::regex words_regex(re); 
        auto words_begin = std::sregex_iterator(infix.begin(), infix.end(), words_regex);
        auto words_end = std::sregex_iterator();

        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            tokens.push_back((*i).str());
        }

        return 0;
    }
};

#endif /* INCLUDE_TOKENIZER_H_ */