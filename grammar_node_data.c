#include <stdio.h>
#include <stdlib.h>

struct grammar_node_data
{
    char * terminal;
    char * nonTerminal;
};

struct grammar_node_data * createGrammarNodeData(char *nonTerminal, char *terminal)
{
    struct grammar_node_data * newNode = (struct grammar_node_data *) malloc (sizeof(struct grammar_node_data));
    newNode->terminal = terminal;
    newNode->nonTerminal = nonTerminal;
    return newNode;
}