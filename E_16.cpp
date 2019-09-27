#include <iostream>
#include "doublelinkedlist.h"
using namespace std;

int main(){
    doubleLinkedList<int> L;
	L.insertFirst(1);
	L.insertFirst(2);
	L.insertFirst(3);
	L.insertFirst(4);

	doubleLinkedList<int>::reverse_iterator it = L.rbegin();
	while( it != L.rend() )
		cout << *it++ << endl;
	return 0;
}
