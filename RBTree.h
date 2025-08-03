#ifndef RBTREE_H
#define RBTREE_H

#include <string>
#include <vector>
#include <functional>
#include "Book.h"

class RBTree {
private:
    class Node {
    public:
        Book data;
        bool isRed;
        Node* left;
        Node* right;
        Node* parent;

        Node(const Book& book) : data(book), isRed(false), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* _root;
    Node* _nil;
    std::function<bool(const Book&, const Book&)> comparator;

    void initializeNil();
    void deleteTree(Node* node);
    void inOrderHelper(Node* node) const;
    void leftRotate(Node* a);
    void rightRotate(Node* a);
    Node* insertHelper(Node* root, Node* node);
    void searchHelper(Node* node, const std::string& keyword, std::vector<Book>& books) const;
    void setSortHelper(Node* node, std::vector<Book>& books) const;

public:
    RBTree();
    ~RBTree();
    void setSort(const int& key);
    void insert(const Book& book);
    void inOrder() const;
    RBTree search(const std::string& keyword) const;
};

#endif
