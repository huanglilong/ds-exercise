#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include <algorithm>
#include <iostream>

using namespace std;

// binary search tree class

// binary search tree node element need compare operation
template <typename Comparable>
class BinarySearchTree
{
public:
    // constructor
    BinarySearchTree() : root{ nullptr }
    {

    }

    // copy constructor
    BinarySearchTree( const BinarySearchTree & rhs ) : root{ nullptr }
    {
        root = clone( rhs.root );   // copy
    }

    // move constructor 
    BinarySearchTree( BinarySearchTree && rhs) : root{ rhs.root}
    {
        rhs.root = nullptr;         // must
    }

    // destructor for the tree
    ~BinarySearchTree()
    {
        makeEmpty();
    }

    // copy assignment
    BinarySearchTree & operator=(const BinarySearchTree &rhs)
    {
        BinarySearchTree copy = rhs;    // copy constructor
        std::swap(*this, copy);         // move
        return *this;
    }

    // find the smallest item in the tree 
    const Comparable & findMin( ) const 
    {
        // if(isEmpty())
        // {
        //     return;     // empty tree
        // }
        // call private function
        return findMin(root)->element;
    }

    const Comparable & findMax( ) const 
    {
        // if(isEmpty())
        // {
        //     return;
        // }
        return findMax(root)->element;
    }

    // why using two same member function ?
    // implement independent with interface; recusive
    // returns true if x is found in the tree
    bool contains( const Comparable &x) const 
    {
        return contains(x, root);
    }

    bool isEmpty() const 
    {
        return root == nullptr;
    }

    void printTree(ostream &out = cout) const 
    {
        if(isEmpty())
        {
            out << "empty tree" << endl;
        }
        else 
        {
            printTree(root, out);
        }
    }

    void makeEmpty()
    {
        makeEmpty(root);
    }

    void insert( const Comparable &x)
    {
        insert(x, root);
    }

    void insert(Comparable && x)
    {
        // std::move(x): convert x into rvalue
        insert(std::move(x), root); // insert(x, root) is ok here, but not recommand
    }

    void remove(const Comparable & x)
    {
        remove(x, root);
    }

private:
    // node structure
    struct BinaryNode
    {
        Comparable element;
        BinaryNode *left;
        BinaryNode *right;

        // copy consturctor
        BinaryNode(const Comparable &x, BinaryNode *l, BinaryNode *r) :
        element{ x }, left{ l }, right{ r }
        {

        }

        // move constructor 
        BinaryNode( Comparable && x, BinaryNode *l, BinaryNode *r) :
        element{ std::move(x) }, left{ l }, right{ r }
        {
            
        }
    };

    BinaryNode *root;

    // BinaryNode * & t, t is BinaryNode * type reference
    void insert(const Comparable &x , BinaryNode * & t)
    {
        if( t == nullptr)
        {
            t = new BinaryNode(x, nullptr, nullptr);    // empty sub tree
        }
        else if( x < t->element)
        {
            insert(x, t->left);
        }
        else if( x > t->element)
        {
            insert(x, t->right);
        }
        else    // duplicate, do nothing 
        {

        }
    }

    void insert(Comparable &&x, BinaryNode * & t)
    {
        if( t == nullptr )
        {
            t = new BinaryNode(std::move(x), nullptr, nullptr);    // move constructor
        }
        else if(x < t->element )
        {
            // std::move(x) must ?
            insert(std::move(x), t->left);
        }
        else if(x > t->element)
        {
            insert(std::move(x), t->right);
        }
        else    // duplicate, do nothing 
        {

        }
    }

    void remove( const Comparable & x, BinaryNode * & t)
    {
        if( t == nullptr )
        {
            return;     // not found
        }
        else if( x < t->element)
        {
            remove(x, t->left);
        }
        else if( x > t->element)
        {
            remove(x, t->right);
        }
        else if(t->left != nullptr && t->right != nullptr)  // have two children
        {
            t->element = findMin(t->right)->element;        // findMin always return minimun node from the tree
            remove(t->element, t->right);
        }
        else 
        {
            // remove function alwalys result in removing leaf node
            BinaryNode *old = t;
            t = (t->left != nullptr) ? t->left : t->right;
            delete old;
        }
    }

    // recursive method
    BinaryNode * findMin( BinaryNode *t) const
    {
        if( t == nullptr )
        {
            return nullptr;     // empty tree
        }
        if( t->left == nullptr)
        {
            return t;
        }
        else 
        {
            return findMin(t->left);
        }
        /*
        while( t->left != nullptr )
        {
            t = t->left;
        }
        return t;
        */
    }

    // nonrecursive method
    BinaryNode * findMax( BinaryNode *t) const 
    {
        if( t == nullptr )
        {
            return nullptr;
        }
        while(t->right != nullptr)   // right leaf node
        {
            t = t->right;
        }
        return t;
    }

    bool contains(const Comparable &x, BinaryNode *t) const 
    {
        if(t == nullptr)
        {
            return false;
        }
        if( x < t->element )
        {
            contains(x, t->left);
        }
        else if( x > t->element )
        {
            contains(x, t->right);
        }
        return true;
    }

    void makeEmpty( BinaryNode * & t)
    {
        if( t != nullptr)
        {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
        }
        t = nullptr;    // not need ?
    }

    void printTree( BinaryNode *t, ostream &out ) const 
    {
        if( t == nullptr )
        {
            return;
        }
        printTree(t->left, out);
        out << t-> element << endl;
        printTree(t->right, out);

    }

    BinaryNode * clone( BinaryNode *t) const 
    {
        if( t == nullptr )
        {
            return nullptr;
        }
        else 
        {
            return new BinaryNode(t->element, clone(t->left), clone(t->right));
        }

    }
};

#endif