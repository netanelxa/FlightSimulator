

#include <sstream>
#include <deque>
#include <stack>
#include <iostream>
#include "Expression.h"
#include "Interpreter.h"
#include "VarObj.h"
#include "UpdateVar.h"
#include "UMinus.h"
#include "UPlus.h"
#include "Mul.h"
#include "Div.h"
#include "Plus.h"
#include "Minus.h"
#include "Value.h"

/**
* constructor
*/
Shunting_yard::Shunting_yard() {

}

//define operator
bool Shunting_yard::isoperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '&' || c == '#';
}

/**
* this method checks if there is demical fruction in the string.
 * @return new string
*/
string Shunting_yard::checkDigit(string fix) {
    deque<string> var;
    int flag = 0;
    string str;
    istringstream readSentence(fix);
    char dummy;
    string a;
    //check not set variable
    char token = readSentence.peek();
    if (token == -1)
        throw "bed set variable";
    while ((int) readSentence.tellg() != EOF) {
        token = readSentence.peek();
        if (token == -1)
            break;
        if (!isoperator(token)) {
            if (token == ')') {
                break;
            }
            //it can be . or digit
            if (token == '.' || isdigit(token)) {
                if (token == '.') {
                    flag++;
                }
                if (flag > 2)
                    throw "bad input";
                a += token;
                var.push_back(a);
                readSentence >> dummy;
            } else
                //bad digit
                return a;
        } else
            break;
    }
    return a;
}

/**
* this method checks if a char is a letter
 * @param fix is the string that might have letters
* @return new string
*/
string Shunting_yard::checkIsalpha(string fix) {
    deque<string> var;
    string str;
    istringstream readSentence(fix);
    char dummy;
    string a;
    while ((int) readSentence.tellg() != EOF) {
        char token = readSentence.peek();
        //end of string
        if (token == -1)
            break;
        if (!isoperator(token)) {
            if (token == ')') {
                break;
            }
            if (token == '_' || isdigit(token) || isalpha(token)) {
                a += token;
                var.push_back(a);
                readSentence >> dummy;
            } else {
                throw "erorr alpha";
            }
        } else
            break;
    }
    return a;
}

/**
* this method checks the second operator
 * @param infix is the infix string
 * @return the counter to the operator
*/
int Shunting_yard::checkOp2(string infix) {
    istringstream readSentence(infix);
    int index = 0;
    int countOperator = 0;
    char dummy;
    int flag = 0;
    while ((int) readSentence.tellg() != EOF) {
        //check only two char if there are  two opertor- error
        char token = readSentence.peek();
        if (index < 2) {
            if (token == '/') {
                index++;
                flag = 1;
                readSentence >> dummy;
            } else if (isoperator(token)) {
                countOperator++;
                if (flag == 1 && (token == '-' || token == '+')) {
                    countOperator--;
                }
            }
            index++;
            readSentence >> dummy;
        } else
            break;
    }
    return countOperator;
}

/**
* this methos marks the unary operators
 * @param str is the string of the expression. # is for negative and & for positive.
 * @return string with marks.
*/
string Shunting_yard::negativeMarker(string str) {
    for (unsigned int i = 0; i < str.length(); ++i) {
        if (i == 0) {
            if (str[i] == '-' && str[i + 1] == '(') {
                str[i] = '#';
            }
            if (str[i] == '+' && str[i + 1] == '(') {
                str[i] = '&';
            }
        }
        if (str[i] == '(' && str[i + 1] == '-' && isdigit(str[i + 2])) {
            str[i + 1] = '#';
        }
        if (!(isdigit(str[i])) && str[i + 1] == '-' && str[i + 2] == '(') {
            str[i + 1] = '#';
        }
    }
    return str;
}

/**
* this method converts the strig for the interpreter
 * @param infix is the string of expression.
*/
vector<string> Shunting_yard::convert(string infix) {
    stack<char> operators;

    string sh = negativeMarker(infix);
    istringstream readSentence(sh);
    char tmp;
    vector<string> strings;
    while ((int) readSentence.tellg() != EOF) {
        char token = readSentence.peek();
//      if (isalpha(token) || isdigit(token))
        if (isalpha(token) || token == '_') {
//            tokenBool = false;
            string getVariable = checkIsalpha(sh);
            strings.push_back(getVariable);
            sh = sh.substr(getVariable.length());
            for (unsigned i = 0; i < getVariable.length(); i++) {
                readSentence >> tmp;
            }
        }
            //if the char is digit we will check it
        else if (isdigit(token)) {
//            tokenBool = false;
            string getVariable = checkDigit(sh);
            strings.push_back(getVariable);
            sh = sh.substr(getVariable.length());
            for (unsigned i = 0; i < getVariable.length(); i++) {
                readSentence >> tmp;
            }
        }
            //if the char is operator check
        else if (isoperator(token) || token == '#' || token == '&') {
            int b = checkOp2(sh);
            if (b == 2) {
                throw "two operator next each other";
                break;
            }
            //check if unary operator "-" indicate #
            if (token == '#') {
                //check if the first char in the string is -
//                tokenBool = false;
                readSentence >> tmp;
                operators.push('#');
                sh = sh.substr(1);
                continue;
            }

            //check if unary operator "+" indicate &
            if (token == '&') {
                //check if the first charin the string is +
                readSentence >> tmp;
                operators.push('&');
                sh = sh.substr(1);
                continue;
            }


            char o1 = token;
            string a;
            if (!operators.empty()) {
                char top = operators.top();
                while (isoperator(top)) {
                    //check precedence
                    if (op.find(o1)->second <= (op.find(top)->second)) {
                        // convert char to string and push it to the list<string>
                        a += top;
                        strings.push_back(a);
                        operators.pop();
                    } else break;
                    if (operators.empty())
                        break;
                    else top = operators.top();
                }
            }
//            tokenBool = true;
            operators.push(o1);
            readSentence >> tmp;
            sh = sh.substr(1);
        } else if (token == '(') {
            operators.push(token);
            readSentence >> tmp;
            sh = sh.substr(1);
        } else if (token == ')') {
            while (operators.top() != '(' && !operators.empty()) {
                string a;
                a += operators.top();
                strings.push_back(a);
                operators.pop();
            }
            if (operators.empty()) {
                throw ("Mismatched parenthesis");
            }
            operators.pop();
            readSentence >> tmp;
            sh = sh.substr(1);
        }
            //recognize space and moving on
        else {
            readSentence.get(tmp);
        }

    }
    if (!operators.empty()) {
        if (operators.top() == '(') {
            throw ("Mismatched parenthesis");
        }
        int size = operators.size();
        for (int i = 0; i < size; i++) {
            string a;
            a += operators.top();
            strings.push_back(a);
            operators.pop();
        }
    }
    return strings;

}

/**
* constructor
*/
Interpreter::Interpreter() {

}

/**
* this method checks if a string is an operator
* @param c is the operator
*/
bool Interpreter::isOperator(string c) {
    return c == "+" || c == "-" || c == "*" || c == "/" || c == "^" || c == "&" || c == "#";
}

/**
* this method deletes spaces
 * @param s is a string.
 * @return string without spaces
*/
string Interpreter::DelSpace(string s) {
    for (int i = 0; i < s.length(); i++) {
        if (s[i] == ' ')
            s.erase(i, 1);
    }
    return s;
}

/**
* this method replace variables with the right value.
 * @param myVar is the variable
 * @return value if the variable
*/
string Interpreter::replacement(string myVar) {
    for (pair<string, VarObj *> it:fromSim_map) {
        string x = it.first;
        if (it.first == myVar) {
            return to_string(it.second->getValue());
        }
    }
    for (pair<string, VarObj *> it:toSim_map) {
        string x = it.first;
        if (it.first == myVar) {
            return to_string(it.second->getValue());
        }
    }
    return myVar;
}

/**
* this method uses the replacement method and returns the string with it's values.
 * @return string without variables
*/
string Interpreter::setVariables(string varStr) {
    char op1 = '+';
    char op2 = '-';
    char op3 = '*';
    char op4 = '/';
    string numberstring;
    int j = 0;
    int k = 0;
    for (int i = 0; i < varStr.length(); i++) {
        j++;
        if (varStr[i] == op1 || varStr[i] == op2 || varStr[i] == op3 || varStr[i] == op4) {
            string newStr = varStr.substr(k, j - 1);
            k = j;
            j = 0;
            numberstring += replacement(DelSpace(newStr));
            numberstring += varStr[i];
        }
        if (i == varStr.length() - 1) {
            char op = numberstring[numberstring.length() - 1];
            k = varStr.rfind(op) + 1;
            string newStr = varStr.substr(k, j);
            numberstring += replacement(DelSpace(newStr));
        }
    }
    for (int j = 0; j < numberstring.length(); j++) {
        if (numberstring[j] == '-' && numberstring[j + 1] == '-') {
            numberstring[j] = '+';
            numberstring.erase(j + 1, 1);
        }
    }
    return numberstring;
}

/**
* this is the interpreter
 * @param str is the expression
 * @return calculated expression
*/
Expression *Interpreter::interpret(string str) {
    int flag = 0;
    int q = 0;
    str = DelSpace(str);
    while (q < str.length()) {
        if (isdigit(str[q])) {
            flag = 0;
        } else if (str[q] == '+' || str[q] == '-' || str[q] == '*' || str[q] == '/') {
            flag = 0;
        }
        else if(isalpha(str[q])){
            flag=1;
            break;
        }
        q++;
    }
    if (flag == 1)
        str = setVariables(str);
    map<string, double>::iterator it;
    vector<string> postfix;
    Shunting_yard *n = new Shunting_yard();
    postfix = n->convert(str);
    stack<Expression *> nums;
//    int index=0;
    char tmp;
    for (string s:postfix) {
        istringstream readSentance(s);
        char token = readSentance.peek();
        if (isalpha(token) || token == '_');

        else if (isdigit(token)) {
            try {
                nums.push(new Value(stod(s)));
                readSentance >> tmp;
            }
            catch (exception &e) {
                throw "bad input";
            }
        } else {
            Expression *num2 = nums.top();
            nums.pop();
            //if # recognize minus unarry
            if (s == "#") {
                readSentance >> tmp;
                nums.push(new UMinus(num2));
                continue;
            }
                //if & recognize plus unarry
            else if (s == "&") {
                nums.push(new UPlus(num2));
                readSentance >> tmp;
                nums.push(new UPlus(num2));
                continue;
            }
            if (isOperator(s)) {
                Expression *num1 = new Value(0);
                Expression *res;
                if (!nums.empty()) {
                    num1 = nums.top();
                    nums.pop();
                }
                if (s == "+" || s == "-") {
                    if (token == '-')
                        num2 = new Mul(num2, new UMinus(new Value(1)));
                    res = new Plus(num1, num2);
                } else if (s == "*" || s == "/") {
                    if (token == '/')
                        num2 = new Div(new Value(1), num2);
                    res = new Mul(num1, num2);
                }
                nums.push(res);
                readSentance >> tmp;
            }
        }

    }
    return nums.top();
}

