/*
 * Author		: huang li long <huanglilongwk@gmail.com>
 * Time			: 2016/10/08
*/

/* problems
3.11 Assume that a singly linked list is implemented with a header node, but no tail
node, and that it maintains only a pointer to the header node. Write a class that
includes methods to
a. return the size of the linked list
b. print the linked list
c. test if a value x is contained in the linked list
d. add a value x if it is not already contained in the linked list
e. remove a value x if it is contained in the linked list
*/

#include "s_list.h"

int main()
{
    SList<int> sl;
    int a[5];
    for(int i=0; i<5; ++i)
    {
        a[i] = i;
        sl.add(a[i]);
    }
    sl.print();
    sl.remove(4);
    sl.print();
}