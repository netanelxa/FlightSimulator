//
// Created by shiran on 8.11.2019.
//

#ifndef UNTITLED_PLUS_H
#define UNTITLED_PLUS_H


#include "Expression.h"
#include "BinaryOperator.h"
/**
* header of Plus
*/
class Plus: public BinaryOperator {

public:
    Plus(Expression *left1, Expression *right1);

    virtual double calculate();


};

#endif //UNTITLED_PLUS_H
