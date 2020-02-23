#include "Evaluator.h"
#include "Tokenizer.h"
#include "Operator.h"
#include "ShuntingYard.h"
#include "Utils.h"
#include "Node.h"
#include <iostream>
#include <vector>

using namespace std;

bool Evaluator::exec(std::string& expression,  std::map<std::string, std::string>& variables)
{
    // Let's tokenize the expression, get a vector of ordered tokens
    Tokenizer tokenizer{};
    vector<string>tokens;
    tokenizer.tokenize(expression, tokens);

    #ifdef DEBUG_BUILD
        for (auto t: tokens)
        {
            DEBUG("Token: " << t);
        }
    #endif

    // configure operators for shunting yard algorithm
    // @TODO configure tokenizer with same operators:
    // dynamically create the regex
    vector<OperatorPtr> operators;
    // @TODO pass calc value implementation in operators, in order to have
    // opeators nodes agnostic about calculation and just depending
    // on the passed operator
    operators.push_back(std::make_shared<Operator>("&&", false, 1, false));
    operators.push_back(std::make_shared<Operator>("||", false, 1, false));
    operators.push_back(std::make_shared<Operator>("<", false, 2, false));
    operators.push_back(std::make_shared<Operator>(">", false, 2, false));
    operators.push_back(std::make_shared<Operator>("==", false, 2, false));
    operators.push_back(std::make_shared<Operator>(">=", false, 2, false));
    operators.push_back(std::make_shared<Operator>("<=", false, 2, false));
    operators.push_back(std::make_shared<Operator>("!", false, 3, true));

    ShuntingYard shuntingYard(operators);
    NodePtr root = shuntingYard.infixToTree(tokens);
    DEBUG("\nTree\n");
    DEBUG("Root: " << root->getSymbol());
    DEBUG("Expression: " << expression);
    printTree(root, nullptr, false);

    return true;
}