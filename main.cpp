#include <iostream>
#include <vector>
#include "Command.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "Lexer.h"

int main() {
 /*   Command *c = new OpenServerCommand();
    c->execute(1);
    Command *b = new ConnectCommand();
    b->execute(3);*/
   Lexer *d = new Lexer("fly.txt");
    d->readFile();
    d->createPairedVector();
    d->parser();
    Command *dd = new DefineVarCommand();
    dd->execute(5);
}