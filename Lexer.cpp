//
// Created by netanel on 17/12/2019.
//

#include "Lexer.h"


void Lexer::readFile() {
    string line;
    fileread.open(filename, ios::in | ios::binary);
    if (!fileread)
        std::cout << "Opening w file error " << filename<< endl;
    while (std::getline(fileread, line)){

        fileread.close();
    }
}