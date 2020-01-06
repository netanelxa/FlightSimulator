//
// Created by shiran on 7.11.2019.
//


#include "BinaryOperator.h"
#include "Minus.h"

/**
* constructor
 * @param left1 is the number before the Minus
 * @param right1 is the number after the Minus
*/
Minus::Minus(Expression *left1, Expression *right1) : BinaryOperator(left1,right1){}

/**
* this method calculates the minus operator.
 * @return the value of the calculation.
*/
double Minus::calculate() {
        return left->calculate()-right->calculate();
    }

