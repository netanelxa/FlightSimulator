//
// Created by netanel on 31/12/2019.
//

#include <chrono>
#include <thread>
#include <iostream>
#include "SleepCmd.h"
#include "UpdateVar.h"

/**
* constructor
*/
SleepCmd::SleepCmd() {
}
/**
* this method executes the Sleep command
*@param currentPlace is the index of the current command in the file.
* @return the number of steps to the index of the next command
*/
int SleepCmd::execute(int currentPlace) {
    cout << "sleep " << arrayofString[currentPlace + 1] << endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(stoi(arrayofString[currentPlace + 1])));

    if (arrayofString[currentPlace + 2] == "var") {
        return 3;
    }
    return 2;
}