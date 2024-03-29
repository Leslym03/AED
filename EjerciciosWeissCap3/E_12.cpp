#include<iostream>
using namespace std;

template <typename Object>
struct Node {
    Object data;
    Node * next;
    Node ( const Object&d= Object(), Node *n = NULL ): data(d) , next(n) {}
};

template <typename Object>
class singleList {
public:
    singleList( ) { 
        init(); 
    }
    ~singleList(){
        eraseList(head);
    }
    singleList( const singleList & rhs){
        eraseList(head);
        init();
        *this = rhs;
    }
    bool add(Object x) {
        if (contains(x))
            return false;
        else {
            Node<Object> *ptr = head->next;
            Node<Object>* trailer = head;
            while(ptr && ptr->data < x) {
                trailer = ptr;
                ptr = ptr->next;
            }
            trailer->next = new Node<Object> (x);
            trailer->next->next = ptr;
            theSize++;
        }
        return true;
    }
    bool remove(Object x) {
        if (!contains(x))
            return false;
        else {
            Node<Object>*ptr = head->next;
            Node<Object>*trailer;
            while(ptr->data != x){ 
                trailer = ptr;
                ptr=ptr->next;
            }
            trailer->next = ptr->next;
            delete ptr;
            theSize--;
        }
        return true;
    }
    int size() { 
        return theSize;
    }
    void print() {
        Node<Object> *ptr = head->next;
        while (ptr != NULL) {
            cout<< ptr->data<<" ";
            ptr = ptr->next;
        }
        cout<<endl;
    }
    bool contains(const Object & x) {
        Node<Object> * ptr = head->next;
        while (ptr != NULL && ptr->data <= x ) {
            if (x == ptr->data)
                return true;
            else
                ptr = ptr-> next;
        }
        return false;
    }
    void init() {
        theSize = 0;
        head = new Node<Object>;
        head-> next = NULL;
    }
    void eraseList(Node<Object> * h) {
        Node<Object> *ptr= h;
        Node<Object> *nextPtr;
        while(ptr != NULL) {
            nextPtr = ptr->next;
            delete ptr;
            ptr= nextPtr;
        }
    }
private:
    Node<Object> *head;
    int theSize;
};


int main(){
    return 0;
}