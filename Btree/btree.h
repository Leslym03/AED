#include<iostream>
#include <vector>
#include <fstream>
using namespace std;

class Node {
    int n;
    int t;
    bool leaf;
    vector <int> keys;
    vector <Node *> childs;
public:
    Node(int _t, bool _leaf);

    void insertNonFull(int k);
    void splitChild(int i, Node *y);
    void traverse();
    Node *search(int k);

friend class Tree;
};

class Tree{
    Node *root;
    int t;
public:
    Tree(int _t) {
        root = NULL;  t = _t;
    }

    void traverse() {
        if (root != NULL) root->traverse();
    }

    Node* search(int k) {
        return (root == NULL)? NULL : root->search(k);
    }

    Node* getRoot() {
        return root;
    }

    int minimum(Node *x);
    int maximum(Node *x);

    void insert(int k);

friend class Node;
};

