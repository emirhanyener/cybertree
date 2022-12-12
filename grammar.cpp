#include <iostream>
#include <fstream>
#include <string>
#define grammarCount 15

class grammar{
    public:
    char * terminal;
    char * nonTerminal;

    grammar(){
        this->terminal = "";
        this->nonTerminal = "";
    }
    grammar(char * nonTerminal, char * terminal){
        this->terminal = terminal;
        this->nonTerminal = nonTerminal;
    }
};