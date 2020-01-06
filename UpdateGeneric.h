//
// Created by netanel on 05/01/2020.
//

#ifndef NEWEX3_UPDATEGENERIC_H
#define NEWEX3_UPDATEGENERIC_H

#include "string"

using namespace std;
/**
* header of UpdateGeneric
*/
class UpdateGeneric {
public:
    UpdateGeneric();

    void updateFromSim(vector<pair<string, double>> genericMap);

};


#endif //NEWEX3_UPDATEGENERIC_H
