#include <algorithm>
#include <iostream>







template <typename Object>
class Vector{
public:
    explicit Vector(int initSize = 0) : theSize{initSize},theCapacity{initSize + SPARE_CAPACITY}{
        objects = new Object[theCapacity];
    }

    Vector(const Vector &rhs) : theSize{rhs.theSize},theCapacity{rhs.theCapacity}, objects{nullptr}{
        objects = new Object[theCapacity];
        for (int k = 0; k < theSize; ++k)
            objects[k] = rhs.objects[k];
    }

    Vector &operator=(const Vector &rhs){
        Vector copy = rhs;
        std::swap(*this, copy);
        return *this;
    }

    ~Vector(){
        delete[] objects;
    }

    Vector(Vector &&rhs) : theSize{rhs.theSize},theCapacity{rhs.theCapacity}, objects{rhs.objects}{
        rhs.objects = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
    }

    void resize(int newSize){
        if (newSize > theCapacity)
            reserve(newSize * 2);
        theSize = newSize;
    }

    void reserve(int newCapacity){
        if (newCapacity < theSize)
            return;

        Object *newArray = new Object[newCapacity];
        for (int k = 0; k < theSize; ++k)
            newArray[k] = std::move(objects[k]);

        theCapacity = newCapacity;
        std::swap(objects, newArray);
        delete[] newArray;
    }

    bool empty() const{return size() == 0;}
    int size() const{return theSize;}
    int capacity() const{return theCapacity;}

    void push_back(const Object &x){
        if (theSize == theCapacity)
            reserve(2 * theCapacity + 1);
        objects[theSize++] = x;
    }

    void push_back(Object &&x){
        if (theSize == theCapacity)
            reserve(2 * theCapacity + 1);
        objects[theSize++] = std::move(x);
    }

    void pop_back(){
        --theSize;
    }

    const Object &back() const{
        return objects[theSize - 1];
    }

    typedef Object *iterator;
    typedef const Object *const_iterator;


    iterator begin( ) { 
        return iterator(*this ,&objects[ 0 ]); 
    }
    const_iterator begin( ) const { 
        return const_iterator(*this,&objects[ 0 ]); 
    }
    iterator end( ) { 
        return iterator(*this, &objects[ size( ) ]); 
    }
    const_iterator end( ) const { 
        return const_iterator(*this, &objects[ size( ) ]);
    }



    static const int SPARE_CAPACITY = 16;

private:
    int theSize;
    int theCapacity;
    Object *objects;




    class const_iterator {
    public:
        //const_iterator( ) : current( NULL )
        // { } Forzar el uso del constructor seguro
        const Object & operator* () const { 
            return retrieve( ); 
        }
        const_iterator & operator++ () {
            current++;
            return *this;
        }
        const_iterator operator++ ( int ) {
            const_iterator old = *this;
            ++( *this );
            return old;
        }
        bool operator== ( const const_iterator & rhs ) const { 
            return current == rhs.current; 
        }
        bool operator!= ( const const_iterator & rhs ) const { 
            return !( *this == rhs ); 
        }
    protected:
        Object *current;
        const Vector<Object> *theVect;
        
        Object & retrieve() const{
            assertIsValid();
            return *current;
        }
        const_iterator( const Vector<Object> & vect, Object *p ) :theVect (& vect), current( p ){}
        void assertIsValid() const {
            if (theVect == NULL || current == NULL )
            throw IteratorOutOfBoundsException();
        }
        friend class Vector<Object>;
    };


    class iterator : public const_iterator {
    public:
        //iterator( )
        // { } Forzar el uso del constructor seguro
        
        Object & operator* () { 
            return retrieve(); 
        }
        const Object & operator* () const{ 
            return const_iterator::operator*(); 
        }
        iterator & operator++ () {
            cout<<"old "<<*current<<" ";
            current++;
            cout<<" new "<<*current<<" ";
            return *this;
        }
        iterator operator++ ( int ) {
            iterator old = *this;
            ++( *this );
            return old;
        }
    protected:
        iterator(const Vector<Object> & vect, Object *p )
        : const_iterator(vect, p ){}
        
        friend class Vector<Object>;
    };




};

int main(){
   
    return 0;
}