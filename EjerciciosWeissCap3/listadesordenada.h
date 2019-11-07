#ifndef LISTADESORDENADA_H
#define LISTADESORDENADA_H 

#include "linkedlist.h"
#include <iostream>
using namespace std;

template <class T>
class ListaDesordenada : public linkedList<T>{
public:
    bool search(const T elemento) const;
    void insertFirst(const T item);
    void insertLast(const T item);
    void deleteNode(const T deleteItem);
    void swap(int pos1, int pos2);
    void splice(int ,ListaDesordenada<T>&);
};

template <class T>
void ListaDesordenada<T>::splice(int position,ListaDesordenada<T>& List){
    Nodo<T>* temp= this->first;
    for(int i=0;i<position;i++)
        temp = temp->link;
    for(linkedListIterator<T> it=List.begin();it!=List.end();++it){
        Nodo<T>* newNodo= new Nodo<T>;
        newNodo->data=*it;
        newNodo->link=temp->link;
        temp->link=newNodo;
        this->count++;
        temp=temp->link;
    }
    List.initializeList();
}

template <class T>
void ListaDesordenada<T>::swap(int pos1,int pos2){
	Nodo<T>* aux= this->first;
	Nodo<T>* anterior = aux;
	if(pos1>= this->count || pos2>= this->count)
		return;
	if(!(pos1-pos2==1 || pos1-pos2==-1))
		return;
	if(pos1>pos2){
        int temp=pos1;
        pos1=pos2;
        pos2=temp;
    }

    for(int i=0;i<pos1;i++){
        anterior =aux;
        aux = aux->link;
    }
    if(aux==anterior){
        this->first =aux->link;
        aux->link=aux->link->link;
        this->first->link=aux;
    }
    else{
        anterior->link = aux->link;
        aux->link=(aux->link)->link;
        anterior->link->link=aux;
    }
}

template <class T>
bool ListaDesordenada<T>::search(const T elemento) const{
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
void ListaDesordenada<T>::insertFirst(const T item){
    Nodo<T> *newNode;
    newNode = new Nodo<T>;
    newNode->data = item;
    newNode->link = this->first;
    newNode->Stole=false;
    this->first = newNode;
    this->count++;
    if (this->last == NULL)
        this->last = newNode;
}

template <class T>
void ListaDesordenada<T>::insertLast(const T item){
    Nodo<T> *newNode;
    newNode = new Nodo<T>;
    newNode->data = item;
    newNode->link = NULL;
    newNode->Stole=false;
    if (this->first == NULL){
        this->first = newNode;
        this->last = newNode;
        this->count++;
    }
    else{
        this->last->link = newNode;
        this->last = newNode;
        this->count++;
    }
}

template <class T>
void ListaDesordenada<T>::deleteNode(const T elemento){
    Nodo<T> *aux;
    bool found;
    if (this->first == NULL)
        cout << "La lista esta vacia no se puede borrar" << endl;
    else{
        if (this->first->data == elemento){
            this->invalid_node = this->first;
            this->first = this->first->link;
            this->count--;
            if (this->first == NULL)
                this->last = NULL;
            this->invalid_node->Stole=true;
            delete this->invalid_node;
            
            
        }
        else{
            found = false;
            aux = this->first;
            this->invalid_node = this->first->link;
            while (this->invalid_node != NULL && !found){
                if (this->invalid_node->data != elemento){
                    aux = this->invalid_node;
                    this->invalid_node = this->invalid_node->link;
                }
                else
                    found = true;
            }
            if (found){
                aux->link = this->invalid_node->link;
                this->count--;
                if (this->last == this->invalid_node)
                    this->last = aux;
                delete this->invalid_node;
                this->invalid_node->Stole=true;
            }
            else
                cout << "El elemento a borrar no esta en la lista" << endl;
        }
    }
}

#endif
