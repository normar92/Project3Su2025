#include <iostream>
#include "Book.h"
#include "RBTree.h"
using namespace  std;

int main() {
    RBTree tree;
    tree.insert(Book("A Book", "John Smith", "Educational", 1800));
    tree.insert(Book("B Book", "Mary White", "Dystopian", 1900));
    tree.insert(Book("Novel", "Benjamin Jones", "Dystopian", 2000));
    tree.insert(Book("Comic", "Charles Grant", "Comedy", 2020));

    cout << "Sorted by Title (default):" << endl;
    tree.inOrder();

    cout << "================================" << endl << endl;;

    tree.setSort(2);
    cout << "Sorted by Author:" << endl;
    tree.inOrder();

    cout << "================================" << endl << endl;;

    tree.setSort(3);
    cout << "Books sorted by Genre:" << endl;
    tree.inOrder();

    cout << "================================" << endl << endl;;

    tree.setSort(4);
    cout << "Sorted by Year:" << endl;
    tree.inOrder();

    cout << "================================" << endl << endl;

    cout << "Key word search: \'oo\'" << endl;
    RBTree res = tree.search("oo");
    res.inOrder();

    cout << "================================" << endl << endl;;

    res.setSort(3);
    cout << "Key word search result, Sorted by Genre:" << endl;
    res.inOrder();

    return 0;
}