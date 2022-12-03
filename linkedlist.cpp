#include <iostream>
#include <string>
#include "node.cpp"

using namespace std;

template <typename T>
class linkedlist{
    public:
    node<T> * first;
    void push(T data){
        node<T> * newnode = new node<T>();
        newnode->data = data;
        newnode->next = NULL;

        if(this->first == NULL){
            this->first = newnode;
        } else {
            node<T> * temp = this->first;
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = newnode;
        }
    }
    void print(){
        node<T> * temp = this->first;
        while(temp != NULL){
            cout << temp->data << endl;
            temp = temp->next;
        }
    }
};