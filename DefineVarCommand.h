//
// Created by shiran on 12/18/19.
//

#ifndef UNTITLED_DEFINDEVARCOMMAND_H
#define UNTITLED_DEFINDEVARCOMMAND_H


#include "Command.h"
#include <vector>
#include <string>
#include "Lexer.h"

using namespace std;
/**
* header of DefineVarCommand
*/
class DefineVarCommand : public Command {
public:
    DefineVarCommand();

    virtual int execute(int currentPlace);

};


#endif //UNTITLED_DEFINDEVARCOMMAND_H
