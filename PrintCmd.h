//
// Created by netanel on 31/12/2019.
//

#ifndef NEWEX3_PRINTCMD_H
#define NEWEX3_PRINTCMD_H

#include "string"
#include <iostream>
#include "Command.h"
#include "Interpreter.h"
/**
* header of Print
*/
class PrintCmd : public Command {
    Interpreter *interpreter;

public:
    PrintCmd();

    int execute(int currentPlace);
    bool isInMap(int currentPlace);
    virtual ~PrintCmd(){};
};


#endif //NEWEX3_PRINTCMD_H
