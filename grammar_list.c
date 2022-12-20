#include <stdio.h>
#include <stdlib.h>

struct grammar_list
{
    grammar_node * first;
    grammar_node * next;
};

void grammarListPush(grammar_list * list, grammar_node_data * data)
{
    grammar_node * newnode = (struct grammar_node *) malloc (sizeof(struct grammar_node));
    newnode->data = data;
    newnode->next = NULL;

    if (list->first == NULL)
    {
        list->first = newnode;
        list->next = newnode;
    }
    else
    {
        grammar_node * temp_grammar = list->first;
        while (temp_grammar->next != NULL)
        {
            temp_grammar = temp_grammar->next;
        }
        temp_grammar->next = newnode;
    }
}
bool grammarListNextNode(grammar_list * list)
{
    if (list->next->next != NULL)
    {
        list->next = list->next->next;
        return true;
    }
    return false;
}
void grammarListFirstNode(grammar_list * list)
{
    list->next = list->first;
}