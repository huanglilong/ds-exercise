/*
 * Author		: huang li long <huanglilongwk@gmail.com>
 * Time			: 2016/10/10
*/

#include "BinarySearchTree.h"
#include "AvlTree.h"

int main()
{
    BinarySearchTree<int> tree;
    for(int i=0; i<10; i++)
    {
        tree.insert(i);
    }
    tree.insert(11);
    cout << "max: " << tree.findMax() << endl;
    cout << "min: " << tree.findMin() << endl;

    tree.printTree();

    tree.remove(0);
    tree.remove(11);
    cout << "max: " << tree.findMax() << endl;
    cout << "min: " << tree.findMin() << endl;
    tree.printTree();

    /* AvTree class test */
    cout << "AvlTree class test part:" << endl;
    
    AvlTree<int> avltree;
    for(int i=0; i<10; i++)
    {
        avltree.insert(i);
    }
    avltree.insert(11);
    cout << "max: " << avltree.findMax() << endl;
    cout << "min: " << avltree.findMin() << endl;

    avltree.printTree();

    avltree.remove(0);
    avltree.remove(11);
    cout << "max: " << avltree.findMax() << endl;
    cout << "min: " << avltree.findMin() << endl;
    avltree.printTree();


}