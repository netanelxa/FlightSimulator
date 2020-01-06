//
// Created by shiran on 7.11.2019.
//

#ifndef UNTITLED_UNARYOPERATOR_H
#define UNTITLED_UNARYOPERATOR_H


#include "Expression.h"
/**
* header of UnaryOperator
*/
class UnaryOperator: public Expression {
protected:
    Expression *exp;

public:
    UnaryOperator(Expression *exp1);

    virtual double calculate()=0;
    virtual ~UnaryOperator();
};


#endif //UNTITLED_UNARYOPERATOR_H
