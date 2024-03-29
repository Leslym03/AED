#include<iostream>
using namespace std;

template <typename Object>
struct node {
    node () { next = NULL;}
    node (Object obj) : data(obj) {}
    node (Object obj, node * ptr) : data(obj), next(ptr) {}
    Object data;
    node * next;
};

template <typename Object>
class stack {
public:
    stack () { head = NULL;}
    ~stack() { while (head) pop(); }
    
    void push(Object obj){
        node<Object> * ptr = new node<Object>(obj, head);
        head= ptr;
    }
    Object top(){
        return (head->data); 
    }
    void pop() {
        node<Object> * ptr = head->next;
        delete head;
        head = ptr;
    }
private:
    node<Object> * head;
};

int main(){
    return 0;
}