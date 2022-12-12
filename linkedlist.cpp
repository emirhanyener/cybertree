#include <iostream>
#include <string>
#include "node.cpp"

using namespace std;

template <typename T>
class linkedlist{
    public:
    node<T> * first;
    node<T> * next;
    void push(T data){
        node<T> * newnode = new node<T>();
        newnode->data = data;
        newnode->next = NULL;

        if(this->first == NULL){
            this->first = newnode;
            this->next = newnode;
        } else {
            node<T> * temp = this->first;
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = newnode;
        }
    }
    bool nextNode(){
        if(this->next->next != NULL){
            this->next = this->next->next;
            return true;
        } 
        return false;
    }
    void firstNode(){
        this->next = this->first;
    }
};