#ifndef REDBLACK_H
#define REDBLACK_H

#include <bits/stdc++.h>
#include <iostream>
#include <QGraphicsView>
#include <QTextStream>
#include <QProcess>
using namespace std ;

enum Color {RED, BLACK, DOUBLE_BLACK};

struct Node{
    int data;
    int color;
    Node *left, *right, *parent;

    explicit Node(int);
};

class RBTree{
    private:
        Node *root;
    protected:
        void rotateLeft(Node *&);
        void rotateRight(Node *&);
        void transplant(Node * destNode, Node * sourceNode);
        void fixInsertRBTree(Node *&);
        void fixDeleteRBTree(Node *&);
        int getColor(Node *&);
        void setColor(Node *&, int);
        Node *minValueNode(Node *&);
        Node *maxValueNode(Node *&);
        Node* deleteBST(Node *&, int);

        void deleteFixup(Node * node);

        //********************

        QGraphicsScene* _scene;
        QGraphicsView* _view;

        int countNodes(Node* p);
        int countLevels(Node* p);
        int countLeftNodes(Node *p);
        Node* findSuccessor(int val);
        QByteArray _prepareGraph();
        void _graphWalk(Node* p,  QTextStream* stream);
    public:
        RBTree();
        Node * getNode(int value);
        void insertValue(int);
        void deleteValue(int);
        void remove(int value);

        //********************

        void init(QGraphicsScene* scene, QGraphicsView* view);
        int countNodes();
        int countLevels();
        int countLeftNodes();
        void show();
};

#endif // REDBLACK_H
