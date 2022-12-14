#include <iostream>
#include <string>
#include "node.cpp"

using namespace std;

template <typename T>
class stack
{
public:
    node<T> *top;
    void push(T data)
    {
        node<T> *newnode = new node<T>();
        newnode->data = data;
        newnode->next = NULL;

        if (this->top == NULL)
        {
            this->top = newnode;
        }
        else
        {
            newnode->next = this->top;
            this->top = newnode;
        }
    }
    void print()
    {
        node<T> *temp = this->top;
        while (temp != NULL)
        {
            cout << temp->data << endl;
            temp = temp->next;
        }
    }
    node<T> *pop()
    {
        if (this->top != NULL)
        {
            cout << this->top->data;
            this->top = this->top->next;
        }
    }
};