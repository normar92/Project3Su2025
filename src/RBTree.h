#ifndef RBTREE_H
#define RBTREE_H
#include <string>
#include <vector>
#include <functional>
#include "Book.h"
using namespace std;

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
        function<bool(const Book&, const Book&)> comparator;

        void initializeNil();
        void deleteTree(Node* node);
        void inOrderHelper(Node* node) const;
        void leftRotate(Node* a);
        void rightRotate(Node* a);
        //void insertHelper(Node* a);
        Node* insertHelper(Node* root, Node* node);
        void searchHelper(Node* node, const string& keyword, vector<Book>& books) const;
        void setSortHelper(Node* node, vector<Book>& books) const;

public:
        RBTree();
        ~RBTree();
        void setSort(const int& key);
        void insert(const Book& book);
        void inOrder() const;
        RBTree search(const string& keyword) const;



};

#endif //RBTREE_H