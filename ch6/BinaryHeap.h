#ifndef BINARY_HEAP_H
#define BINARY_HEAP_H

#include <algorithm>
#include <vector>
#include <iostream>

using namespace std;

template <typename Comparable>
class BinaryHeap
{
public:
    explicit BinaryHeap( int capacity = 100 )
    : array( capacity + 1 ), currentSize{ 0 }
    {

    }

    explicit BinaryHeap( const vector<Comparable> & items )
    : array( items.size() + 10 ), currentSize( items.size() )
    {
        for(int i=0; i < items.size(); ++i)
        {
            array[i+1] = items[i];      // array[0] for special use
        }
        buildHeap();
    }

    bool isEmpty() const 
    {
        return currentSize == 0;
    }

    const Comparable & findMin() const 
    {
        // throw exception
        return array[1];
    }

    void insert( const Comparable &x )
    {
        // no enough space 
        if( currentSize == array( ) - 1 )
        {
            array.resize( array.size() * 2 );
        }

        int hole = ++currentSize;               // new hole position
        Comparable copy = x;

        array[0] = std::move( copy );
        for(; x < array[hole/2]; hole /=2 )
        {
            // http://www.cplusplus.com/reference/utility/move/?kw=move
            array[hole] = std::move( array[hole/2] );        // parent node down
        }
        array[hole] = std::move( array[0] );
    }

    void insert( Comparable && x )
    {
        if( currentSize == array.size() -1 )
        {
            array.resize( array.size() * 2 );
        }

        int hole = ++currentSize;
        //array[0] = std::move( x );  
        for(; hole > 1 && x < array[hole/2]; hole /= 2 )
        {
            array[hole] = std::move( array[hole/2] );
        }

        // hole = 1 or x >= array[hole/2]
        array[hole] = std::move( x );
    }

    void deleteMin( )
    {
        array[1] = std::move( array[currentSize--] );
        percolateDown( 1 );
    }

    void deleteMin( Comparable & x )
    {
        x = std::move( array[1] );
        array[1] = std::move( array[currentSize--] );
        percolateDown( 1 );
    }

    void makeEmpty()
    {
        currentSize = 0;
    }

private:
    int                 currentSize;
    vector<Comparable>  array;

    void buildHeap( )
    {
        for( int i = currentSize / 2; i > 0; --i)
        {
            // currentSize / 2 is last right parant node
            // from right to left and down to up
            percolateDown( i );
        }
    }

    void percolateDown( int hole )
    {
        int child;
        Comparable tmp = std::move( array[hole] );

        for( ; hole * 2 <= currentSize; hole = child )
        {
            child = hole * 2;
            if( child != currentSize && array[child + 1] < array[child])
            {
                child++;    // right child node
            }
            if( array[child] < tmp )
            {
                array[hole] = std::move( array[child] );
            }
            else        // correct position
            {
                break;
            }
        }
        // leaf node or break from for statement
        array[hole] = std::move( tmp );
    }
};

#endif