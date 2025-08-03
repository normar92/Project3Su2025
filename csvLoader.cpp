//
// Created by nrmma on 8/3/2025.
//

#include "csvLoader.h"
#include <fstream>
#include <iostream>

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
        } else if (c == ',' && !insideQuotes) {
            result.push_back(field);
            field.clear();
        } else {
            field += c;
        }
    }
    result.push_back(field);
    return result;
}

void loadBooks(const std::string& filename, RBTree& tree) {
    std::ifstream file(filename);
    if (!file) {
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

        // insert into both data structures
        bookTable[b.asin] = b;
        tree.insert(b);
    }
}
