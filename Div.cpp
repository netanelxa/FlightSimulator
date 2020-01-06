//
// Created by shiran on 7.11.2019.
//


#include "Expression.h"
#include "BinaryOperator.h"
#include "Div.h"
/**
* header of Plus
 * @param left1 is the number before the Div sign.
 * @param left2 is the number after the Div sign.
*/
Div::Div(Expression *left1, Expression *right1) : BinaryOperator(left1,right1){}

/**
* this method calculates the expression
 * @return calculated expression
*/
double Div::calculate() {
    if (right->calculate() == 0) {
        throw "division by zero";
    } else {
        return (left->calculate()) / (right->calculate());
    }
}

