#include <iostream>
#include <string>
#include <map>
#include "Evaluator.h"
#include <vector>
#include <regex>

using namespace std;

int main(int argc, char **argv) {


    Evaluator eval{};
    std::map<std::string, std::string> m;
    std::string e1 = "v0 == 1";
    // std::string e1 = "v2 > 5 || (v0 == 1) && v2";
    std::string e2 = "(v0 == 2 || v1 > 10)";
    std::string e3 = "(v0 == 2 || (v1 > 10  && v2 < 3 || !v4 && true)) && v3 == 0";
    // std::string e3 = "(v0 == 2 || (v1 > 10  && v2 > 3) || (v1 > 10  && v2 > 3)) && v3 == 0";
    std::string e4 = "(v0 == 2 || (v1 > 10  && v2 > 3)) && v3 == -15.000000001 && !v4";
    std::string e5 = "(v0 == 2 || (v1 > 10  && v2 > 3)) && v3 == -15.000000001 && v4";
    std::string e6 = "((v0==2 || (v1 > 10  && v2 > 3)) && v3 == -15.000000001 && v4) && (v5 == !v4)";
    std::string e7 = "true";
    m["v0"] = "1";
    m["v1"] = "15.55";
    m["v2"] = "-10";
    m["v3"] = "-15.000000001";
    m["v4"] = "true";
    m["v5"] = "false";
    eval.compile(e3);
    eval(m);
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