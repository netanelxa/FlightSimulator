//
// Created by shiran on 12/31/19.
//

#include "IfCommand.h"
#include "ConditionParser.h"
#include "UpdateVar.h"
#include "SleepCmd.h"
#include "PrintCmd.h"
#include "ConnectCommand.h"
#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include "stack"

using namespace std;
extern stack<int> sockets;
/**
* constructor
*/
IfCommand::IfCommand()  {
}

/**
* this method checks if the key is in one of the maps
 * @param currentPlace is the index of the current command
 * @return true if it is in one of the maps, fales othewise.
*/
bool IfCommand::isInMap(int currentPlace) {
    //check in the fromSim map
    for (pair<string, VarObj *> it:fromSim_map) {
        if (it.first == arrayofString[currentPlace]) {
            return true;
        }
    }

    //check in the toSim map
    for (pair<string, VarObj *> it:toSim_map) {
        if (it.first == arrayofString[currentPlace]) {
            return true;
        }
    }
    return false;
}

/**
* this method update condition after each iteration of while
 * @param currentPlace is the index of the current command
*/
void IfCommand::updateCondition(int currentPlace) {
    string myVar = arrayofString[currentPlace + 1];
    for (pair<string, VarObj *> it:fromSim_map) {
        if (it.first == myVar) {
            this->val1 = it.second->getValue();
        }
    }
}

/**
* this method checks if the condition is true
 * @param val1 is the value before operator
 * @param val2 is the value after operatoe
 * @param oper is operator of the condition
 * @return true if the condition is true, fales othewise.
*/
bool IfCommand::isCondition(int val1, int val2, string oper) {
    if (oper == "<" || oper == "< ") return val1 < val2;
    else if (oper == ">" || oper == "> ") return val1 > val2;
    else if (oper == "<=" || oper == "<= ") return val1 <= val2;
    else if (oper == ">=" || oper == ">= ") return val1 >= val2;
    else if (oper == "==" || oper == "== ") return val1 == val2;
    else if (oper == "!=" || oper == "!= ") return val1 != val2;
    else
        return true;
}

/**
* this method updates variable in the fromSim map and toSim map and send it to server.
 * @param currentPlace is the index of the current command
*/
void IfCommand::UpdateVarible(int currentPlace) {
    this->socket = sockets.top();
    //update toSim map
    for (pair<string, VarObj *> it:fromSim_map) {
        if (it.first == arrayofString[currentPlace]) {
            it.second->setValue(-1*stod(arrayofString[currentPlace + 2]));
            string n = "set " + it.second->getSim() + " " + to_string(it.second->getValue()) + "\r\n";
            const char *nsend = n.c_str();
            string sim = it.second->getSim();
            string values = to_string(it.second->getValue());
            send(this->socket, nsend, strlen(nsend), 0);
            updateQueue.push(n);
        }
    }
    //update fromSim map
    for (pair<string, VarObj *> it:toSim_map) {
        this->socket = sockets.top();

        if (it.first == arrayofString[currentPlace]) {
            it.second->setValue(-1*stod(arrayofString[currentPlace + 2]));
            string n = "set " + it.second->getSim() + " " + to_string(it.second->getValue()) + "\r\n";
            const char *nsend = n.c_str();
            string sim = it.second->getSim();
            string values = to_string(it.second->getValue());
            send(this->socket, nsend, strlen(nsend), 0);
            updateQueue.push(n);
        }
    }
}


/**
* this method updates variable in the fromSim map and toSim map and send it to server.
 * @param currentPlace is the index of the current command
 * @param e is the expression comes from interpreter
*/
void IfCommand::UpdateVarible(int currentPlace, Expression *e) {
    this->socket = sockets.top();
    for (pair<string, VarObj *> it:fromSim_map) {
        if (it.first == arrayofString[currentPlace]) {
            it.second->setValue(-1*stod(to_string(e->calculate())));
            string n = "set " + it.second->getSim() + " " + to_string(it.second->getValue()) + "\r\n";
            const char *nsend = n.c_str();
            string sim = it.second->getSim();
            string values = to_string(it.second->getValue());
            int a = send(this->socket, nsend, strlen(nsend), 0);
            updateQueue.push(n);
        }
    }

    for (pair<string, VarObj *> it:toSim_map) {
        this->socket = sockets.top();

        if (it.first == arrayofString[currentPlace]) {
            it.second->setValue(-1*stod(to_string(e->calculate())));
            string sim = it.second->getSim();
            string values = to_string(it.second->getValue());
            string n = "set " + it.second->getSim() + " " + to_string(it.second->getValue()) + "\r\n";
            const char *nsend = n.c_str();
            int b = send(this->socket, nsend, strlen(nsend), 0);

            updateQueue.push(n);
        }
    }
}

/**
* this method handles while loop in text.
 * @param currentPlace is the index of the current command
 * @return the number of steps to the index of the next command
*/
int IfCommand::execute(int currentPlace) {
    oper = arrayofString[currentPlace + 2];
    val2 = stod(arrayofString[currentPlace + 3]);
    updateCondition(currentPlace); // set condition
    this->condition = isCondition(val1, val2, oper); //check if condition is true
    currentPlace = currentPlace + 5; // start from the first command in the loop
    int flag = 1;

    if (condition == true) {
        flag = 0;
        this->tempIndex = currentPlace;
        while (arrayofString[this->tempIndex] != "}") {
            string s = arrayofString[currentPlace];
            if (arrayofString[this->tempIndex] == "Sleep") {
                SleepCmd *a = new SleepCmd();
                a->execute(this->tempIndex);
            }
            if (arrayofString[this->tempIndex] == "Print") {
                PrintCmd *a = new PrintCmd();
                a->execute(this->tempIndex);
            }

            //handle expression in the text.
            if (isInMap(this->tempIndex) && (arrayofString[this->tempIndex + 1] == "=")) {
                string exp = arrayofString[this->tempIndex + 2];
                if (exp.find('+') > 0 || exp.find('-') > 0 || exp.find('/') > 0 || exp.find('*') > 0) {
                    Interpreter *i1 = new Interpreter();
                    Expression *e4 = nullptr;
                    e4 = i1->interpret(exp);

                    //update variable in the maps
                    UpdateVarible(this->tempIndex, e4);
                } else {
                    UpdateVarible(this->tempIndex);
                }
            }
            this->tempIndex++;
        }
        updateCondition(currentPlace); // update condition before the next iteration
        this->condition = isCondition(val1, val2, oper); // check if condition is true
    }
    int a = this->tempIndex;
    int b = currentPlace;
    if (flag == 1) {
        while (arrayofString[b] != "}")
            b++;
        b++;
        cout<<b-currentPlace<<endl;
        return ((b-currentPlace)+5);
    }
    return ((this->tempIndex - currentPlace) + 6);
}