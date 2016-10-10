#ifndef LIST_H
#define LIST_H

#include <algorithm>

template <typename Object>
class List
{
private:
    // the basic doubly linked list Node 
    // nested inside of list, can be public
    // because the Node is just for List class using, so we make it private
    struct Node
    {
        Object data;
        Node *prev;
        Node *next;

        Node(const Object &d = Object{}, Node *p = nullptr, Node *n = nullptr)
        : data{ d }, prev{ p }, next{ n }
        {

        }

        Node(Object && d, Node *p = nullptr, Node *n = nullptr)
        : data{ std::move(d) }, prev{ p }, next{ n }
        {

        }
    };      // ; --> decarlation

public:
    class const_iterator
    {
    public:
        // public constructor for const_iterator
        const_iterator() : current{ nullptr }
        {

        }

        // return the object stored at the current position
        // for const_iterator, this is an accessor with a const reference return type
        const Object & operator* () const
        {
            return retrieve();
        }

        const_iterator & operator++ ()      // ++iterator
        {
            current = current->next;
            return *this;
        }

        const_iterator operator++ (int)     // iterator++
        {
            const_iterator old = *this;
            ++(*this);                      // call operator++()
            return old;
        }

        const_iterator & operator-- ()      // --iterator
        {
            current = current->prev;
            return *this;
        }

        const_iterator & operator-- (int)   // iterator--
        {
            const_iterator old = *this;
            --(*this);                      // call operator--()
            return old;
        }

        // point to same object
        bool operator== ( const const_iterator &rhs ) const 
        {
            return current == rhs.current;
        }

        bool operator!= (const const_iterator &rhs ) const 
        {
            return !(*this == rhs);     // call operator==()
        }

    protected:
        Node *current;
        
        Object & retrieve() const 
        {
            return current->data;
        }

        const_iterator(Node *p) : current{ p }
        {

        }

        friend class List<Object>;
    };

    class iterator : public const_iterator
    {
      public:

        // Public constructor for iterator.
        // Calls the base-class constructor.
        // Must be provided because the private constructor
        // is written; otherwise zero-parameter constructor
        // would be disabled.
        iterator( )
        {

        }

        Object & operator* ( )
        { 
            return const_iterator::retrieve( ); 
        }

        // Return the object stored at the current position.
        // For iterator, there is an accessor with a
        // const reference return type and a mutator with
        // a reference return type. The accessor is shown first.
        const Object & operator* ( ) const
        { 
              return const_iterator::operator*( ); 
        }
        
        iterator & operator++ ( )
        {
            this->current = this->current->next;     // base class protected member
            return *this;
        }

        iterator operator++ ( int )
        {
            iterator old = *this;
            ++( *this );
            return old;
        }

        iterator & operator-- ( )
        {
            this->current = this->current->prev;
            return *this;
        }

        iterator operator-- ( int )
        {
            iterator old = *this;
            --( *this );
            return old;
        }

      protected:
        // Protected constructor for iterator.
        // Expects the current position.
        iterator( Node *p ) : const_iterator{ p }
        {

        }

        friend class List<Object>;
    };

    public:
        List()
        {
            init();
        }

        ~List()
        {
            clear();
            delete head;
            delete tail;
        }

        List(const List &rhs)
        {
            init();
            for(auto &x : rhs)
            {
                push_back(x);
            }
        }

        List & operator= (const List &rhs)
        {
            List copy = rhs;
            std::swap(*this, copy);
            return *this;
        }

        List(List &&rhs)    // constructor for rvalue parameter
        : theSize{ rhs.theSize }, head{ rhs.head }, tail{ rhs.tail }
        {
            rhs.theSize = 0;
            rhs.head = nullptr;
            rhs.tail = nullptr;
            // rhs will be delete automatically
        }

        // move assignment
        List & operator= (List &&rhs)
        {
            std::swap( theSize, rhs.theSize );
            std::swap( head, rhs.head );
            std::swap( tail, rhs.tail );
            
            return *this;
        }

        iterator begin()
        {
            return iterator(head->next);
        }

        const_iterator begin() const 
        {
            return const_iterator(head->next);
        }

        iterator end( )
        { 
            return iterator( tail ); 
        }

        const_iterator end( ) const
        { 
            return const_iterator( tail ); 
        }

        // exercise 3.3
        iterator find(iterator start, iterator end, const Object &x)
        {
            for(auto itr = start; itr != end; ++itr)
            {
                if(itr.current->data == x)
                    return itr;
            }
        }
        int size() const 
        {
            return theSize;
        }

        bool empty() const 
        {
            return size() == 0;
        }

        void clear()
        {
            while(!empty())
            {
                pop_front();
            }
        }

        // double linker basic operations
        Object & front()
        {
            return *begin();
        }

        const Object & front() const 
        {
            return *begin();
        }

        Object & back( )
        { 
            return *--end( ); 
        }

        const Object & back( ) const
        { 
            return *--end( ); 
        }

        void push_front( const Object &x)
        {
            insert(begin(), x);
        }

        void push_back( const Object &x)
        {
            insert(end(), x);
        }

        void push_front( Object && x )
        { 
            insert( begin( ), std::move( x ) ); 
        }

        void push_back( Object && x )
        { 
            insert( end( ), std::move( x ) );
        }

        void pop_front()
        {
            erase(begin());
        }

        void pop_back()
        {
            erase(--end());
        }

        // insert x before itr 
        iterator insert(iterator itr, const Object &x)
        {
            Node *p = itr.current;
            ++theSize;
            return iterator(p->prev = p->prev->next = new Node{ x, p->prev, p });
        }

        // Insert x before itr.
        iterator insert( iterator itr, Object && x )
        {
            Node *p = itr.current;
            ++theSize;
            return iterator( p->prev = p->prev->next = new Node{ std::move( x ), p->prev, p } );
        }

        // erase item at itr 
        iterator erase(iterator itr)
        {
            Node *p = itr.current;
            iterator retVal(p->next);       // protected constructor
            p->prev->next = p->next;
            p->next->prev = p->prev;
            delete p;
            --theSize;

            return retVal;                  // next element

        }

        iterator erase( iterator from, iterator to )
        {
            for( iterator itr = from; itr != to; )
                itr = erase( itr );

            return to;
        }

private:
    int theSize;
    Node *head;
    Node *tail;

    void init( )
    {
        theSize = 0;
        head = new Node;
        tail = new Node;
        head->next = tail;
        tail->prev = head;
    }
};

#endif