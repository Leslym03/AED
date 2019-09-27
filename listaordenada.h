
#ifndef LISTAORDENADA_H
#define LISTAORDENADA_H

#include "linkedlist.h"
#include <iostream>
using namespace std;

template <class T>
class ListaOrdenada : public linkedList<T>{
public:
    bool search(const T elemento) const;
    void insert(const T item);
    void insertFirst(const T item);
    void insertLast(const T item);
    void deleteNode(const T deleteItem);

};


template <class T>
bool ListaOrdenada<T>::search(const T elemento) const{
    Nodo<T> *current;
    bool found = false;
    current = this->first;
    while (current != NULL && !found)
        if (current->data == elemento)
            found = true;
        else
            current = current->link;
    return found;
}

template <class T>
void ListaOrdenada<T>::insert(const T item){
    Nodo<T> *current;   
    Nodo<T> *aux;
    Nodo<T> *newNode;   
    bool found;
    newNode = new Nodo<T>;
    newNode->data = item;     
    newNode->link = NULL;         
    if (this->first == NULL) {
        this->first = newNode;
        this->last = newNode;
        this->count++;
    }
    else{
        current = this->first;
        found = false;
        while (current != NULL && !found) 
            if (current->data >= item)
                found = true;
            else{
                aux = current;
                current = current->link;
            }
        if (current == this->first) {
            newNode->link = this->first;
            this->first = newNode;
            this->count++;
        }
        else{
            aux->link = newNode;
            newNode->link = current;
            if (current == NULL)
                this->last = newNode;
            this->count++;
        }
    } 
}

template <class T>
void ListaOrdenada<T>::insertFirst(const T item){
    insert(item);
}
template <class T>
void ListaOrdenada<T>::insertLast(const T item){
    insert(item);
}

template <class T>
void ListaOrdenada<T>::deleteNode(const T elemento){
    Nodo<T> *current;
    Nodo<T> *aux;
    bool found;
    if (this->first == NULL) 
        cout << "La lista esta vacia no se puede borrar" << endl;
    else{
        if (this->first->data == elemento){
            current = this->first;
            this->first = this->first->link;
            this->count--;
            if (this->first == NULL)
                this->last = NULL;
            delete current;
        }
        else{
            found = false;
            aux = this->first;
            current = this->first->link;
            while (current != NULL && !found){
                if (current->data != elemento){
                    aux = current;
                    current = current->link;
                }
                else
                    found = true;
            }
            if (found){
                aux->link = current->link;
                this->count--;
                if (this->last == current)
                    this->last = aux;
                delete current;
            }
            else
                cout << "El elemento a borrar no esta en la lista" << endl;
        }
    }
}

#endif
