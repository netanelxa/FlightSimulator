//
// Created by shiran on 12/31/19.
//

#ifndef TEST_LOOPCOMMAND_H
#define TEST_LOOPCOMMAND_H


#include "ConditionParser.h"
#include "Interpreter.h"
#include "ConnectCommand.h"

/**
* header of IfCommand
*/
class IfCommand : public ConditionParser {
    bool condition;
    int val1;
    int val2;
    string oper;
    int socket;
public:
    int tempIndex;

    IfCommand();

    void setSocketfd1(int socketfd);

    void updateCondition(int currentPlace);

    void UpdateVarible(int currentPlace);

    void UpdateVarible(int currentPlace, Expression *e);

    virtual int execute(int currentPlace);

    virtual ~IfCommand() {}

    bool isCondition(int val1, int val2, string oper);

    bool isInMap(int currentPlace);

};


#endif //TEST_LOOPCOMMAND_H