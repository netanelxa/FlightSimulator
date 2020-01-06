//
// Created by shiran on 7.11.2019.
//


#include "Expression.h"
#include "UnaryOperator.h"

/**
* constructor
* @param exp1 is the expression that needs to be calculated
*/
UnaryOperator:: UnaryOperator(Expression *exp1){
    this->exp=exp1;
}

/**
* destructor
*/
UnaryOperator::~UnaryOperator() {
    delete exp;
}

