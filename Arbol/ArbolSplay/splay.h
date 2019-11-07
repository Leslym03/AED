#ifndef SPLAY_H
#define SPLAY_H

#include <bits/stdc++.h>
#include <iostream>
#include <QGraphicsView>
#include <QTextStream>
#include <QProcess>
using namespace std ;

class SplayTree{
  public:
    SplayTree();
    ~SplayTree();
    void Insert(const int& value);
    void Remove(const int& value);
    void Clear();
    bool Find(const int& value);

    //********************

    void init(QGraphicsScene* scene, QGraphicsView* view);
    int countNodes();
    int countLevels();
    int countLeftNodes();
    void show();

private:
    struct Node {
            int value;
            Node *left;
            Node *right;
    };

    Node *root;

    Node* RotateLeft(Node *node);
    Node* RotateRight(Node *node);
    Node* Splay(Node *node, const int& value);
    Node* Insert(Node *node, const int& value);
    Node* Remove(Node *node, const int& value);
    void Clear(Node* &node);

    //********************

    QGraphicsScene* _scene;
    QGraphicsView* _view;

    int countNodes(Node* p);
    int countLevels(Node* p);
    int countLeftNodes(Node *p);
    Node* findSuccessor(int val);
    QByteArray _prepareGraph();
    void _graphWalk(Node* p,  QTextStream* stream);
};


#endif // SPLAY_H
