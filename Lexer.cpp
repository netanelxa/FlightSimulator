
// Created by netanel on 17/12/2019.
//

#include "Lexer.h"
#include "OpenServerCommand.h"
#include "ConnectCommand.h"
#include "DefineVarCommand.h"
#include "SleepCmd.h"
#include "PrintCmd.h"
#include "LoopCommand.h"

map<string, Command *> commandsMap;
vector<pair<string, double>> genericMap;
vector<string> arrayofString;
map<string, VarObj *> toSim_map;
map<string, VarObj *> fromSim_map;
queue<string> updateQueue;

string Dissolver(string line) {
    if (line.find('(') != -1)
        line.erase(line.find('('), 1);
    if (line.find(',') != -1)
        line.erase(line.find(','), 1);
    if (line.find(')') != -1)
        line.erase(line.find(')'), 1);

    if (line.find(' ') == 0) {
        line.erase(line.find(' '), 1);
    }
    if (line.find(' ') == line.length())
        line.erase(line.find(' '), 1);
    if (line.find('\t') != -1)
        line.erase(line.find('\t'), 1);
    if (line.find('"') != -1)
        line.erase(line.find('"'), 1);
    if (line.rfind('"') != -1)
        line.erase(line.rfind('"'), 1);

    return line;
}


vector<string> Lexer::readFile() {
    string line;
    string substr;
    bool checkifEmpty;
    filereader.open(filename, ios::in | ios::binary);
    if (!filereader.is_open()) {
        std::cout << "Opening w file error " << filename << endl;
    }

    while (std::getline(filereader, line)) {
        int i = 0;
        while (i < line.length()) {
            if (line[i] == '(') {
                i = line.find('(');
                string substr = line.substr(0, i);
                checkifEmpty = Dissolver(substr).length();
                if (checkifEmpty)
                    arrayofString.push_back(Dissolver(substr));
                line = line.substr(i, line.length() - i);
                i = 0;
                while (line[i] != ')' && line.length()) {
                    i++;
                    char k = line[i];
                    if (line[i] == '"') {
                        i++;
                        i = line.rfind('"', i);
                        string substr = line.substr(0, i);
                        checkifEmpty = Dissolver(substr).length();
                        if (checkifEmpty)
                            arrayofString.push_back(Dissolver(substr));
                        i++;
                        line = line.substr(i, line.length() - i);
                        i = 0;
                    } else if (line[i] == ')') {
                        i = line.find(')');
                        string substr = line.substr(0, i);
                        checkifEmpty = Dissolver(substr).length();
                        if (checkifEmpty)
                            arrayofString.push_back(Dissolver(substr));
                        i++;
                        line = line.substr(i, line.length() - i);
                        i = 0;
                    } else if (line[i] == ',')
                        i++;
                }
            } else if (line[i] == ',')
                i++;
            else if (line[i] == '-' && line[i + 1] == '>') {
                string substr = line.substr(0, line.find(' '));
                arrayofString.push_back(Dissolver(substr));
                substr = line.substr(line.find(' '), line.find('-') - line.find(' '));
                arrayofString.push_back(Dissolver(substr));
                line = line.substr(line.find('-'), line.length() - i);
                i = line.find('-');
                substr = line.substr(0, i);
                checkifEmpty = Dissolver(substr).length();
                if (checkifEmpty)
                    arrayofString.push_back(Dissolver(substr));
                arrayofString.push_back("->");
                i += 2;
                line = line.substr(i, line.length() - i);
                substr = line.substr(0, line.find('('));
                arrayofString.push_back(Dissolver(substr));
                line = line.substr(line.find('('), line.length() - 1);
                line = " " + line;
                i = 0;
            } else if (line[i] == '<' && line[i + 1] == '-') {
                string substr = line.substr(0, line.find(' '));
                arrayofString.push_back(Dissolver(substr));
                substr = line.substr(line.find(' '), line.find('<') - line.find(' '));
                arrayofString.push_back(Dissolver(substr));
                line = line.substr(line.find('<'), line.length() - i);

                arrayofString.push_back("<-");
                i += 2;
                substr = line.substr(2, line.find('(') - 2);
                arrayofString.push_back(Dissolver(substr));
                line = line.substr(line.find('('), line.length() - 1);
                line = " " + line;
                i = 0;
            } /*else if (line[i] == ' ' && (line[i - 1] != '=' || line[i - 1] != '(')) {
                i = line.find(' ');
                string substr = line.substr(0, i);
                checkifEmpty = Dissolver(substr).length();
                if (checkifEmpty)
                    arrayofString.push_back(Dissolver(substr));
                line = line.substr(i, line.length() - i);
                i = 0;
            } */else if (line[i] == '=' && (line[i - 1] != '<' || line[i - 1] != '>')) {
                if (line[i + 1] == '=' || line[i - 1] == '=') {
                    arrayofString.push_back("==");
                    string substr = line.substr(0, line.find(' '));
                    arrayofString.push_back(Dissolver(substr));
                    substr = line.substr(line.find(' '), line.find('=') - line.find(' '));
                    arrayofString.push_back(Dissolver(substr));
                    line = line.substr(line.rfind('=') + 1, line.length() - i - 1);
                    int end = line.length() - 1;
                    if (line.find('{')) {
                        end = line.find('{');
                    }
                    substr = line.substr(0, end);

                    checkifEmpty = Dissolver(substr).length();
                    if (checkifEmpty)
                        arrayofString.push_back(Dissolver(substr));
                    if (line.find('{'))
                        arrayofString.push_back("{");
                } else {
                    string substr = line.substr(0, line.find(' '));
                    checkifEmpty = Dissolver(substr).length();
                    if (checkifEmpty)
                        arrayofString.push_back(Dissolver(substr));
                    substr = line.substr(line.find(' '), line.find('=') - line.find(' '));
                    checkifEmpty = Dissolver(substr).length();
                    if (checkifEmpty)
                        arrayofString.push_back(Dissolver(substr));
                    line = line.substr(line.find('='), line.length() - i);
                    i = line.find('=');
                    arrayofString.push_back("=");
                    i++;
                    substr = line.substr(i, line.length() - i);
                    checkifEmpty = Dissolver(substr).length();
                    if (checkifEmpty)
                        arrayofString.push_back(Dissolver(substr));
                    line = line.substr(i, line.length() - i);
                }
                break;
            } else if (line[i] == '}') {
                arrayofString.push_back("}");
            } else if (line[i] == '=' && (line[i - 1] == '<' || line[i - 1] == '>') ||
                       (line[i] == '>') && (line[i - 1] != '-')
                       || (line[i] == '<') && (line[i + 1] != '-')) {
                string substr = line.substr(0, line.find(' '));
                arrayofString.push_back(Dissolver(substr));
                if (line[i] == '<')
                    substr = line.substr(line.find(' '), line.find('<') - line.find(' '));
                else if (line[i] == '>')
                    substr = line.substr(line.find(' '), line.find('>') - line.find(' '));
                else if (line[i] == '=')
                    substr = line.substr(line.find(' '), line.find('=') - line.find(' '));
                arrayofString.push_back(Dissolver(substr));
                if (line[i] == '<' && line[i + 1] != '=') {
                    arrayofString.push_back("<");
                    int end = line.length() - 1;
                    if (line.find('{')) {
                        end = line.find('{');
                    }
                    substr = line.substr(line.find('<') + 1, end - line.find('<') - 1);
                } else if (line[i] == '>' && line[i + 1] != '=') {
                    arrayofString.push_back(">");
                    int end = line.length() - 1;
                    if (line.find('{')) {
                        end = line.find('{');
                    }
                    substr = line.substr(line.find('>') + 1, end - line.find('>') - 1);
                } else if (line[i + 1] == '=') {
                    if (line[i] == '<') {
                        arrayofString.push_back("<=");
                        int end = line.length() - 1;
                        if (line.find('{')) {
                            end = line.find('{');
                        }
                        substr = line.substr(line.find('=') + 2, end - line.find('=') - 2);
                    } else {
                        arrayofString.push_back(">=");
                        int end = line.length() - 1;
                        if (line.find('{')) {
                            end = line.find('{');
                        }
                        substr = line.substr(line.find('=') + 2, end - line.find('=') - 2);
                    }
                }
                checkifEmpty = Dissolver(substr).length();
                if (checkifEmpty)
                    arrayofString.push_back(Dissolver(substr));
                if (line.find('{'))
                    arrayofString.push_back("{");
                break;
            }
            i++;
        }
    }
    filereader.close();
    return arrayofString;
}


/**
 *this method creates a map of all the commands.
*/
void Lexer::createPairedVector() {

    int i = 0;
    while (i < arrayofString.size()) {
        if (arrayofString[i] == "openDataServer") {
            Command *a = new OpenServerCommand();
            commandsMap.emplace("openDataServer", a);
        }
        if (arrayofString[i] == "connectControlClient") {
            Command *a = new ConnectCommand();
            commandsMap.emplace("connectControlClient", a);
        }
        if (arrayofString[i] == "var") {
            Command *a = new DefineVarCommand();
            commandsMap.emplace(arrayofString[i + 1], a);
        }
        if (arrayofString[i] == "Print") {
            Command *a = new PrintCmd();
            commandsMap.emplace(arrayofString[i], a);
        }
        if (arrayofString[i] == "Sleep") {
            Command *a = new SleepCmd();
            commandsMap.emplace(arrayofString[i], a);
        }
        if (arrayofString[i] == "while") {
            Command *a = new LoopCommand();
            commandsMap.emplace(arrayofString[i], a);
        }
        i++;
    }
}

/**
* this method runs over all te commands and call their execute function.
*/
void Lexer::parser() {
    int j = 0;
    while (j < arrayofString.size()) {
        string s = arrayofString[j];
        string str = arrayofString[j + 1];
        Command *c = commandsMap.find(arrayofString[j])->second;
        if (c != NULL &&
            (arrayofString[j + 1] != "=" || arrayofString[j - 1] == "var" && arrayofString[j + 1] == "=")) {
            j += c->execute(j);
        } else if (arrayofString[j + 1] == "=") {
            UpdateVar *a = new UpdateVar(j);

            j += a->updateMap();
        }
    }
}


