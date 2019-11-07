#ifndef DOUBLELINKEDLIST_H
#define DOUBLELINKEDLIST_H

#include "linkedlist.h"

#include <iostream>
using namespace std;
template <class T>
class doubleLinkedList : public linkedList<T>{
	public:
    class const_reverse_iterator{
        friend class doubleLinkedList<T>;
        const_reverse_iterator( ) : current{ nullptr }{}

        const T & operator* ( ) const
        { return current->data; }

        const_reverse_iterator & operator++ ( ){
            current = current->prev_link;
            return *this;
        }

        const_reverse_iterator operator++ ( int ){
            const_reverse_iterator old = *this;
            -- *this;
            return old;
        }

        bool operator== ( const const_reverse_iterator & rhs ) const
        { return current == rhs.current; }
        bool operator!= ( const const_reverse_iterator & rhs ) const
        { return !( *this == rhs ); }

        protected:
            Nodo<T> *current;
            const_reverse_iterator( Nodo<T> *p ) : current(p){}
    };

    class reverse_iterator : public const_reverse_iterator{
        public:
        friend class doubleLinkedList<T>;
            reverse_iterator(){
                this->current=nullptr;
            }
            const T & operator* ( ) const{
                return const_reverse_iterator::operator*();
            }

            T & operator*(){
                return this->current->data;
            }

            reverse_iterator & operator++ ( ){
                this->current = this->current->prev_link;
                return *this;
            }

            reverse_iterator operator++ ( int ){
                reverse_iterator old = *this;
                ++*this;
                return old;
            }

            bool operator== ( const reverse_iterator & rhs ) const
            { return this->current == rhs.current; }

            bool operator!= ( const reverse_iterator & rhs ) const
            { return !( *this == rhs ); }

        protected:
            reverse_iterator(Nodo<T>* a){
                this->current=a;
            }
    };

    reverse_iterator rbegin(){
        reverse_iterator temp(this->last);
        return temp;
    }

    reverse_iterator rend(){
        reverse_iterator temp(nullptr);
        return temp;
    }
		bool search(const T elemento) const;
		void insertFirst(const T item);
		void insertLast(const T item);
		void deleteNode(const T elemento);
        void swap(int pos1,int pos2);
};


template <class T>
void doubleLinkedList<T>::swap(int pos1,int pos2){
    Nodo<T>* current=this->first;
    
    for(int i=0;i<pos1;i++)
        current=current->link;
    if(current==this->first){
        this->first=current->link;
        current->link=current->link->link;
        this->first->link=current;
        current->prev_link=this->first;
        this->first->prev_link=nullptr;
        current->link->prev_link = current;
    }
}

template <class T>
bool doubleLinkedList<T>::search(const T elemento) const{
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
void doubleLinkedList<T>::insertFirst(const T item){
    Nodo<T> *newNode;
    newNode = new Nodo<T>;
    newNode->data = item;
    newNode->link = this->first;
    newNode->prev_link = nullptr ;
    if(this->count)
        this->first->prev_link = newNode; 
    this->first = newNode;
    this->count++;
    if (this->last == NULL)
        this->last = newNode;
}

template <class T>
void doubleLinkedList<T>::insertLast(const T item){
    Nodo<T> *newNode;
    newNode = new Nodo<T>;
    newNode->data = item;
    newNode->link = NULL;
    newNode->prev_link = this->last;
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
void doubleLinkedList<T>::deleteNode(const T elemento){
    Nodo<T> *current;
    Nodo<T> *aux;
    bool found;
    if (this->first == NULL)
        cout << "La lista esta vacia no se puede borrar" << endl;
    else{
        if (this->first->data == elemento){
            current = this->first;
            this->first = this->first->link;
            this->first->prev_link=nullptr;
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
