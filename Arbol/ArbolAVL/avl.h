#ifndef AVL_H
#define AVL_H

#include <bits/stdc++.h>
#include <iostream>
#include <QGraphicsView>
#include <QTextStream>
#include <QProcess>
using namespace std ;

class AvlTree{
private:
    struct AvlNode{
        int element;
        AvlNode   *left;
        AvlNode   *right;
        int       height;

        AvlNode( const int & ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element{ ele }, left{ lt }, right{ rt }, height{ h } { }

        AvlNode( int && ele, AvlNode *lt, AvlNode *rt, int h = 0 )
          : element{ std::move( ele ) }, left{ lt }, right{ rt }, height{ h } { }
    };
    AvlNode *root;

    void insert( const int & x, AvlNode * & t );
    void insert( int && x, AvlNode * & t );
    void remove( const int & x, AvlNode * & t );

    static const int ALLOWED_IMBALANCE = 1;

    void balance( AvlNode * & t );
    void makeEmpty( AvlNode * & t );
    int height( AvlNode *t ) const;
    int max( int lhs, int rhs ) const;
    AvlNode * findMin( AvlNode *t ) const;
    AvlNode * findMax( AvlNode *t ) const;

    void rotateWithLeftChild( AvlNode * & k2 );
    void rotateWithRightChild( AvlNode * & k1 );
    void doubleWithLeftChild( AvlNode * & k3 );
    void doubleWithRightChild( AvlNode * & k1 );

    //********************

    QGraphicsScene* _scene;
    QGraphicsView* _view;

    int countNodes(AvlNode* p);
    int countLevels(AvlNode* p);
    int countLeftNodes(AvlNode *p);
    AvlNode* findSuccessor(int val);
    QByteArray _prepareGraph();
    void _graphWalk(AvlNode* p,  QTextStream* stream);

public:
    AvlTree();
    ~AvlTree();
    void insert( const int & x );
    void insert( int && x );
    void remove( const int & x );
    void makeEmpty();
    const int & findMin( ) const;
    const int & findMax( ) const;
    bool isEmpty( ) const;

    //********************

    void init(QGraphicsScene* scene, QGraphicsView* view);
    int countNodes();
    int countLevels();
    int countLeftNodes();
    void show();

};




#endif // AVL_H
