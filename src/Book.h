#ifndef BOOK_H
#define BOOK_H
#include <string>
#include <functional>
using namespace std;

class Book {
public:
    string _title;
    string _author;
    string _genre;
    int _year;

    Book(string title="", string author="", string genre="", int year=0) :
        _title(move(title)), _author(move(author)), _genre(move(genre)), _year(year) {}
    void print() const;
};

#endif //BOOK_H
