//
// Created by shiran on 7.11.2019.
//


#include "UnaryOperator.h"
#include "UMinus.h"

/**
* constructor
* @param exp1 is the expression that needs to be calculated
*/
UMinus::UMinus(Expression *exp1) : UnaryOperator(exp1){}

/**
* this method calculates the expression as the negative value of the number.
* @return calculated expression
*/
double UMinus:: calculate() {
    return (-1)*exp->calculate();
}