//
// Created by netanel on 17/12/2019.
//

#include <fstream>
#include <iostream>
using namespace std;
#ifndef EX3_LEXER_H
#define EX3_LEXER_H


class Lexer {
    string filename;
    fstream fileread;
public:
    Lexer(string FlyFile){
        this->filename=FlyFile;
    };
    void readFile();

};


#endif //EX3_LEXER_H
