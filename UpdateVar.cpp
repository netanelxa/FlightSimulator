//
// Created by netanel on 30/12/2019.
//

#include "UpdateVar.h"
#include "Command.h"
#include "Expression.h"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include "ConnectCommand.h"
#include "stack"

extern stack<int> sockets;
extern vector<pair<string, double>> genericMap;

/**
* constructor
 * @param currentIndex is the index of the current string that the
 * program reads from the file.
*/
UpdateVar::UpdateVar(int currentIndex) {
    this->currentPlace = currentIndex;
}


/**
* this method updates toSim map and fromSim map and sends it to the server.
 * this handles the 'var x= number' lines.
* @return index of the next command
*/
int UpdateVar::updateMap() {
    //update toSim map
    this->sock2 = sockets.top();
    string b = arrayofString[currentPlace];
    int a = toSim_map.size();
    for (pair<string, VarObj *> it:toSim_map) {
        if (it.first == arrayofString[currentPlace]) {
            it.second->setValue(stod(arrayofString[currentPlace + 2]));
            string n = "set " + it.second->getSim() + " " + to_string(it.second->getValue()) + "\r\n";
            const char *nsend = n.c_str();
            string sim = it.second->getSim();
            string values = to_string(it.second->getValue());
            send(this->sock2, nsend, strlen(nsend), 0);
            updateQueue.push(n);
        }
    }

    //update fromSim map
    for (pair<string, VarObj *> it:fromSim_map) {
        if (it.first == arrayofString[currentPlace]) {
            it.second->setValue(stod(arrayofString[currentPlace + 2]));
            string n = "set " + it.second->getSim() + " " + to_string(it.second->getValue()) + "\r\n";
            const char *nsend = n.c_str();
            string sim = it.second->getSim();
            string values = to_string(it.second->getValue());
            send(this->sock2, nsend, strlen(nsend), 0);
            updateQueue.push(n);
        }
    }
    if (arrayofString[currentPlace + 3] == "var") {
        return 4;
    }
    return 3;
}