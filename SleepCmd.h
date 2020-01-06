//
// Created by netanel on 31/12/2019.
//

#ifndef NEWEX3_SLEEPCMD_H
#define NEWEX3_SLEEPCMD_H

#include "Command.h"

using namespace std;
/**
* header of Sleep
*/
class SleepCmd :public Command {
public:
    SleepCmd();

    int execute(int currentPlace);

    virtual ~SleepCmd() {};
};


#endif //NEWEX3_SLEEPCMD_H
