#include <iostream>
#include <fstream>
#include <string>

class grammarNode
{
public:
    char *terminal;
    char *nonTerminal;

    grammarNode()
    {
    }
    grammarNode(char *nonTerminal, char *terminal)
    {
        this->terminal = terminal;
        this->nonTerminal = nonTerminal;
    }
};