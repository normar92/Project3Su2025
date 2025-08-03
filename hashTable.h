//
// Created by nrmma on 8/2/2025.
//

#ifndef HASHTABLE_H
#define HASHTABLE_H
#include <string>
#include <unordered_map>
#include <vector>


// Book structure
struct Book {
    std::string asin;
    std::string title;
    std::string author;
    std::string soldBy;
    std::string imgUrl;
    std::string productURL;
    double stars;
    int reviews;
    double price;
    bool isKindleUnlimited;
    int category_id;
    bool isBestSeller;
    bool isEditorsPick;
    bool isGoodReadsChoice;
    std::string publishedDate;
    std::string category_name;
};

// Global hash table for books
extern std::unordered_map<std::string, Book> bookTable;

// Load CSV file into the hash table
void loadBooks(const std::string& filename);

// Search by ASIN (exact)
Book* searchBook(const std::string& asin);

// Search by title (partial match)
std::vector<Book*> searchByTitle(const std::string& titleFragment);

// Search by author (partial match)
std::vector<Book*> searchByAuthor(const std::string& authorFragment);

// Utility: print book details
void printBook(const Book* book);

#endif

