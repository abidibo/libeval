#ifndef INCLUDE_EVALUATOR_H_
#define INCLUDE_EVALUATOR_H_

#include <string>
#include <memory>
#include <map>
#include <vector>
#include "Utils.h"
#include "Tokenizer.h"
#include "ShuntingYard.h"
#include "Operator.h"
#include "Config.h"

class Evaluator
{
public:
    /**
     * Builds a nodes tree given the literal expression
     * @param expression: the expression as string
     * @return  0 on success
     *         -1 on failure (invalid expression)
     */ 
    int compile(std::string& expression)
    {
        try
        {
            // tokenize the expression, get a vector of ordered tokens
            Tokenizer tokenizer{};
            std::vector<std::string>tokens;
            tokenizer.tokenize(expression, Config::operators, tokens);

            DEBUG("Expression: " << expression << std::endl);
            #ifdef DEBUG_BUILD
                for (auto t: tokens)
                {
                    DEBUG("Token: " << t);
                }
            #endif
            
            // build the tree
            ShuntingYard shuntingYard(Config::operators);
            std::map<std::string, std::vector<NodePtr>> deps;
            tree = shuntingYard.infixToTree(tokens, deps);
            DEBUG("\nTree\n");
            DEBUG("Root: " << tree->getSymbol());
            printTree(tree, nullptr, false);
            DEBUG("\nDependencies\n");
            for (auto v: deps)
            {
                DEBUG(v.first);
                for (auto n: v.second) {
                    DEBUG("\t" << n);
                }
            }
            return 0;
        }
        catch(const std::exception& e)
        {
            DEBUG(e.what());
            return -1;
        }
    };

    /**
     * Calculates the expression result given the input variables values 
     * @param variables: the var->value dictionary
     */
    bool operator()(std::map<std::string, std::string>& variables)
    {
        DEBUG("Evaluating");
    }
private:
    NodePtr tree;
};

#endif /* INCLUDE_EVALUATOR_H_ */
