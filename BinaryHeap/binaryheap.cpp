#include <iostream>
#include <sstream>
#include <string>
#include "binaryheap.h"
using namespace std;


int main( )
{
    int minItem = 100;  
    int maxItem = 999;
    BinaryHeap<string> h;
    string str = "hello";
    int i = 37;
    string x;

    for( i = 37; i != 0; i = ( i + 37 ) % maxItem ){
        ostringstream sout;
        sout << "hello" << i;
        if( i >= minItem ){
            string s = sout.str( );
            h.insert( s );
        }
    }
    for( i = minItem; i < maxItem; ++i ){
        ostringstream sout;
        sout << "hello" << i;
        
        h.deleteMin( x );

        if( x != sout.str( ) )
            cout << " " << i << endl;
    }

    return 0;
}