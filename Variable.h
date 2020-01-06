//
// Created by shiran on 6.11.2019.
//

#ifndef UNTITLED_VARIABLE_H
#define UNTITLED_VARIABLE_H

#include <string>

#include "Expression.h"
/**
* header of variable.
*/
class Variable: public Expression{
private:
    string name;
    double value;

public: Variable(string name1, double value1);
    Variable&  operator++();
    Variable&  operator--();
    Variable&  operator+=(double num);
    Variable&  operator-=(double num);
    Variable&  operator++(int demo);
    Variable&  operator--(int demo);




    virtual double calculate();

};


#endif //UNTITLED_VARIABLE_H
