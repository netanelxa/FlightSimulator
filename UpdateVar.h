//
// Created by netanel on 30/12/2019.
//

#ifndef NEWEX3_UPDATEVAR_H
#define NEWEX3_UPDATEVAR_H

#include <queue>
#include "string"
#include "map"
#include "VarObj.h"
#include "ConnectCommand.h"
#include "Command.h"


using namespace std;
extern vector<string> arrayofString;
extern map<string, VarObj *> toSim_map;
extern map<string, VarObj *> fromSim_map;
extern queue<string> updateQueue;
/**
* header of UpdateVar
*/
class UpdateVar {

    int sock2;
    int currentPlace;

public:
    UpdateVar(int currentIndex);


    void setSocketfd(int socketfd);

    int updateMap();

};


#endif //NEWEX3_UPDATEVAR_H
