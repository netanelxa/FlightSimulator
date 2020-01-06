//
// Created by netanel on 17/12/2019.
//

#include <fstream>
#include <iostream>
#include <string>
#include "Command.h"
#include <vector>
#include <map>
#include "UpdateVar.h"

using namespace std;
#ifndef EX3_LEXER_H
#define EX3_LEXER_H

/**
* header of Lexer
*/
class Lexer {

    string filename;
    ifstream filereader;
    map<string, Command *> pairedCommands;
public:
    Lexer(string FlyFile) {
        this->filename = FlyFile;
    };

    vector<string> readFile();
    void createPairedVector();
    void parser();
/*
    map<string,Command*> createPairedVector(vector<string> arrayofString);

    void parser(vector<string> arrayofString, map<string, Command *> pairedCommands);
    */
    virtual ~Lexer(){};
};


#endif //EX3_LEXER_H