#include "BinaryHeap.h"
#include <iostream>

int main()
{
    int min = 0;
    vector<int> items;
    for(int i=5; i < 10; ++i)
    {
        items.push_back(i);
    }
    
    BinaryHeap<int> heap(items);
    
    min = heap.findMin();
    cout << "min value is: " << min << endl;

    heap.insert(2);
    min = heap.findMin();
    cout << "min value is: " << min << endl;

    heap.deleteMin();
    heap.deleteMin();
    min = heap.findMin();
    cout << "min value is: " << min << endl;

}
