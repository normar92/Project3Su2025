//
// Created by nrmma on 8/3/2025.
//

#include <iostream>
#include <limits>
#include "RBTree.h"
#include "hashTable.h"
#include "csvLoader.h"

using namespace std;

void printMenu() {
    cout << "\n===== Kindle Book Manager =====\n";
    cout << "1. Search by ASIN (Hash Table)\n";
    cout << "2. Search by Title (Hash Table, partial match)\n";
    cout << "3. Search by Author (Hash Table, partial match)\n";
    cout << "4. Keyword search (RBTree - title only)\n";
    cout << "5. Print all books (RBTree, sorted)\n";
    cout << "6. Change sorting order (RBTree)\n";
    cout << "0. Exit\n";
    cout << "Select an option: ";
}

int main() {
    RBTree tree;
    loadBooks("../kindle_data-v2.csv", tree);

    int choice;
    do {
        printMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            string asin;
            cout << "Enter ASIN: ";
            getline(cin, asin);
            Book* book = searchBook(asin);
            if (book) book->print();
            else cout << "Book not found.\n";

        } else if (choice == 2) {
            string title;
            cout << "Enter title keyword: ";
            getline(cin, title);
            auto matches = searchByTitle(title);
            if (matches.empty()) cout << "No books found.\n";
            else for (auto* b : matches) b->print();

        } else if (choice == 3) {
            string author;
            cout << "Enter author keyword: ";
            getline(cin, author);
            auto matches = searchByAuthor(author);
            if (matches.empty()) cout << "No books found.\n";
            else for (auto* b : matches) b->print();

        } else if (choice == 4) {
            string keyword;
            cout << "Enter keyword (title): ";
            getline(cin, keyword);
            RBTree result = tree.search(keyword);
            result.inOrder();

        } else if (choice == 5) {
            tree.inOrder();

        } else if (choice == 6) {
            int sortKey;
            cout << "Sort by: 1=Title, 2=Author, 3=Genre, 4=Year: ";
            cin >> sortKey;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            tree.setSort(sortKey);
            cout << "Sorting updated.\n";
        }

    } while (choice != 0);

    cout << "Exiting program.\n";
    return 0;
}
