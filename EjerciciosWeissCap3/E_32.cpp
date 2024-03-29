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
class queue{
public:
    queue () { front = NULL; rear = NULL;}
    ~queue() { while (front) deque(); }
    
    void enque(Object obj) {
        node<Object> * ptr = new node<Object>(obj, NULL);
        if (rear)
            rear= rear->next = ptr;
        else
            front = rear = ptr;
    }
    Object deque() {
        Object temp = front->data;
        node<Object> * ptr = front;
        if (front->next == NULL) // only 1 node
            front = rear = NULL;
        else
            front = front->next;
        delete ptr;
        return temp;
    }
private:
    node<Object> * front;
    node<Object> * rear;
};


int main(){
    return 0;
}