#ifndef INCLUDE_SHUNTINGYARD_H_
#define INCLUDE_SHUNTINGYARD_H_

#include <vector>
#include <memory>
#include <unordered_map>
#include <stack>
#include "Operator.h"
#include "Node.h"

class ShuntingYard
{
    public:
        ShuntingYard(std::vector<OperatorPtr>);
        NodePtr infixToTree(std::vector<std::string>);
    private:
        std::unordered_map<std::string, OperatorPtr> operatorsMap;
        void addNode(std::stack<NodePtr>& stack, std::string op);
        bool isOperator(std::string str);
};

#endif /* INCLUDE_SHUNTINGYARD_H_ */