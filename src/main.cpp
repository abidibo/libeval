#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include "Evaluator.h"
#include <vector>
#include <regex>
#include "Utils.h"
#include "Console.h"

using namespace std;

int main(int argc, char **argv) {
    std::string expr = "(v0 == 2 || (v1 > 10  && v2 > -23)) && v3 == -15.000000001 && v4";
    Evaluator eval{};
    eval.compile(expr);

    // calc from root
    DEBUG(green << "\nComplete calc from tree root" << def);
    std::unordered_map<string, double> values;
    values["v0"] = 1.0;
    values["v1"] = 15.5;
    values["v2"] = -10.0;
    values["v3"] = -15.000000001;
    eval.setValues(values);
    eval.setValue("v4", true);
    bool res = eval();
    DEBUG (std::endl << "RESULT" << std::endl);
    DEBUG("Res: " << res);
    DEBUG(green << "\nExecute again without changing anything" << def);
    res = eval();
    DEBUG("Res: " << res);
    DEBUG(green << "\nExecute again changing one var" << def);
    DEBUG("Every node from infected one up to root should be calculated again with this change");
    eval.setValue("v3", 9);
    res = eval();
    DEBUG("Res: " << res);

    // calc from root
    DEBUG(green << "\nCalc exits immediately because of AND false" << def);
    eval.compile(expr);
    values["v0"] = 1.0;
    values["v1"] = 15.5;
    values["v2"] = -10.0;
    values["v3"] = -15.000000001;
    eval.setValues(values);
    eval.setValue("v4", false);
    res = eval();
    DEBUG (std::endl << "RESULT" << std::endl);
    DEBUG("Res: " << res);

    // calc from root
    DEBUG(green << "\nFrom root again" << def);
    values["v0"] = 1.0;
    values["v1"] = 15.5;
    values["v2"] = -10.0;
    values["v3"] = -15.000000002;
    eval.setValues(values);
    eval.setValue("v4", true);
    res = eval();
    DEBUG (std::endl << "RESULT" << std::endl);
    DEBUG("Res: " << res);
    DEBUG(green << "\nRe calc from botton stops before reaching root node" << def);
    DEBUG("Just one change, and doesn't cause a change in the parent operator node, so the calculation stops and prev root value is considered");
    eval.setValue("v3", 2);
    res = eval();
    DEBUG("Res: " << res);

    /*
    std::string expr = "KeyOff && (EngineSpeed <= 100) && (ActualEngine_PercTorque == 1500)";
    Evaluator eval{};
    eval.compile(expr);

    // calc from root
    DEBUG(green << "\nComplete calc from tree root" << def);
    std::unordered_map<string, double> values;
    values["KeyOff"] = 0;
    values["EngineSpeed"] = 450;
    values["ActualEngine_PercTorque"] = 1500;
    eval.setValues(values);
    bool res = eval();
    DEBUG (std::endl << "RESULT" << std::endl);
    DEBUG("Res: " << res);
    DEBUG(green << "\nExecute again without changing anything" << def);
    res = eval();
    DEBUG("Res: " << res);
    DEBUG(green << "\nExecute again changing one var" << def);
    DEBUG("Every node from infected one up to root should be calculated again with this change");
    eval.setValue("KeyOff", 1);
    res = eval();
    DEBUG("Res: " << res);
    */
}