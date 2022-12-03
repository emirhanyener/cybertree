#include <iostream>
#include <string>
#include "linkedlist.cpp"

using namespace std;

template <typename T>
class tree{
    public:
    T data;
    linkedlist<T> * nodes = new linkedlist<T>();
    tree(T data){
        this->data = data;
    }
    void push(T data){
        nodes->push(data);
    }
    void print(){
        linkedlist<T> * temp = this->nodes;
        while(temp != NULL){
            temp->print();
            temp = temp->next;
        }
    }
};