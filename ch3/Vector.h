#ifndef VECTOR_H
#define VECTOR_H

#include <algorithm>
#include <iostream>

/* Notes:
 * 1. lvalue: program can obtain it's address; left side of an assignment statement
 * 2. rvalue: appear on the right-hand side of assignment statement, for move
 * 3. binding an rvalue to an rvalue reference results in the value being stored in a location
 *    whose address can be taken
*/
template <typename Object>
class Vector
{
public:
    explicit Vector(int initSize = 0)  // default constructor 
    : theSize{ initSize }, theCapacity{ initSize + SPACE_CAPACITY }
    { 
        objects = new Object[theCapacity];
    }

    Vector(const Vector &rhs)          // copy constructor
    : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ nullptr }
    {
        objects = new Object[theCapacity]; // deep copy 
        for(int k=0; k < theSize; k++)
        {
            objects[k] = rhs.objects[k];
        }
    }

    Vector & operator= (const Vector &rhs)
    {
        Vector copy = rhs;
        std::swap(*this, copy);         // by moving
        return *this;
    }

    ~Vector()
    {
        delete [] objects;
    }

    Vector(Vector &&rhs)
    : theSize{ rhs.theSize }, theCapacity{ rhs.theCapacity }, objects{ rhs.objects }
    {
        rhs.objects = nullptr;
        rhs.theSize = 0;
        rhs.theCapacity = 0;
    }

    Vector & operator= (Vector &&rhs)
    {
        std::swap( theSize, rhs.theSize );
        std::swap( theCapacity, rhs.theCapacity );
        std::swap( objects, rhs.objects );

        return *this;
    }

    bool empty() const 
    {
        return size() == 0;
    }

    int size() const 
    {
        return theSize;
    }

    int capacity() const 
    {
        return theCapacity;
    }

    Object & operator[] (int index)
    {
        return objects[index];
    }

    const Object & operator[](int index) const 
    {
        return objects[index];
    }

    void resize(int newSize)
    {
        if(newSize > theCapacity)
        {
            reserve(newSize * 2 + 1);
        }
        theSize = newSize;
    }

    void reserve(int newCapacity)
    {
        if(newCapacity < theSize)
        {
            return;
        }

        Object *newArray = new Object[newCapacity];     // allocate new space 
        for(int k=0; k < theSize; k++)
        {
            newArray[k] = std::move(objects[k]);        // the contents of objects move to newArray, no copy
        }

        theCapacity = newCapacity;
        std::swap(objects, newArray);
        delete [] newArray;
    }

    void push_back( const Object &x)
    {
        if(theSize == theCapacity)
        {
            reserve(2 * theCapacity + 1);
        }

        objects[ theSize++ ] = x;
    }

    void push_back(Object &&x)
    {
        if(theSize == theCapacity)
        {
            reserve( 2 * theCapacity + 1);
        }

        objects[ theSize++ ] = std::move(x);
    }

    void pop_back()
    {
        if(empty())
        {
            return;
        }
        --theSize;
    }

    const Object & back() const 
    {
        if(empty())
        {
            return;
        }

        return objects[theSize - 1];
    }

    typedef Object * iterator;
    typedef const Object * const_iterator;

    iterator begin()
    {
        return &objects[0];
    }
    const_iterator begin() const
    {
        return &objects[0];
    }

    iterator end()
    {
        return &objects[size()];
    }

    const_iterator end() const 
    {
        return &objects[size()];
    }

    static const int SPACE_CAPACITY = 2;

private:
    int theSize;
    int theCapacity;
    Object *objects;
};

#endif