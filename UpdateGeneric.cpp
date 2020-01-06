//
// Created by netanel on 05/01/2020.
//

#include <vector>
#include "UpdateGeneric.h"
#include "VarObj.h"
#include "UpdateVar.h"

/**
* constructor
*/
UpdateGeneric::UpdateGeneric(){}


/**
* this method updates genericMap.
 * @param genericMap is map that contains values from simulator to client.
*/
void UpdateGeneric::updateFromSim(vector<pair<string, double>> genericMap) {
    for (int i=0; i<genericMap.size();i++) {
        for (pair<string, VarObj *> it:fromSim_map) {
            string name=it.first;
            int value= it.second->getValue();
            int rpmvalue=genericMap[35].second;
            string s= it.second->getSim();
            string s2 = genericMap[i].first;
            if (it.second->getSim() == genericMap[i].first) {
                it.second->setValue(genericMap[i].second);
            }
        }
    }
}