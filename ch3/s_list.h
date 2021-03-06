#ifndef S_LIST_H
#define S_LIST_H

#include <iostream>
#include <algorithm>

template <typename Object>
class SList
{
private:
    struct Node 
    {
        Object data;
        Node *next;

        Node(const Object &d = Object{}, Node *n = nullptr)
        : data{ d }, next{ n }
        {

        }

        Node(const Object &&d, Node *n = nullptr)
        : data{ std::move(d) }, next{ n }
        {

        }
    };

public:
    SList()
    {
        theSize = 0;
        head = new Node;
        head->next = nullptr;
    }

    ~SList()
    {
        for(auto ptr = head->next; ptr != nullptr;)
        {
            delete ptr;
            ptr = ptr->next;
        }
        delete head;
        /*
        auto ptr = head->next;
        while(ptr != nullptr)
        {
            delete ptr;
            ptr = ptr->next;
        }
        delete head;
        */
    }

    int size() const 
    {
        return theSize;
    }

    void print() const 
    {
        std::cout << "list print: " << std::endl;
        for(auto ptr = head->next; ptr != nullptr;)
        {
            std::cout << ptr->data << " ";
            ptr = ptr->next;
        }
        std::cout << std::endl;
    }

    bool contain(const Object &x) const
    {
        for(auto ptr = head->next; ptr != nullptr;)
        {
            if(ptr->data == x)
            {
                return true;
            }
            ptr = ptr->next;
        }
        return false;
    }

    void add(const Object &x)
    {
        auto ptr = head->next;
        auto prev = head;

        // if(head->next == nullptr)   // empty list
        // {
        //     Node *p = new Node;
        //     p->data = x;
        //     p->next = head->next;
        //     head->next = p;
        //     theSize++;
        //     return;
        // }

        while(ptr != nullptr)
        {
            if(ptr->data < x)       // next position
            {
                prev = prev->next;
                ptr = ptr->next;
            }
            else if(ptr->data > x)
            {
                Node *p = new Node;
                p->data = x;
                p->next = prev->next;
                prev->next = p;
                theSize++;
                return;
            }
            else
            {
                return;
            }
        }

        if(ptr == nullptr)      // empty or x greator than all element in the list
        {
            Node *p = new Node;
            p->data = x;
            p->next = prev->next;
            prev->next = p;
            theSize++;
        }
    }

    void remove(const Object &x)
    {
        auto prev = head;
        
        for(auto ptr = head->next; ptr != nullptr;)
        {
            if(ptr->data == x)
            {
                prev->next = ptr->next;
                theSize--;
                return;
            }
            prev = prev->next;
            ptr = ptr->next;
        }
    }

private:
    int theSize;       // list's size
    Node *head;
};

#endif