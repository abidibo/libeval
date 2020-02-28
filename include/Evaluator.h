#ifndef INCLUDE_EVALUATOR_H_
#define INCLUDE_EVALUATOR_H_

#include <string>
#include <memory>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <vector>
#include "Utils.h"
#include "Tokenizer.h"
#include "ShuntingYard.h"
#include "Operator.h"
#include "Config.h"

/**
 * Evaluator class
 * 
 * Class used to evaluete expressions. Usage:
 *
 * <pre>
 *   Evaluator eval{};
 *   eval.compile("v1 && (v2 > 8.8 || v3)");
 *   eval.set("v1", true);
 *   eval.set("v2", 10.0);
 *   eval.set("v3", false);
 *   bool res = eval.exec(); // true
 * </pre>
 */
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

            DEBUG(std::endl << "EXPRESSION" << std::endl);
            DEBUG(expression << std::endl);
            #ifdef DEBUG_BUILD
                for (auto t: tokens)
                {
                    DEBUG("Token: " << t);
                }
                DEBUG("");
            #endif
            
            // build the tree
            // make sure deps are cleared
            deps.clear();
            ShuntingYard shuntingYard(Config::operators);
            tree = shuntingYard.infixToTree(tokens, deps);

            DEBUG(std::endl << "TREE" << std::endl);
            DEBUG("Root: " << tree->getSymbol());
            printTree(tree, nullptr, false);
            DEBUG(std::endl << "DEPENDENCIES" << std::endl);
            for (auto v: deps)
            {
                uninitializedVariables.insert(v.first);
                #ifdef DEBUG_BUILD
                    DEBUG(v.first);
                    for (auto n: v.second) {
                        DEBUG("\t" << n);
                    }
                #endif
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
     * Sets the value of a variable
     * the value is passed to all nodes which depend on such variable
     * @param var: variable name
     * @param val: variable value
     * @return  0 on success
     *         -1 if the tree was not yet built
     *         -2 if the variable was not recognized
     */
    template<class A>
    int setValue(std::string var, A val)
    {
        if (!tree)
        {
            DEBUG("Cannot set values of uncompiled tree nodes");
            return -1;
        }

        if (deps.find(var) == deps.end())
        {
            DEBUG("Unrecognized variable");
            return -2;
        }

        for (auto n: deps[var])
        {
            // cast to double
            int res = std::dynamic_pointer_cast<OperandNode>(n)->setValue(double(val));
            if (res > 0)
            {
                infected.insert(n);
            }
        }
        uninitializedVariables.erase(var);
        return 0;
    }

    template<class A>
    int setValues(std::unordered_map<std::string,A> values)
    {
        int res;
        for (auto v: values)
        {
            if ((res = setValue(v.first, v.second)) != 0)
            {
                return res;
            }
        }
        return 0;
    }

    /**
     * Calculates the expression
     * @return result
     */
    double operator()()
    {
        return exec();
    }

    /**
     * Calculates the expression
     * @return result
     */
    double exec()
    {
        if (uninitializedVariables.size())
        {
            DEBUG("There are still uninitialized variables");
            throw UninitializedVariables();
        }

        if (!infected.size())
        {
            DEBUG(std::endl << "USING CACHED RESULT" << std::endl);
            return tree->getValue();
        }

        double res;
        if (infected.size() > 1)
        {
            DEBUG(std::endl << "EVALUATING FROM ROOT" << std::endl);
            res = tree->calc();
        }
        else
        {
            int rootDepth = tree->getDepth();
            auto node = std::move((*infected.begin()));
            DEBUG(std::endl << "EVALUATING FROM INFECTED NODE " << node->id << std::endl);
            int updateRes = 1;
            while(node->getDepth() < rootDepth and updateRes > 0)
            {
                node = node->getParent();
                DEBUG("UPDATING NODE " << node->id);
                updateRes = node->update();
            }
            res = tree->getValue();
        }
        
        printTree(tree, nullptr, false, true);
        infected.clear();
        return res;
    }
private:
    NodePtr tree = nullptr;
    std::unordered_map<std::string, std::vector<NodePtr>> deps;
    std::unordered_set<NodePtr> infected;
    std::unordered_set<std::string> uninitializedVariables;
};

#endif /* INCLUDE_EVALUATOR_H_ */
