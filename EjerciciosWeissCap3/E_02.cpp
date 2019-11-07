#include <iostream>
#include "listadesordenada.h"
#include "doublelinkedlist.h"
using namespace std;

int main(){
    ListaDesordenada<int> L1;
	L1.insertLast(1);
	L1.insertLast(2);
	L1.insertLast(8);
	L1.insertLast(9);

    doubleLinkedList<int> L2;
	L2.insertFirst(1);
	L2.insertFirst(2);
	L2.insertFirst(3);
	L2.insertFirst(4);

    L1.print(); 
    cout <<endl;
	L1.swap(1,0);
	L1.print();
    cout <<endl;

    L2.print();
    cout <<endl;
	L2.swap(0,1);
	L2.print();
    cout <<endl;

	return 0;
}

