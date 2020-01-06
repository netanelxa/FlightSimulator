//
// Created by shiran on 12/18/19.
//

#include "OpenServerCommand.h"
#include <exception>


using namespace std;
extern map<string, VarObj *> fromSim_map;
extern vector<pair<string, double>> genericMap;
/**
* constructor
*/
OpenServerCommand::OpenServerCommand() {}

/**
* this method receives valuse from server and updates generic map.
 * @param client_socket is the number of the socket.
*/
void OpenServerCommand::StartServer(int client_socket) {
    string firstBuffer = "";
    int temp = 0;
    vector<double> vec;
    while (temp < 1000) {
        char line[1024] = {0};
        read(client_socket, line, 1024);
        string secondBuffer = line;
        firstBuffer = firstBuffer + secondBuffer;
        string firstToken = firstBuffer.substr(0, firstBuffer.find("\n"));
        string seconedToken = firstBuffer.substr(firstBuffer.find("\n") + 1, firstBuffer.length());
        for (int i = 0; i < 36; i++) {
            int pos = firstToken.find(",");
            vec.push_back(stod(firstToken.substr(0, pos)));
            firstToken = firstToken.substr(pos + 1);
        }
        int i = 0;
        for (pair<string, double> x : genericMap) {
            genericMap[i].second = vec[i];
            i++;
        }
        upd->updateFromSim(genericMap);
        i = 0;
        vec.clear();
        firstBuffer = seconedToken;
    }
}

/**
* this method execute openServer command. it opens a thread, creates sockts and generic map.
 * @param currentPlace is the index of the current command in the file.
 * @return index of next command.
*/
int OpenServerCommand::execute(int currentPlace) {
    this->upd = new UpdateGeneric();
    this->interpreter = new Interpreter;

    //insert values to generic map.

    genericMap.push_back(pair<string, double>("/instrumentation/airspeed-indicator/indicated-speed-kt", 0));
    genericMap.push_back(pair<string, double>("/sim/time/warp", 0));
    genericMap.push_back(pair<string, double>("/controls/switches/magnetos", 0));
    genericMap.push_back(pair<string, double>("/instrumentation/heading-indicator/offset-deg", 0));
    genericMap.push_back(pair<string, double>("/instrumentation/altimeter/indicated-altitude-ft", 0));
    genericMap.push_back(pair<string, double>("/instrumentation/altimeter/pressure-alt-ft", 0));
    genericMap.push_back(pair<string, double>("/instrumentation/attitude-indicator/indicated-pitch-deg", 0));
    genericMap.push_back(pair<string, double>("/instrumentation/attitude-indicator/indicated-roll-deg", 0));
    genericMap.push_back(pair<string, double>("/instrumentation/attitude-indicator/internal-pitch-deg", 0));
    genericMap.push_back(pair<string, double>("/instrumentation/attitude-indicator/internal-roll-deg", 0));
    genericMap.push_back(pair<string, double>("/instrumentation/encoder/indicated-altitude-ft", 0));
    genericMap.push_back(pair<string, double>("/instrumentation/encoder/pressure-alt-ft", 0));
    genericMap.push_back(pair<string, double>("/instrumentation/gps/indicated-altitude-ft", 0));
    genericMap.push_back(pair<string, double>("/instrumentation/gps/indicated-ground-speed-kt", 0));
    genericMap.push_back(pair<string, double>("/instrumentation/gps/indicated-vertical-speed", 0));
    genericMap.push_back(pair<string, double>("/instrumentation/heading-indicator/indicated-heading-deg", 0));
    genericMap.push_back(pair<string, double>("/instrumentation/magnetic-compass/indicated-heading-deg", 0));
    genericMap.push_back(pair<string, double>("/instrumentation/slip-skid-ball/indicated-slip-skid", 0));
    genericMap.push_back(pair<string, double>("/instrumentation/turn-indicator/indicated-turn-rate", 0));
    genericMap.push_back(pair<string, double>("/instrumentation/vertical-speed-indicator/indicated-speed-fpm", 0));
    genericMap.push_back(pair<string, double>("/controls/flight/aileron", 0));
    genericMap.push_back(pair<string, double>("/controls/flight/elevator", 0));
    genericMap.push_back(pair<string, double>("/controls/flight/rudder", 0));
    genericMap.push_back(pair<string, double>("/controls/flight/flaps", 0));
    genericMap.push_back(pair<string, double>("/controls/engines/engine/throttle", 0));
    genericMap.push_back(pair<string, double>("/controls/engines/current-engine/throttle", 0));
    genericMap.push_back(pair<string, double>("/controls/switches/master-avionics", 0));
    genericMap.push_back(pair<string, double>("/controls/switches/starter", 0));
    genericMap.push_back(pair<string, double>("/engines/active-engine/auto-start", 0));
    genericMap.push_back(pair<string, double>("/controls/flight/speedbrake", 0));
    genericMap.push_back(pair<string, double>("/sim/model/c172p/brake-parking", 0));
    genericMap.push_back(pair<string, double>("/controls/engines/engine/primer", 0));
    genericMap.push_back(pair<string, double>("/controls/engines/current-engine/mixture", 0));
    genericMap.push_back(pair<string, double>("/controls/switches/master-bat", 0));
    genericMap.push_back(pair<string, double>("/controls/switches/master-alt", 0));
    genericMap.push_back(pair<string, double>("/engines/engine/rpm", 0));
    string exp = arrayofString[currentPlace + 1];
    unsigned int PORT = 0; // initialize port number
    if (exp.find('+') > 0 || exp.find('-') > 0 || exp.find('/') > 0 || exp.find('*') > 0) {
        Expression *e4 = interpreter->interpret(exp);
         int PORT = stoi(to_string(e4->calculate()));
    } else {
         int PORT = stoi(arrayofString[currentPlace + 1]);
    }

    //create socket
    int socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
    }

    //bind socket to IP address
    // we first need to create the sockaddr obj.
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY; //give me any IP allocated for my machine
    address.sin_port = htons(PORT);
    //we need to convert our number
    // to a number that the network understands.

    //the actual bind command
    if (bind(socketfd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        std::cerr << "Could not bind the socket to an IP" << std::endl;
    }

    //making socket listen to the port
    if (listen(socketfd, 5) == -1) { //can also set to SOMAXCON (max connections)
        std::cerr << "Error during listening command" << std::endl;
    } else {
        std::cout << "Server is now listening ..." << std::endl;
    }

    // accepting a client
    {
        int client_socket = accept(socketfd, (struct sockaddr *) &address, (socklen_t *) &address);
        cout << "Client accepted" << endl;
        if (client_socket == -1) {
            std::cout << "Error accepting client" << std::endl;
        }

        close(socketfd); //closing the listening socket

        thread thread1([=] { StartServer(client_socket); });
        bool a = thread1.joinable();
        if (thread1.joinable()) {
            thread1.detach();
        }
    }

    return 2;
}