#include <iostream>
#include <list>
using namespace std;

int main() {
    int i,j, n, m, mPrime, numLeft;
    list <int > L;
    list<int>::iterator iter;
    //Inicializacion
    cout << "ingrese N (# de personas) y M (# de pases antes de la eliminacion)";
    cin >> n >> m;
    numLeft = n;
    mPrime = m % n;
    for (int I =1 ; I <= n; i++)
        L.push_back(i);
    iter = L.begin();
    // Pasar la papa
    for (int I = 0; I < n; i++) {
        mPrime = mPrime % numLeft;
        if (mPrime <= numLeft/2) // pasar adelante
            for (j = 0; j < mPrime; j++) {
                iter++;
                if (iter == L.end())
                    iter = L.begin();
        }
        else // pasar hacia atrás
            for (j = 0; j < mPrime; j++) {
                if (iter == L.begin())
                    iter = --L.end();
                else
                    iter--;
            }
        cout<<*iter<<" ";
        iter= L.erase(iter);
        if (iter == L.end())
        iter = L.begin();
    }
    cout<<endl;
    return 0;
}