#ifndef LINKEDLISTITERATOR_H
#define LINKEDLISTITERATOR_H

template <class T>
class linkedListIterator{
public:
    linkedListIterator();
    linkedListIterator(Nodo<T> *ptr);
    T operator*();
    linkedListIterator<T> operator++();
    linkedListIterator<T> operator+(int);
    bool operator==(const linkedListIterator<T> &right) const;
    bool operator!=(const linkedListIterator<T> &right) const;
    linkedListIterator<T> operator--();
    linkedListIterator<T> operator-(int num);
    bool isStole(){ return current->Stole; }

private:
    Nodo<T> *current;
};

template <class T>
linkedListIterator<T>::linkedListIterator(){
    current = NULL;
}

template <class T>
linkedListIterator<T>::linkedListIterator(Nodo<T> *ptr){
    current = ptr;
}

template <class T>
T linkedListIterator<T>::operator*(){
    return current->data;
}

template <class T>
linkedListIterator<T> linkedListIterator<T>::operator++(){
    current = current->link;
    return *this;
}

template<class T>
linkedListIterator<T> linkedListIterator<T>::operator+(int num){
    linkedListIterator<T> temp=*this;
    for(int i=0;i<num;i++)
        ++temp;
    return temp;
}

template <class T>
linkedListIterator<T> linkedListIterator<T>::operator--(){
    current=current->prev_link;
    return *this;
}

template <class T>
linkedListIterator<T> linkedListIterator<T>::operator-(int num){
    linkedListIterator<T> temp=*this;
    for(int i=0;i<num;i++)
        --temp;
    return temp;
}

template <class T>
bool linkedListIterator<T>::operator==(const linkedListIterator<T> &other) const{
    return (current == other.current);
}

template <class T>
bool linkedListIterator<T>::operator!=(const linkedListIterator<T> &other) const{
    return (current != other.current);
}

#endif

