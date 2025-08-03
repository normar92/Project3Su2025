#include <iostream>
#include "hashTable.h"

int main() {
    // Load books from CSV
    loadBooks("../kindle_data-v2.csv");
    //std::cout<<"books loaded" << std::endl;

    // Query example
    std::string queryASIN = "B00TZE87S4";
    Book* found = searchBook(queryASIN);

    if (found) {
        std::cout << "\nTitle: " << found->title << "\n"
                  << "Author: " << found->author << "\n"
                  << "Price: $" << found->price << "\n";
    } else {
        std::cout << "Book not found.\n";
    }

    return 0;
}
