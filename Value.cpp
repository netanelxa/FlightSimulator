//
// Created by shiran on 6.11.2019.
//

#include <iostream>
#include "Expression.h"
#include "Value.h"


/**
* constructor
* @param value1
*/
Value::Value(const double value1) {
    this->value = value1;
}

/**
* calculate function
* @return value of calculated expression.
*/
double Value::calculate() {
    return value;
}

