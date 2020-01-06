# FlightSimulator
Netanel Abu

Shiran Ben-Meir


## Description
This project represents interpreter that controls an airplane in a flight simulator. 
The Flight-Simulator program receives a text fly named "fly.txt" that contains commands.
The Lexer reads the file and is able to split lines to tokens. The tokens are inserted to a vector of tokens. Using a HashMap of commands that was created, the Parser executes each command from the text file.

First commans is "Open Data Server". While executing this command, the program opens up a thread that runs a server that listens to a port. The port was given in the text file.
Second command is "Connect Control Client". While executing this command, the program connects as a client in  a different thread. 

Other commands are represented in HashMap. Using this HashMap, the server or the client are updated respectively.
The program handles Print and Sleep commands along with while and if conditions. In addition, the program handles math expressions that are given in the file.


## Running Instructions
1. download and install ‫‪FlightGear‬‬ simulator.
2. set the "additional settings" to be:

       --telnet=socket,in,10,127.0.0.1,5402,tcp
       --generic=socket,out,10,127.0.0.1,5400,tcp,generic_small
3. in terminal, run the command:
     
        g++ -std=c++14 *.cpp -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -o a.out -pthread
   and then:
       
       ./a.out fly.txt
       
4. when the program prints "server is litening..."- start the simulator by pressing "fly!".


## More
FlightGear link https://www.flightgear.org/

github link https://github.com/netanelxa/FlightSimulator

