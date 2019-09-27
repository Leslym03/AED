#include <iostream>
#include "listaLibro.h"
using namespace std;

template <typename Object>
void printLista(List <Object> L, List<int> P) {
    typename List < int > ::const_iterator pIter ;
    typename List < Object >::const_iterator lIter ;
    int inicio = 0;
    lIter = L.begin();
    for (pIter=P.begin(); pIter != P.end() && lIter != L.end(); pIter++) {
        while (inicio < *pIter && lIter != L.end()) {
            inicio++;
            lIter++;
        }
        if (lIter !=L.end())
            cout<<*lIter<< " ";
    }
}


int main(){
    List <int> L;
    L.push_back(0);
    L.push_back(1);
    L.push_back(2);
    L.push_back(3);
    L.push_back(4);
    L.push_back(5);
    L.push_back(6);
    List <int> P;
    P.push_back(1);
    P.push_back(3);
    P.push_back(4);
    P.push_back(6);

    for (List<int> ::iterator b=P.begin();b!=P.end();b++){
        cout<<*b<<" ";
    }
    cout << endl;

    for (List<int> ::iterator b=L.begin();b!=L.end();b++){
        cout<<*b<<" ";
    }
    cout << endl;

    printLista(L,P);
    cout << endl;


	return 0;
}

