# FlightSimulator

## Description
The Flight-Simulator program receives a text fly named "fly.txt" that contains commands. 
The Lexer reads the file and is able to split lines to tokens. The tokens are inserted to a vector of tokens. Using a HashMap of commands that was created, the Parser executes each command from the text file.

First commans is "Open Data Server". While executing this command, the program opens up a thread that runs a server that listens to a port. The port was given by the text file.
Second command is "Connect Control Client". While executing this command, the program connects as a client in  a different thread. 
Other commands are represented in HashMap. Using this HashMap, the server or the client are updated re
