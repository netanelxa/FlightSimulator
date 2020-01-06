//
// Created by gal on 18/11/2019.
//

#ifndef EX1_EX1_H
#define EX1_EX1_H

#include <map>
#include <vector>
#include "Expression.h"


using namespace std;
/**
* header of Interpret
*/

class Shunting_yard {
private:
    map<char, int> op = {
            {'(', 1},
            {'+', 2},
            {'-', 2},
            {'*', 3},
            {'/', 3},
            {'#', 4},
            {'&', 4}
    };

    bool isoperator(char);

public:
    Shunting_yard(string);

    Shunting_yard();

    vector<string> convert(string infix);

    string checkIsalpha(string fix);

    string checkDigit(string fix);

    int checkOp2(string infix);

    string negativeMarker(string str);

};



///Interpreter//////

class Interpreter {
    bool isOperator(string);

public:

    Interpreter();

    Expression *interpret(string str);

    string setVariables(string varStr);

    string DelSpace(string s);

    string replacement(string myVar);


};


#endif //EX1_EX1_H
