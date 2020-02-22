#ifndef INCLUDE_EVALUATOR_H_
#define INCLUDE_EVALUATOR_H_

#include <string>
#include <memory>
#include <map>

class Evaluator
{
    public:
        bool exec(std::string& expression,  std::map<std::string, std::string>& variables);
};

#endif /* INCLUDE_EVALUATOR_H_ */
