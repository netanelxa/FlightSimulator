//
// Created by shiran on 12/20/19.
//
#include "ConnectCommand.h"
#include "UpdateVar.h"
#include <sys/socket.h>
#include <string>
#include <iostream>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include <string>
#include <cstring>
#include <thread>
#include "stack"

using namespace std;
stack<int> sockets;

/**
*constructor
 */
ConnectCommand::ConnectCommand() {}


void ConnectCommand::buffer(int client_socket) {

    //if here we made a connection
    char hello[] = "Hi from client";
    int is_sent = send(client_socket, hello, strlen(hello), 0);
    if (is_sent == -1) {
        std::cout << "Error sending message" << std::endl;
    } else {
        std::cout << "Hello message sent to server" << std::endl;
    }

    char buffer[1024] = {0};
    while (buffer)
        int valread = read(client_socket, buffer, 1024);
    std::cout << buffer << std::endl;

    close(client_socket);
}

/**
* this method executes the connect command. it opens a thread.
 * @param currentPlace is the index of the current command.
 * @returnsteps to the next command.
*/
int ConnectCommand::execute(int currentPlace) {
    this->interpreter = new Interpreter;
    //create socket
    int client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket == -1) {
        //error
        std::cerr << "Could not create a socket" << std::endl;
        return -1;
    }

    //We need to create a sockaddr obj to hold address of server
    sockaddr_in address; //in means IP4
    address.sin_family = AF_INET;//IP4

    string ipString = arrayofString[currentPlace + 1];
    const char *IP = ipString.c_str();
    address.sin_addr.s_addr = inet_addr(IP);  //the localhost address
    string exp = arrayofString[currentPlace + 2];
    unsigned int PORT = 1;
    if (exp.find('+') > 0 || exp.find('-') > 0 || exp.find('/') > 0 || exp.find('*') > 0) {
        Expression *e4 = interpreter->interpret(exp);
        PORT = stoi(to_string(e4->calculate()));
    } else {
        PORT = stoi(arrayofString[currentPlace + 2]);
    }
    cout << "Clinet port" << PORT << endl;
    address.sin_port = htons(PORT);

    //we need to convert our number (both port & localhost)
    // to a number that the network understands.

    // Requesting a connection with the server on local host with port 8081
    int is_connect = connect(client_socket, (struct sockaddr *) &address, sizeof(address));
    if (is_connect == -1) {
        std::cerr << "Could not connect to host server" << std::endl;
        return -2;
    } else {
        std::cout << "Client is now connected to server" << std::endl;
    }
    sockets.push(client_socket);
    thread thread1([client_socket, this] { buffer(client_socket); });
    thread1.detach();


    return 4;
}
