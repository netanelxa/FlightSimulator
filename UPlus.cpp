//
// Created by shiran on 8.11.2019.
//


#include "UnaryOperator.h"
#include "UPlus.h"

/**
* constructor
*/
UPlus::UPlus(Expression *exp1) : UnaryOperator(exp1){}


/**
* calculate function
* @return value of calculated expression.
*/
double UPlus :: calculate() {
    return exp->calculate();
}
