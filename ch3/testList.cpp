#include "List.h"
#include <iostream>

using namespace std;

int main()
{
    List<int> int_list;
    int a = 1;
    int b = 2;
    int_list.push_front(a);
    int_list.push_front(b);
    cout << "size: " << int_list.size() << endl;
    cout << "back element: " << int_list.back() << endl;

    auto itr = int_list.find(int_list.begin(), int_list.end(), 2);
    cout << "value: " << *itr << endl;
}