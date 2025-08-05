# Project3Su2025 Amazon Kindle Books

This project implements 3 search and sorting algorithms using hash tbales and a red/black tree to the Amazon Kindle Book dataset. The dataset contains book details of asin,	title,	author, soldBy, imgUrl, productURL, stars,	reviews,	price,	isKindleUnlimited,	category_id,	isBestSeller, isEditorsPick,	isGoodReadsChoice,	publishedDate	and category_name. 

## Features:
1. Search by ASIN (Hash Table)
2. Search by Title (Hash Table, partial match)
3. Search by Author (Hash Table, partial match)
4. Keyword search (RBTree - title only)
5. Print all books (RBTree, sorted)
6. Change sorting order (RBTree)

## Sorting Algorithms Implemented:
- **Timer and Red/Black Tree (Vincent Zvolsky)**  
- **Hash Table Sort and UI (Norma Marin)**

## Data:
- Source: https://www.kaggle.com/datasets/asaniczka/amazon-kindle-books-dataset-2023-130k-books
- Includes book details for Amazon Kindle Books

## Usage:
- Clone the repository:
  ```bash
  git clone https://github.com/normar92/Project3Su2025
  ```
- !!! DUE TO THE FILE SIZE IT WOULD NOT ALLOW US TO UPLOAD THE RAW FILE!!!
- Please download the raw file (either thru the link or the "archive.zip" folder in the repo) and add to the directory before running the profile!! 
- Compile and run `main.cpp` to perform sorting operations.
- Select Options
- If using Option 1 - enter one of the following ASIN keys:
          B00AEBEQUK
          B0BN5742KY
          B098PXH8CK
          B087D5YQXB
          B00AN2JPNI
          B0B69SQNJY
          B07FZPTDJ3
          B0BN4RB7L9
          B0BNWSS8H3
          B0B3Y8QQ6R
  - Options 2-6 can use any type of key word and name. 

## Tools & Libraries:
- **Languages:** C++ 
- **Applications:** Excel, Clion

## Results:
- Outputs include sorted CSV files, results in searching keywords or ASIN keys. 

## Contributors:
- Vincent Zvolsky ([vincentzvo](https://github.com/vincentzvo))
- Norma Marin ([normar92](https://github.com/normar92))
