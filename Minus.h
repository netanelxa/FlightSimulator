//
// Created by shiran on 7.11.2019.
//

#ifndef UNTITLED_MINUS_H
#define UNTITLED_MINUS_H
#include "BinaryOperator.h"
/**
* header of Minus
*/


class Minus: public BinaryOperator {

public:
    Minus(Expression *left1, Expression *right1);
    virtual double calculate();


};


#endif //UNTITLED_MINUS_H
