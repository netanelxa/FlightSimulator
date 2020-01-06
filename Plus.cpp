//
// Created by shiran on 8.11.2019.
//


#include "BinaryOperator.h"
#include "Plus.h"
/**
* header of Plus
 * @param left1 is the number before the plus sign.
 * @param left2 is the number after the plus sign.
*/
Plus::Plus(Expression *left1, Expression *right1) : BinaryOperator(left1,right1){}

/**
* this method calculates the expression
 * @return calculated expression
*/
    double Plus:: calculate() {
        return left->calculate()+right->calculate();
    }
