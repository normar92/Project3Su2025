//
// Created by nrmma on 8/2/2025.
//

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <string>
#include <unordered_map>
#include <vector>
#include "Book.h"

// Global hash table for books
extern std::unordered_map<std::string, Book> bookTable;

// Search by ASIN (exact)
Book* searchBook(const std::string& asin);

// Search by title (partial match)
std::vector<Book*> searchByTitle(const std::string& titleFragment);

// Search by author (partial match)
std::vector<Book*> searchByAuthor(const std::string& authorFragment);

#endif
