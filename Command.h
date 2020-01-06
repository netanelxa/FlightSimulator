//
// Created by shiran on 12/18/19.
//

#ifndef UNTITLED_COMMAND_H
#define UNTITLED_COMMAND_H

#include <string>
#include <vector>
#include <map>
#include "VarObj.h"

class Command {

public:


    virtual int execute(int currentPlace) = 0;

    virtual ~Command() {}
};

#endif //UNTITLED_COMMAND_H
