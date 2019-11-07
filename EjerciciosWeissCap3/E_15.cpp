#include <iostream>
#include "listadesordenada.h"
using namespace std;

int main(){
    ListaDesordenada<int> L1;
	L1.insertLast(1);
	L1.insertLast(2);
	L1.insertLast(8);
	L1.insertLast(9);
	
	ListaDesordenada<int> L2;
	L2.insertLast(3);
	L2.insertLast(4);
	L2.insertLast(5);
	L2.insertLast(6);
	L2.insertLast(7);

    L1.splice(1,L2);
    L1.print();
	return 0;
}
