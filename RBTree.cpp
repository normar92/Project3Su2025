

#include "RBTree.h"
#include <iostream>
#include <algorithm>
using namespace std;

void RBTree::initializeNil() {
    _nil = new Node(Book());
    _nil->isRed = false;
    _nil->left = nullptr;
    _nil->right = nullptr;
    _nil->parent = nullptr;
}

void RBTree::deleteTree(Node* node) {
    if (node == _nil)
        return;
    else {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

void RBTree::inOrderHelper(Node* node) const {
    if (node == _nil)
        return;
    else {
        inOrderHelper(node->left);
        node->data.print();
        inOrderHelper(node->right);
    }
}

void RBTree::leftRotate(Node* a) {
    Node* b = a->right;
    a->right = b->left;

    if (b->left != _nil)
        b->left->parent = a;

    b->parent = a->parent;

    if (a->parent == _nil)
        _root = b;
    else if (a == a->parent->left)
        a->parent->left = b;
    else
        a->parent->right = b;

    b->left = a;
    a->parent = b;
}

void RBTree::rightRotate(Node* a) {
    Node* b = a->left;
    a->left = b->right;

    if (b->right != _nil)
        b->right->parent = a;

    b->parent = a->parent;

    if (a->parent == _nil)
        _root = b;
    else if (a == a->parent->right)
        a->parent->right = b;
    else
        a->parent->left = b;

    b->right = a;
    a->parent = b;
}

RBTree::Node* RBTree::insertHelper(Node* root, Node* node) {
    if (root == _nil)
        return node;
    else {
        if (comparator(node->data, root->data)) {
            Node* leftChild = insertHelper(root->left, node);
            root->left = leftChild;
            leftChild->parent = root;
        } else {
            Node* rightChild = insertHelper(root->right, node);
            root->right = rightChild;
            rightChild->parent = root;
        }
    }
    return root;
}

void RBTree::searchHelper(Node* node, const string& keyword, vector<Book>& books) const {
    if (node == _nil)
        return;
    else {
        string keywordLowercase = keyword;
        transform(keywordLowercase.begin(), keywordLowercase.end(), keywordLowercase.begin(), ::tolower);

        searchHelper(node->left, keyword, books);

        string titleLowercase = node->data.title;
        transform(titleLowercase.begin(), titleLowercase.end(), titleLowercase.begin(), ::tolower);

        if (titleLowercase.find(keywordLowercase) != string::npos)
            books.push_back(node->data);

        searchHelper(node->right, keyword, books);
    }
}

void RBTree::setSortHelper(Node* node, vector<Book>& books) const {
    if (node == _nil)
        return;
    else {
        setSortHelper(node->left, books);
        books.push_back(node->data);
        setSortHelper(node->right, books);
    }
}

RBTree::RBTree() {
    initializeNil();
    _root = _nil;
    setSort(1);
}

RBTree::~RBTree() {
    deleteTree(_root);
    delete _nil;
}

void RBTree::setSort(const int& key) {
    if (key == 1) {
        comparator = [](const Book& a, const Book& b) {
            return a.title < b.title;
        };
    } else if (key == 2) {
        comparator = [](const Book& a, const Book& b) {
            return a.author < b.author;
        };
    } else if (key == 3) {
        comparator = [](const Book& a, const Book& b) {
            return a.category_name < b.category_name;
        };
    } else if (key == 4) {
        comparator = [](const Book& a, const Book& b) {
            return a.publishedDate < b.publishedDate;
        };
    }

    vector<Book> books;
    setSortHelper(_root, books);
    deleteTree(_root);
    _root = _nil;

    for (const Book& book : books)
        insert(book);
}

void RBTree::insert(const Book& book) {
    Node* node = new Node(book);
    node->left = _nil;
    node->right = _nil;

    if (_root == _nil) {
        _root = node;
        _root->isRed = false;
        _root->parent = _nil;
    } else {
        _root = insertHelper(_root, node);

        while (node->parent->isRed) {
            if (node->parent == node->parent->parent->left) {
                Node* temp = node->parent->parent->right;

                if (temp->isRed) {
                    node->parent->isRed = false;
                    temp->isRed = false;
                    node->parent->parent->isRed = true;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        leftRotate(node);
                    }

                    node->parent->isRed = false;
                    node->parent->parent->isRed = true;
                    rightRotate(node->parent->parent);
                }
            } else {
                Node* temp = node->parent->parent->left;
                if (temp->isRed) {
                    node->parent->isRed = false;
                    temp->isRed = false;
                    node->parent->parent->isRed = true;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rightRotate(node);
                    }

                    node->parent->isRed = false;
                    node->parent->parent->isRed = true;
                    leftRotate(node->parent->parent);
                }
            }
        }
    }
    _root->isRed = false;
}

void RBTree::inOrder() const {
    if (_root == _nil)
        cout << "No books found." << endl;
    inOrderHelper(_root);
}

RBTree RBTree::search(const string& keyword) const {
    vector<Book> books;
    searchHelper(_root, keyword, books);
    RBTree subTree;

    for (const Book& book : books)
        subTree.insert(book);

    return subTree;
}