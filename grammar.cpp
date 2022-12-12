#include <iostream>
#include <fstream>
#include <string>

class grammar{
    public:
    char * terminal;
    char * nonTerminal;

    grammar(){
        
    }
    grammar(char * nonTerminal, char * terminal){
        this->terminal = terminal;
        this->nonTerminal = nonTerminal;
    }
};