#include <regex>
#include "Tokenizer.h"

using namespace std;

int Tokenizer::tokenize(const string& infix, vector<string>& tokens)
{
    // var name: [a-zA-Z][a-zA-Z0-9]*
    // int or double: [0-9]?([0-9]*[.])?[0-9]+
    // AND, OR, ==, <=, <=, NOT, (, )
    std::regex words_regex("[a-zA-Z][a-zA-Z0-9]*|[0-9]?([0-9]*[.])?[0-9]+|&&|\\|\\||==|<=|>=|[<>\\!\\(\\)]"); 
    auto words_begin = std::sregex_iterator(infix.begin(), infix.end(), words_regex);
    auto words_end = std::sregex_iterator();

    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        tokens.push_back((*i).str());
    }

    return 0;
}