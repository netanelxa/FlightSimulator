//
// Created by shiran on 7.11.2019.
//

#ifndef UNTITLED_MUL_H
#define UNTITLED_MUL_H
#include "BinaryOperator.h"
/**
* header of Mul
*/
class Mul: public  BinaryOperator{
public:
    Mul(Expression *left1, Expression *right1);
    virtual double calculate();

};


#endif //UNTITLED_MUL_H
