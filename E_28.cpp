
#include<iostream>
#include "listaLibro.h"
using namespace std;

template <typename Object>
class deque {
public:
    deque() { l();}
    void push (Object obj) {l.push_front(obj);}
    Object pop () {Object obj=l.front(); l.pop_front(); return obj;}
    void inject(Object obj) {l.push_back(obj);}
    Object eject() {pop_back(obj);}
private:
    List<Object> l;
};

int main(){
    return 0;
}