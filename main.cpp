#include <iostream>
#include "Lexer.h"

int main() {
    Lexer* a= new Lexer("fly.txt");
    a->readFile();
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
