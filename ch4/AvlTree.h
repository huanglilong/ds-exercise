#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <algorithm>
#include <iostream>

using namespace std;

// Avl tree class 
template <typename Comparable>
class AvlTree
{
public:
    // default constructor
    AvlTree() : root{ nullptr } { }

    // copy constructor
    AvlTree( const AvlTree & rhs ) : root{ nullptr }
    {
        root = clone(rhs.root);     // copy
    }

    // move construtor
    AvlTree( AvlTree &&rhs ) : root{ rhs.root }
    {
        rhs.root = nullptr;
    }

    ~AvlTree()
    {
        makeEmpty();
    }

    // deep copy 
    AvlTree & operator=( const AvlTree & rhs )
    {
        AvlTree copy = rhs;     // copy constructor
        std::swap(*this, copy); // move 
        return *this;
    }

    // move assignment
    AvlTree & operator=( AvlTree && rhs )
    {
        //root = rhs.root;
        //rhs.root = nullptr;
        std::swap( root, rhs.root );
        return *this;
    }

    const Comparable & findMax() const 
    {
        return findMax(root)->element;
    }

    const Comparable & findMin() const 
    {
        return findMin(root)->element;
    }

    bool contains( const Comparable & x ) const
    {
        return contains(x, root);
    }

    bool isEmpty() const
    {
        return root == nullptr;
    }

    void printTree() const 
    {
        if( isEmpty() )
        {
            cout << "empty tree" << endl;
            return;
        }
        printTree( root );
    }

    void makeEmpty()
    {
        makeEmpty( root );
    }

    void insert( const Comparable &x )
    {
        insert(x, root);
    }

    void insert( Comparable && x )
    {
        insert( std::move(x), root );
    }

    void remove( const Comparable & x )
    {
        remove( x, root );
    }

private:
    struct AvlNode
    {
        Comparable  element;
        AvlNode     *left;
        AvlNode     *right;
        int         height;

        AvlNode(const Comparable & e, AvlNode *l, AvlNode *r, int h = 0) :
        element{ e }, left{ l }, right{ r }, height{ h }
        {

        }

        AvlNode(Comparable && e, AvlNode *l, AvlNode *r, int h = 0) :
        element{ std::move(e) }, left{ l }, right{ r }, height{ h }
        {

        }
    };
    
    AvlNode *root;

    void insert(const Comparable &x, AvlNode * & t)
    {
        if( t == nullptr )
        {
            t = new AvlNode( x, nullptr, nullptr );   // new node, always insert leaf node
        }
        if( x < t->element )
        {
            insert( x, t->left );
        }
        else if( x > t->element )
        {
            insert( x, t->right );
        }
        else 
        {
            // duplicate, do nothing
        }

        // balance tree
        balance( t );
    }

    void insert( Comparable && x, AvlNode * & t)
    {
        if( t == nullptr )
        {
            t = new AvlNode( std::move(x), nullptr, nullptr );
        }
        if( x < t->element )
        {
            insert( std::move(x), t->left );
        }
        else if( x > t->element )
        {
            insert(std::move(x), t->right);
        }

        balance( t ); 
    }

    void remove( const Comparable & x, AvlNode * & t )
    {
        if( t == nullptr )
        {
            return;
        }
        if( x < t->element )
        {
            remove( x, t->left );
        }
        else if( x > t->element )
        {
            remove( x, t->right );
        }
        else if( t->left != nullptr && t->right != nullptr )    // two children node
        {
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else    // one or no child node
        {
            AvlNode *old = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete old;
        }

        balance( t ); 
    }

    static const int ALLOWED_IMBALANCE = 1;
    
    void balance( AvlNode * & t)
    {
        if( t == nullptr )
        {
            return;
        }
        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE) // unbalance
        {
            if( height( t->left->left ) >= height( t->left->right ) )
            {
                // left - left 
                rotateWithLeftChild( t );
            }
            else 
            {
                // left - right
                doubleWithLeftChild( t );
            }
        }
        if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE )
        {
            if( height( t->right->left ) > height( t->right->right) )
            {
                // right - left 
                doubleWithRightChild( t );
            }
            else 
            {
                rotateWithRightChild( t );
            }
        }

        // update height info
        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }

    AvlNode * findMin( AvlNode * t) const 
    {
        if( t == nullptr )
        {
            return nullptr;
        }
        if( t->left != nullptr )
        {
            return findMin( t->left );
        }
        // t->left == nullptr
        return t;
    }

    AvlNode * findMax( AvlNode * t ) const
    {
        if( t == nullptr )
        {
            return nullptr;
        }
        while( t->right != nullptr )
        {
            t = t->right;
        }
        return t;
    }

    bool contains( const Comparable & x, AvlNode * t) const 
    {
        if( t == nullptr )
        {
            return false;
        }
        if( x < t->element )
        {
            contains( x, t->left );
        }
        else if( x > t->element )
        {
            contains( x, t->right );
        }
        else 
        {
            return true;
        }
    }

    void makeEmpty( AvlNode * & t)
    {
        if( t != nullptr)
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr; // pointer nothing
    }

    void printTree( AvlNode *t ) const 
    {
        if( t != nullptr )
        {
            printTree( t->left );
            cout << t->element << endl;
            printTree( t->right );
        }
    }

    AvlNode * clone( AvlNode *t ) const 
    {
        if( t == nullptr )
        {
            return nullptr;
        }
        else 
        {
            return new AvlNode( t->element, clone( t->left ), clone( t->right ));
        }
    }

    int height( AvlNode * t ) const 
    {
        return t == nullptr ? -1 : t->height;
    } 

    int max( int lhs, int rhs ) const 
    {
        return lhs > rhs ? lhs : rhs;
    }

    void rotateWithLeftChild( AvlNode * & k2 )
    {
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;

        // update height info 
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;    // subtree root node
    }

    void rotateWithRightChild( AvlNode * & k1 )
    {
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;

        // update height info 
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( k1->height, height( k2->right ) ) + 1;
        k1 = k2;
    }

    void doubleWithLeftChild( AvlNode * & k3 )
    {
        rotateWithRightChild( k3->left ); // k1 = k3->left 
        rotateWithLeftChild( k3 );
    }

    void doubleWithRightChild( AvlNode * & k1 )
    {
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }
};

#endif