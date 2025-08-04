#include <iostream>
#include "Book.h"
using namespace std;

void Book::print() const {
    cout << "Title: " << _title << endl;
    cout << "Author: " << _author << endl;
    cout << "Genre: " << _genre << endl;
    cout << "Year: " << _year << endl;
    cout << endl;
}