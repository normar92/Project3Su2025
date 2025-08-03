//
// Created by nrmma on 8/2/2025.
//


#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include "hashTable.h"


std::unordered_map<std::string, Book> bookTable;

// Helper function to parse CSV correctly (handles quotes & commas)
static std::vector<std::string> parseCSVLine(const std::string& line) {
    std::vector<std::string> result;
    std::string field;
    bool insideQuotes = false;

    for (size_t i = 0; i < line.size(); ++i) {
        char c = line[i];

        if (c == '"') {
            if (insideQuotes && i + 1 < line.size() && line[i + 1] == '"') {
                field += '"';
                i++;
            } else {
                insideQuotes = !insideQuotes;
            }
        }
        else if (c == ',' && !insideQuotes) {
            result.push_back(field);
            field.clear();
        }
        else {
            field += c;
        }
    }
    result.push_back(field);
    return result;
}

void loadBooks(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
      // this was added to help troubleshoot
        std::cerr << "Error opening file: " << filename << "\n";
        return;
    }

    std::string line;
    std::getline(file, line); // Skip header

    while (std::getline(file, line)) {
        auto fields = parseCSVLine(line);
        if (fields.size() < 16) {
            std::cerr << "Skipping invalid row: " << line << "\n";
            continue;
        }

        Book b;
        b.asin = fields[0];
        b.title = fields[1];
        b.author = fields[2];
        b.soldBy = fields[3];
        b.imgUrl = fields[4];
        b.productURL = fields[5];

        try { b.stars = fields[6].empty() ? 0.0 : std::stod(fields[6]); }
        catch (...) { b.stars = 0.0; }

        try { b.reviews = fields[7].empty() ? 0 : std::stoi(fields[7]); }
        catch (...) { b.reviews = 0; }

        try { b.price = fields[8].empty() ? 0.0 : std::stod(fields[8]); }
        catch (...) { b.price = 0.0; }

        b.isKindleUnlimited = (fields[9] == "TRUE");
        try { b.category_id = fields[10].empty() ? 0 : std::stoi(fields[10]); }
        catch (...) { b.category_id = 0; }

        b.isBestSeller = (fields[11] == "TRUE");
        b.isEditorsPick = (fields[12] == "TRUE");
        b.isGoodReadsChoice = (fields[13] == "TRUE");
        b.publishedDate = fields[14];
        b.category_name = fields[15];

        bookTable[b.asin] = b;
    }
}

Book* searchBook(const std::string& asin) {
    auto it = bookTable.find(asin);
    if (it != bookTable.end()) {
        return &(it->second);
    }
    return nullptr;
}

// Partial search by title
std::vector<Book*> searchByTitle(const std::string& titleFragment) {
    std::vector<Book*> matches;
    std::string lowerFragment = titleFragment;

    // make case-insensitive review of the parsing
    std::transform(lowerFragment.begin(), lowerFragment.end(), lowerFragment.begin(), ::tolower);

    for (auto& pair : bookTable) {
        std::string lowerTitle = pair.second.title;
        std::transform(lowerTitle.begin(), lowerTitle.end(), lowerTitle.begin(), ::tolower);

        if (lowerTitle.find(lowerFragment) != std::string::npos) {
            matches.push_back(&(pair.second));
        }
    }
    return matches;
}

// Partial search by author
std::vector<Book*> searchByAuthor(const std::string& authorFragment) {
    std::vector<Book*> matches;
    std::string lowerFragment = authorFragment;

    std::transform(lowerFragment.begin(), lowerFragment.end(), lowerFragment.begin(), ::tolower);

    for (auto& pair : bookTable) {
        std::string lowerAuthor = pair.second.author;
        std::transform(lowerAuthor.begin(), lowerAuthor.end(), lowerAuthor.begin(), ::tolower);

        if (lowerAuthor.find(lowerFragment) != std::string::npos) {
            matches.push_back(&(pair.second));
        }
    }
    return matches;
}

// organize the printing book details
void printBook(const Book* book) {
    if (!book) return;

    std::cout << "\n--- Book Details ---\n";
    std::cout << "ASIN: " << book->asin << "\n";
    std::cout << "Title: " << book->title << "\n";
    std::cout << "Author: " << book->author << "\n";
    std::cout << "Price: $" << book->price << "\n";
    std::cout << "Stars: " << book->stars << " (" << book->reviews << " reviews)\n";
    std::cout << "Category: " << book->category_name << "\n";
    std::cout << "Published: " << book->publishedDate << "\n";
    std::cout << "URL: " << book->productURL << "\n";
}