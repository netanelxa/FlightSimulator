//
// Created by shiran on 12/31/19.
//

#ifndef TEST_CONDITIONPARSER_H
#define TEST_CONDITIONPARSER_H


#include "Command.h"

class ConditionParser : public Command {
public:
    ConditionParser(){};

    virtual int execute(int currentPlace) = 0;

    virtual ~ConditionParser() {}

};


#endif //TEST_CONDITIONPARSER_H
