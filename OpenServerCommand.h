//
// Created by shiran on 12/20/19.
//

#ifndef NEWEX3_OPENSERVERCOMMAND_H
#define NEWEX3_OPENSERVERCOMMAND_H


#include "Command.h"
#include <vector>
#include <string>
#include <map>
#include <mutex>
#include "Lexer.h"
#include <sys/socket.h>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <thread>
#include <string>
#include "UpdateGeneric.h"




using namespace std;
/**
* header of OpenServerCommand
*/
class OpenServerCommand : public Command {
    mutex locker1;
    UpdateGeneric* upd;
    Interpreter *interpreter;
public:
    OpenServerCommand();


    void StartServer(int client_socket);

    virtual int execute(int currentPlace);

    virtual ~OpenServerCommand() {}


};


#endif //NEWEX3_OPENSERVERCOMMAND_H