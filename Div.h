//
// Created by shiran on 7.11.2019.
//

#ifndef UNTITLED_DIV_H
#define UNTITLED_DIV_H


#include "BinaryOperator.h"
/**
* header of Div
*/
class Div: public BinaryOperator {
    public:
            Div(Expression *left1, Expression *right1);
    virtual double calculate();

};


#endif //UNTITLED_DIV_H
