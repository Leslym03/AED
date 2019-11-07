#include <iostream>
#include "listaordenada.h"
using namespace std;

template <class T>
ListaOrdenada<T> unir(ListaOrdenada<T> a,ListaOrdenada<T> b){
	ListaOrdenada<T> temp;
	for(linkedListIterator<T> i=a.begin();i!=a.end();++i){
		if(!temp.search(*i))
			temp.insert(*i);
	}
	for(linkedListIterator<T> i=b.begin();i!=b.end();++i){
		if(!temp.search(*i))
			temp.insert(*i);
	}
	return temp;
}

int main(){
    ListaOrdenada<int> L1;
	ListaOrdenada<int> L2;
	L1.insert(9);
	L1.insert(8);
	L1.insert(7);
	L1.insert(6);

	L2.insert(5);
	L2.insert(8);
	L2.insert(7);
	L2.insert(3);

    ListaOrdenada<int> todos;
	todos = unir(L1,L2);
	todos.print();
	cout<<endl;
    
	return 0;
}