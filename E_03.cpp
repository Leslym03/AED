#include <iostream>
#include "listaordenada.h"
using namespace std;

template <typename T>
linkedListIterator<T> find( linkedListIterator<T> begin, linkedListIterator<T> end, const T x ){
	for(linkedListIterator<T> temp = begin; temp !=end ; ++temp){
		if(x==*temp)
			return temp;
	}
	return end;
}


int main(){
    ListaOrdenada<int> a;
	a.insert(7);
	a.insert(8);
	a.insert(9);
	a.insert(10);
	
    find(a.begin(),a.end(),8);
	cout<<endl;
	return 0;
}

