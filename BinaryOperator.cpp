//
// Created by shiran on 5.11.2019.
//

#include "Expression.h"
#include "BinaryOperator.h"
using namespace std;
/**
* constructor
 * @param left1 is the number before operator
 * @param right1 is the number after the operator.
*/
BinaryOperator::BinaryOperator(Expression *left1, Expression *right1) {
    this->left = left1;
    this->right = right1;
}

/**
* destcructor
*/
BinaryOperator :: ~BinaryOperator(){
            delete(left);
            delete(right);
        }

