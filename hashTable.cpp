//
// Created by nrmma on 8/2/2025.
//

#include "hashTable.h"
#include <algorithm>

std::unordered_map<std::string, Book> bookTable;

Book* searchBook(const std::string& asin) {
    auto it = bookTable.find(asin);
    if (it != bookTable.end()) {
        return &(it->second);
    }
    return nullptr;
}

std::vector<Book*> searchByTitle(const std::string& titleFragment) {
    std::vector<Book*> matches;
    std::string lowerFragment = titleFragment;

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
