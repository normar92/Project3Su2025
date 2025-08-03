//
// Created by nrmma on 8/3/2025.
//
#include "Book.h"
#include <iostream>

void Book::print() const {
    std::cout << "\n--- Book Details ---\n";
    std::cout << "ASIN: " << asin << "\n";
    std::cout << "Title: " << title << "\n";
    std::cout << "Author: " << author << "\n";
    std::cout << "Price: $" << price << "\n";
    std::cout << "Stars: " << stars << " (" << reviews << " reviews)\n";
    std::cout << "Category: " << category_name << "\n";
    std::cout << "Published: " << publishedDate << "\n";
    std::cout << "Sold By: " << soldBy << "\n";
    std::cout << "URL: " << productURL << "\n";
    std::cout << (isBestSeller ? "[Best Seller] " : "")
              << (isEditorsPick ? "[Editor's Pick] " : "")
              << (isGoodReadsChoice ? "[GoodReads Choice] " : "")
              << (isKindleUnlimited ? "[Kindle Unlimited]" : "")
              << "\n";
}
