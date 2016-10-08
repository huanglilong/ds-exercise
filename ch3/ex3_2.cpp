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
list<int> unions_list(list<int> const &l1, list<int> const &l2);
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
    auto l3 = intersections_list(l1, l2);
    cout << "intersection list size: " << l3.size() << endl;
    list_print(l3);

    // exercise 3.5
    auto l4 = unions_list(l1, l2);
    cout << "union list size: " << l4.size() << endl;
    list_print(l4);

}

// exercise 3.4
list<int> intersections_list(const list<int> &l1, const list<int> &l2)
{
    list<int> l3;
    for(auto itr1 = l1.begin(); itr1 != l1.end(); ++itr1)
    {
        for(auto itr2 = l2.begin(); itr2 != l2.end(); ++itr2)
        {
            if(*itr1 == *itr2)
            {
                l3.push_back(*itr1);
            }
        }
    }
    return l3;
}

// exercise 3.5
list<int> unions_list(list<int> const &l1, list<int> const &l2)
{
    list<int> l3 = l2;
    
    for(auto itr1 = l1.begin(); itr1 != l1.end(); ++itr1)
    {
        auto itr2 = l3.begin();
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
        }
    }
    return l3;
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