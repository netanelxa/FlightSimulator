//
// Created by shiran on 7.11.2019.
//

#ifndef UNTITLED_UPLUS_H
#define UNTITLED_UPLUS_H


#include "UnaryOperator.h"
/**
* header of UPlus
*/
class UPlus: public UnaryOperator {
public:
    UPlus(Expression *exp1);

    virtual double calculate();
};


#endif //UNTITLED_UPLUS_H
