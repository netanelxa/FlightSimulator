//
// Created by shiran on 7.11.2019.
//

#ifndef UNTITLED_UMINUS_H
#define UNTITLED_UMINUS_H


#include "UnaryOperator.h"
/**
* header of UMinus
*/
class UMinus: public UnaryOperator {
public:
    UMinus(Expression *exp1);

    virtual double calculate();
};


#endif //UNTITLED_UMINUS_H
