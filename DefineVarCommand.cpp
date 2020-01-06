//
// Created by shiran on 12/18/19.
//

#include "DefineVarCommand.h"
#include "VarObj.h"
#include <vector>
#include <string>

using namespace std;
extern vector<string> arrayofString;
extern map<string, VarObj *> toSim_map;
extern map<string, VarObj *> fromSim_map;

/**
* constructor
 */
DefineVarCommand::DefineVarCommand() {}

/**
* this method inserts the var to the maps. 
*@param currentPlace is the index of the current command in the file.
* @return the number of steps to the index of the next command
*/
int DefineVarCommand::execute(int currentPlace) {
    
    //insert to toSim_map
    if (arrayofString[currentPlace + 1] == "->") {
        string variable = arrayofString[currentPlace];
        string sim = arrayofString[currentPlace + 3];
        toSim_map.insert(make_pair(variable, new VarObj(0, sim)));
    }

    //insert to fromSim map
    if (arrayofString[currentPlace + 1] == "<-") {
        string variable = arrayofString[currentPlace];
        string sim = arrayofString[currentPlace + 3];
        fromSim_map.insert(make_pair(variable, new VarObj(0, sim)));
    }

    //insert to toSim_map. handles the h0= variable
    if (arrayofString[currentPlace + 1] == "=") {
        for (pair<string, VarObj *> it:toSim_map) {
            string x = it.first;
            string y = arrayofString[currentPlace + 2];
            if (it.first == arrayofString[currentPlace + 2]) {
                string variable = arrayofString[currentPlace];
                toSim_map.insert(make_pair(variable, it.second));

            }
        }
        for (pair<string, VarObj *> it:fromSim_map) {
            string x = it.first;
            string y = arrayofString[currentPlace + 2];
            if (it.first == arrayofString[currentPlace + 2]) {
                string variable = arrayofString[currentPlace];
                toSim_map.insert(make_pair(variable, it.second));
            }

        }
    }


    int stepCounter;
    if (arrayofString[currentPlace + 4] == "var") {
        stepCounter = 5;
    } else if (arrayofString[currentPlace + 1] == "=") {
        stepCounter = 3;
    } else {
        stepCounter = 4;
    }
    return stepCounter;
}