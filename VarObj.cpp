//
// Created by netanel on 26/12/2019.
//

/**
 * This class represents an object that contains value of a command and sim address.
 */

#include "VarObj.h"

/**
 * constructor
 * @param val is the value.
 * @param sim is the sim address.
 */
VarObj::VarObj(double val,string sim) {
    this->_value=val;
    this->_sim=sim;
}
/**
 * get sim function
 * @return sim address
 */
string VarObj::getSim() {
    return this->_sim;
}
/**
 * get value function
 * @return value of object
 */
double VarObj::getValue() {
    return this->_value;
}
/**
* set sim function
*/
void VarObj::setSim(string newsim) {
    this->_sim=newsim;
}
/**
 * set value function
 */
void VarObj::setValue(double newvalue) {
    this->_value=newvalue;
}