/*
 * Author		: huang li long <huanglilongwk@outlook.com>
 * Time			: 2016/10/08
*/

/* problems
3.4 Given two sorted lists, L1 and L2, write a procedure to compute L1 ∩ L2 using only
    the basic list operations.
3.5 Given two sorted lists, L1 and L2, write a procedure to compute L1 ∪ L2 using only
    the basic list operations.
*/

#include <iostream>
#include <list>

using namespace std;

list<int> intersections_list(const list<int> &l1, const list<int> &l2);
list<int> intersections_list2(const list<int> &l1, const list<int> &l2);
list<int> unions_list(list<int> const &l1, list<int> const &l2);
list<int> unions_list2(list<int> const &l1, list<int> const &l2);
void list_print(list<int> &lt);

int main()
{
    int size1, size2;
    list<int> l1;
    list<int> l2;

    cout << "enter size of list 1: ";
    cin >> size1;

    cout << "enter size of list 2: ";
    cin >> size2;

    cout << "enter sorted list 1: ";
    for(int i = 0; i < size1; i++)
    {
        int data;
        cin >> data;
        l1.push_back(data);
    }

    cout << "enter sorted list 2: ";
    for(int i = 0; i < size2; i++)
    {
        int data;
        cin >> data;
        l2.push_back(data);
    }

    // exercise 3.4
    auto l3 = intersections_list2(l1, l2);
    cout << "intersection list size: " << l3.size() << endl;
    list_print(l3);

    // exercise 3.5
    auto l4 = unions_list2(l1, l2);
    cout << "union list size: " << l4.size() << endl;
    list_print(l4);

}

// exercise 3.4
list<int> intersections_list(const list<int> &l1, const list<int> &l2)
{
    list<int> l3;
    auto itr2 = l2.begin();

    for(auto itr1 = l1.begin(); itr1 != l1.end(); ++itr1)
    {
        for(; itr2 != l2.end(); ++itr2)
        {
            if(*itr1 == *itr2)
            {
                l3.push_back(*itr1);
                break;                  // next
            }
            if(*itr1 < *itr2)
            {
                break;
            }
        }
    }
    return l3;
}

list<int> intersections_list2(const list<int> &l1, const list<int> &l2)
{
    list<int> retlist;
    auto itr1 = l1.begin();
    auto itr2 = l2.begin();
    while(itr1 != l1.end() && itr2 != l2.end()) 
    {
        if(*itr1 < *itr2)
        {
            ++itr1;
        }
        else if(*itr1 > *itr2)
        {
            ++itr2;
        }
        else 
        {
            retlist.push_back(*itr1);
            ++itr1;
            ++itr2;
        }
    }
    return retlist;
}

// exercise 3.5
list<int> unions_list(list<int> const &l1, list<int> const &l2)
{
    list<int> l3 = l2;
    auto itr2 = l3.begin();

    for(auto itr1 = l1.begin(); itr1 != l1.end(); ++itr1)
    {
        for(; itr2 != l3.end(); ++itr2)
        {
            if(*itr1 < *itr2)           // push before it2
            {
                l3.insert(itr2, *itr1);
                break;
            }
            else if(*itr1 == *itr2)
            {
                break;
            }
        }
        if(itr2 == l3.end())            // list1's element > all element from list2
        {
            l3.push_back(*itr1);
            ++itr2;
        }
    }
    return l3;
}

list<int> unions_list2(list<int> const &l1, list<int> const &l2)
{
    list<int> retlist = l1;
    auto itr1 = retlist.begin();
    auto itr2 = l2.begin();

    while(itr1 != retlist.end() && itr2 != l2.end())
    {
        if(*itr1 < *itr2)
        {
            ++itr1;
        }
        else if(*itr1 > *itr2)
        {
            retlist.insert(itr1, *itr2);
            ++itr2;
        }
        else 
        {
            ++itr1;
            ++itr2;
        }
    }
    if(itr1 == retlist.end())
    {
        for(;itr2 != l2.end(); ++itr2)
        {
            retlist.push_back(*itr2);
        }
    }
    return retlist;
}

void list_print(list<int> &lt)
{
    cout << "print list:" << endl;
    for(auto itr = lt.begin(); itr != lt.end(); ++itr)
    {
        cout << *itr << " ";
    }
    cout << endl;
}