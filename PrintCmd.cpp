//
// Created by netanel on 31/12/2019.
//

#include "PrintCmd.h"
#include "UpdateVar.h"
#include "VarObj.h"
/**
* constructor
*/
PrintCmd::PrintCmd() {}
/**
* this method checks if a specific name if in the toSim map or fromSim map.
*@param currentPlace is the index of the current command in the file.
* @return true if the word is in the map thd false otherwise.
*/
bool PrintCmd::isInMap(int currentPlace) {

    //check in fromSim map
    for (pair<string, VarObj *> it:fromSim_map) {
        string x = it.first;
        string y = arrayofString[currentPlace + 1];
        if (it.first == arrayofString[currentPlace + 1]) {
            cout << it.second->getValue() << endl;
            return true;
        }
    }

    //check in toSim map
    for (pair<string, VarObj *> it:toSim_map) {
        string x = it.first;
        string y = arrayofString[currentPlace + 1];
        if (it.first == arrayofString[currentPlace + 1]) {
            cout << it.second->getValue() << endl;
            return true;
        }
    }
    return false;
}

/**
* this method executes the Print command
*@param currentPlace is the index of the current command in the file.
* @return the number of steps to the index of the next command
*/
int PrintCmd::execute(int currentPlace) {
    string PRINT = "";
    string exp = arrayofString[currentPlace + 1];
    int a = exp.find('+');
    int c = exp.find('*');
    int d = exp.find('/');
    if (a > 0 || c > 0 || d > 0) {

        Expression *e4 = interpreter->interpret(exp);
        PRINT = to_string(e4->calculate());
    } else {
        PRINT = arrayofString[currentPlace + 1];
    }
    if (isInMap(currentPlace) == false) {
        std::cout << PRINT << std::endl;
    }


    if (arrayofString[currentPlace + 2] == "var") {
        return 3;
    }
    return 2;
}