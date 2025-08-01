#include "RBTree.h"
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
        searchHelper(node->left, keyword, books);

        if (node->data._title.find(keyword) != string::npos)
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
            return a._title < b._title;
        };
    } else if (key == 2) {
        comparator = [](const Book& a, const Book& b) {
            return a._author < b._author;
        };
    } else if (key == 3) {
        comparator = [](const Book& a, const Book& b) {
            return a._genre < b._genre;
        };
    } else if (key == 4) {
        comparator = [](const Book& a, const Book& b) {
            return a._year < b._year;
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