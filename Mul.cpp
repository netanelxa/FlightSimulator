//
// Created by shiran on 7.11.2019.
//


#include "BinaryOperator.h"
#include "Mul.h"
/**
* constructor
 * @param left1 is the number before the multiple operator
 * @param right1 is the number after the multiple operator
*/
Mul::Mul(Expression *left1, Expression *right1) : BinaryOperator(left1,right1){}

/**
* this method multiple two numbers.
 * @return the value of the calculation.
*/
double Mul::calculate() {
        return left->calculate()*right->calculate();
    }
