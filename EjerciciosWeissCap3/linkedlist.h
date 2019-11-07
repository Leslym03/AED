#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "nodo.h"
#include "linkedlistiterator.h"
#include <iostream>
using namespace std;

template <class T>
class linkedList{
public:
    const linkedList<T> &operator=(const linkedList<T> &);
    void initializeList();
    bool isEmptyList() const;
    void print() const;
    int length() const;
    void destroyList();
    T front() const;
    T back() const;
    virtual bool search(const T searchItem) const = 0;
    virtual void insertFirst(const T item) = 0;
    virtual void insertLast(const T item) = 0;
    virtual void deleteNode(const T deleteItem) = 0;
    linkedListIterator<T> begin();
    linkedListIterator<T> end();
    linkedList();
    linkedList(const linkedList<T> &otherList);
    ~linkedList();

protected:
    int count;
    Nodo<T> *first;
    Nodo<T> *last;
    Nodo<T> *invalid_node;
    void copyList(const linkedList<T> &otherList);
};

template <class T>
bool linkedList<T>::isEmptyList() const{
    return (first == NULL);
}

template <class T>
linkedList<T>::linkedList(){
    invalid_node=nullptr;
    first = NULL;
    last = NULL;
    count = 0;
}

template <class T>
void linkedList<T>::destroyList(){
    Nodo<T> *temp;
    while (first != NULL){
        temp = first;
        first = first->link;
        delete temp;
    }
    last = NULL;
    count = 0;
}

template <class T>
void linkedList<T>::initializeList(){
    destroyList();
}

template <class T>
void linkedList<T>::print() const{
    Nodo<T> *current;
    current = first;
    while (current != NULL){
        cout << current->data << " ";
        current = current->link;
    }
}

template <class T>
int linkedList<T>::length() const{
    return count;
}

template <class T>
T linkedList<T>::front() const{
    assert(first != NULL);
    return first->data;
}

template <class T>
T linkedList<T>::back() const{
    assert(last != NULL);
    return last->data;
}

template <class T>
linkedListIterator<T> linkedList<T>::begin(){
    linkedListIterator<T> temp(first);
    return temp;
}

template <class T>
linkedListIterator<T> linkedList<T>::end(){
    linkedListIterator<T> temp(NULL);
    return temp;
}

template <class T>
void linkedList<T>::copyList(const linkedList<T> &otherList){
    Nodo<T> *newNode;
    Nodo<T> *current;
    if (first != NULL)
        destroyList();
    if (otherList.first == NULL){
        first = NULL;
        last = NULL;
        count = 0;
    }
    else{
        current = otherList.first;
        count = otherList.count;
        first = new Nodo<T>;
        first->data = current->data;
        first->link = NULL;
        last = first;
        current = current->link;
        while (current != NULL)
        {
            newNode = new Nodo<T>;
            newNode->data = current->data;
            newNode->link = NULL;
            last->link = newNode;
            last = newNode;
            current = current->link;
        }
    }
}

template <class T>
linkedList<T>::~linkedList(){
    destroyList();
}

template <class T>
linkedList<T>::linkedList(const linkedList<T> &otherList){
    first = NULL;
    copyList(otherList);
}

template <class T>
const linkedList<T> &linkedList<T>::operator=(const linkedList<T> &otherList){
    if (this != &otherList)
        copyList(otherList);
    return *this;
}
#endif

