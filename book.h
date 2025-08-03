//
// Created by nrmma on 8/3/2025.
//

#ifndef BOOK_H
#define BOOK_H

#include <string>

class Book {
public:
    // Dataset fields
    std::string asin;
    std::string title;
    std::string author;
    std::string genre;
    int year;

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

    // Constructor
    Book(std::string asin_ = "", std::string title_ = "", std::string author_ = "",
         std::string genre_ = "", int year_ = 0)
        : asin(asin_), title(title_), author(author_), genre(genre_), year(year_),
          stars(0.0), reviews(0), price(0.0), isKindleUnlimited(false),
          category_id(0), isBestSeller(false), isEditorsPick(false),
          isGoodReadsChoice(false) {}

    // Utility: print book details
    void print() const;
};

#endif

//BOOK_H
