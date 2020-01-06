//
// Created by shiran on 6.11.2019.
//

#ifndef UNTITLED_VALUE_H
#define UNTITLED_VALUE_H


#include <iostream>
#include "Expression.h"

/**
* header of value
*/
class Value : public Expression{
private:
    double value;
public:
    Value(const double value1);
    virtual double calculate();
};


#endif //UNTITLED_VALUE_H
