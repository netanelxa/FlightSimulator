//
// Created by netanel on 26/12/2019.
//

#ifndef NEWEX3_VAROBJ_H
#define NEWEX3_VAROBJ_H

#include <string>

using namespace std;
/**
* header of varObj.
*/
class VarObj {
    double _value;
    string _sim;
public:
    VarObj(double val,string sim);

    void setValue(double newvalue);

    void setSim(string newstring);

    double getValue();

    string getSim();
};


#endif //NEWEX3_VAROBJ_H
