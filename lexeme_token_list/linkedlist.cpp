#include <iostream>
#include <string>
#include "node.cpp"

using namespace std;

class linkedlist{
    public:
    node * first;
    void push(string lexeme, string token){
        node * newnode = new node();
        newnode->data = lexeme_token(lexeme, token);
        newnode->next = NULL;

        if(this->first == NULL){
            this->first = newnode;
        } else {
            node * temp = this->first;
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = newnode;
        }
    }
    void print(){
        node * temp = this->first;
        printf("\n");
        while(temp != NULL){
            printf("(%s \"%s\") ", temp->data.token.c_str(), temp->data.lexeme.c_str());
            temp = temp->next;
        }
    }
};