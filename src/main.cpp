#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include "Evaluator.h"
#include <vector>
#include <regex>

using namespace std;

int main(int argc, char **argv) {
    Evaluator eval{};
    Evaluator eval2{};
    std::map<std::string, std::string> m;
    std::string e1 = "v0 == 1";
    // std::string e1 = "v2 > 5 || (v0 == 1) && v2";
    std::string e2 = "(v0 == 2 || v1 > 10)";
    // std::string e3 = "(v0 == 2 || (v1 > 10  && v2 < 3 || !v4 && true)) && v3 == -55.5 || v1";
    std::string e3 = "(v0 == 2 || (v1 > 10  && v2 > 3) || (v1 > 10  && v2 > 3)) && v3 == 0";
    std::string e4 = "(v0 == 2 || (v1 > 10  && v2 > -3)) && v3 == -15.000000001 && !v4";
    std::string e5 = "(v0 == 2 || (v1 > 10  && v2 > -23)) && v3 == -15.000000001 && v4";
    std::string e6 = "((v0==2 || (v1 > 10  && v2 > 3)) && v3 == -15.000000001 && v4) && (v5 == !v4)";
    std::string e7 = "true";
    m["v0"] = "1";
    m["v1"] = "15.55";
    m["v2"] = "-10";
    m["v3"] = "-15.000000001";
    m["v4"] = "false";
    m["v5"] = "false";
    eval.compile(e5);
    std::unordered_map<string, double> values;
    values["v0"] = 1.0;
    values["v1"] = 15.5;
    values["v2"] = -10.0;
    values["v3"] = -15.000000001;
    eval.setValues(values);
    eval.setValue("v4", true);

    // eval.setValue("v5", false);
    // eval2.compile(e2);
    bool res = eval();
    std::cout << "Result: " << res << std::endl;
    bool res2 = eval();
    std::cout << "Result 2: " << res2 << std::endl;
    eval.setValue("v3", -15.000000002);
    // eval.setValue("v4", false);

    bool res3 = eval();
    std::cout << "Result 3: " << res3 << std::endl;
    // bool testCorrect = 
    //     (eval.exec(e1, m) &&
    //      eval.exec(e2, m) && 
    //      !eval.exec(e3, m) && 
    //      !eval.exec(e4, m) &&
    //      eval.exec(e5, m) && 
    //      eval.exec(e6, m) &&
	//  eval.exec(e7, m));
    // std::cout << (testCorrect ? "Good job!" : "Uhm, please retry!") << std::endl;
}