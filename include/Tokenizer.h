#ifndef INCLUDE_TOKENIZER_H_
#define INCLUDE_TOKENIZER_H_

#include <string>
#include <vector>

class Tokenizer
{
    public:
        int tokenize(const std::string& infix, std::vector<std::string>& tokens);
};

#endif /* INCLUDE_TOKENIZER_H_ */