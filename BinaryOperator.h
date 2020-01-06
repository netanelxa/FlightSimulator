//
// Created by shiran on 5.11.2019.
//

#ifndef UNTITLED_BINARYOPERATOR_H
#define UNTITLED_BINARYOPERATOR_H


#include "Expression.h"
#include <string.h>
#include <iostream>
using namespace std;
/**
* header of BinaryOperator
*/
class BinaryOperator: public Expression {
protected:
    Expression *left;
    Expression *right;
public: BinaryOperator(Expression *left, Expression *right);
    virtual double calculate()=0;
    virtual ~BinaryOperator();

};


#endif //UNTITLED_BINARYOPERATOR_H
