#include <iostream>
#include <fstream>
#include <string>

struct grammarNode
{
    char * terminal;
    char * nonTerminal;
};

grammarNode * createGrammarNode(char *nonTerminal, char *terminal)
{
    grammarNode * newNode = (struct grammarNode *) malloc (sizeof(struct grammarNode));
    newNode->terminal = terminal;
    newNode->nonTerminal = nonTerminal;
    return newNode;
}