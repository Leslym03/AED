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
class queue {
public:
    queue(int s): maxSize(s), front(0), rear(0) {elements.resize(maxSize);}
    queue () { maxSize = 100; front = 0;
    rear = 0;elements.resize(maxSize);}
    ~queue() { while (front!=rear) deque(); }
    
    void enque(Object obj) {
        if (! full()) {
            elements[rear] = obj;
            rear = (rear + 1) % maxSize;
        }
    }
    Object deque(){ 
        Object temp;
        if (!empty()) {
            temp= elements[front];
            front = (front +1 ) % maxSize;
            return temp;
        }
    }
    bool empty() {return front == rear;}
    bool full() { return (rear + 1) % maxSize == front;}
private:
    int front, rear;
    int maxSize;
    vector<Object> elements ;
};


int main(){
    return 0;
}