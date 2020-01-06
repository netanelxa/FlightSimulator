//
// Created by shiran on 12/20/19.
//

#ifndef NEWEX3_CONNECTCOMMAND_H
#define NEWEX3_CONNECTCOMMAND_H

#include "Command.h"
#include "UpdateVar.h"
#include "LoopCommand.h"
#include <vector>
#include <mutex>
#include <string>

using namespace std;
/**
* header of ConnectCommand
*/
class ConnectCommand : public Command {
    Interpreter *interpreter;
public:
    //   ConnectCommand(vector<std::string> vector, double currentPlace);
    ConnectCommand();

    //virtual double execute(vector<string> arrayofString, double currentPlace);
    virtual int execute(int currentPlace);

    void buffer(int client_socket);

    virtual ~ConnectCommand() {};

};


#endif //NEWEX3_CONNECTCOMMAND_H
