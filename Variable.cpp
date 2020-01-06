//
// Created by shiran on 6.11.2019.
//
/**
 * this class represents Variable object.
 */
#include "Expression.h"
#include "Variable.h"

using namespace std;

/**
 * constructor
 * @param name1 is the name of the variable.
 * @param value1 is the value of the variable.
 */
Variable::Variable(string name1, double value1){
    this->name=name1;
    this->value=value1;
}

/**
* handles ++x
* @param name1 is the name of the variable.
* @return ++x
*/
Variable& Variable:: operator++(){
    ++value;
    return *this;
}

/**
* handles --x
* @param name1 is the name of the variable.
* @return --x;
*/
Variable& Variable::operator--(){
    --value;
    return *this;
}

/**
* handles x+= operator
* @param num is the number that is accelerated.
* @return accelerated value of the num.
*/
Variable& Variable::operator+=(double num){
    value+=num;
    return *this;
}

/**
* handles x-= operator
* @param num is the number that is decelerated.
* @return decelerated value of the num.
*/
Variable& Variable::operator-=(double num){
    value-=num;
    return *this;
}

/**
* handles x++ operator
* @param num is the number that is accelerated.
* @return accelerated value of the num.
*/
Variable& Variable::operator++(int){
    value++;
    return *this;
}
/**
* handles x-- operator
* @param num is the number that is decelerated.
* @return decelerated value of the num.
*/
Variable& Variable::operator--(int){
    value--;
    return *this;
}

/**
* calculate function
* @return value of calculated expression.
*/
double Variable::calculate(){
    return value;
}