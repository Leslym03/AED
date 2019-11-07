#include "avl.h"
#include <bits/stdc++.h>
#include <iostream>
#include <QGraphicsView>
#include <QTextStream>
#include <QProcess>
using namespace std ;

void AvlTree::insert( const int & x, AvlNode * & t ){
        if( t == nullptr )
            t = new AvlNode{ x, nullptr, nullptr };
        else if( x < t->element )
            insert( x, t->left );
        else if( t->element < x )
            insert( x, t->right );

        balance( t );
    }

void AvlTree::insert( int && x, AvlNode * & t ){
        if( t == nullptr )
            t = new AvlNode{ std::move( x ), nullptr, nullptr };
        else if( x < t->element )
            insert( std::move( x ), t->left );
        else if( t->element < x )
            insert( std::move( x ), t->right );

        balance( t );
    }

void AvlTree::remove( const int & x, AvlNode * & t ){
        if( t == nullptr )
            return;   // Item not found; do nothing
        if( x < t->element )
            remove( x, t->left );
        else if( t->element < x )
            remove( x, t->right );
        else if( t->left != nullptr && t->right != nullptr ){
            t->element = findMin( t->right )->element;
            remove( t->element, t->right );
        }
        else{
            AvlNode *oldNode = t;
            t = ( t->left != nullptr ) ? t->left : t->right;
            delete oldNode;
        }

        balance( t );
    }

    void AvlTree::balance( AvlNode * & t ){
        if( t == nullptr )
            return;
        if( height( t->left ) - height( t->right ) > ALLOWED_IMBALANCE )
            if( height( t->left->left ) >= height( t->left->right ) )
                rotateWithLeftChild( t );
            else
                doubleWithLeftChild( t );
        else
        if( height( t->right ) - height( t->left ) > ALLOWED_IMBALANCE )
            if( height( t->right->right ) >= height( t->right->left ) )
                rotateWithRightChild( t );
            else
                doubleWithRightChild( t );

        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }

    void AvlTree::makeEmpty( AvlNode * & t ){
        if( t != nullptr ){
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = nullptr;
    }

    int AvlTree::height( AvlNode *t ) const{
        return t == nullptr ? -1 : t->height;
    }

    int AvlTree::max( int lhs, int rhs ) const{
        return lhs > rhs ? lhs : rhs;
    }

    AvlTree::AvlNode * AvlTree::findMin( AvlNode *t ) const{
            if( t == nullptr )
                return nullptr;
            if( t->left == nullptr )
                return t;
            return findMin( t->left );
    }

    AvlTree::AvlNode * AvlTree::findMax( AvlNode *t ) const{
            if( t != nullptr )
                while( t->right != nullptr )
                    t = t->right;
            return t;
    }

    void AvlTree::rotateWithLeftChild( AvlNode * & k2 ){
        AvlNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    void AvlTree::rotateWithRightChild( AvlNode * & k1 ){
        AvlNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }

    void AvlTree::doubleWithLeftChild( AvlNode * & k3 ){
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }

    void AvlTree::doubleWithRightChild( AvlNode * & k1 ){
        rotateWithLeftChild( k1->right );
        rotateWithRightChild( k1 );
    }

    AvlTree::AvlTree(){
        root = nullptr;
    }

    AvlTree::~AvlTree(){
        makeEmpty( );
    }

    void AvlTree::insert( const int & x ){
        insert( x, root );
    }

    void AvlTree::insert( int && x ){
        insert( std::move( x ), root );
    }

    void AvlTree::remove( const int & x ){
        remove( x, root );
    }

    void AvlTree:: makeEmpty(){
        makeEmpty( root );
    }

    const int & AvlTree::findMin() const{
            return findMin( root )->element;
    }

    const int & AvlTree::findMax() const{
            return findMax( root )->element;
    }

    bool AvlTree::isEmpty() const{
            return root == nullptr;
    }



//*******

    void AvlTree::init(QGraphicsScene* scene, QGraphicsView* view){
        this->root = nullptr ;
        this->_scene = scene;
        this->_view = view;
    }

    int AvlTree::countLevels(AvlNode* p){
            int h1 = 0, h2 = 0;
            if(p == nullptr) return 0;
            if(p->left)
                h1 = countLevels(p->left);
            if(p->right)
                h2 = countLevels(p->right);
            return(max(h1,h2)+1);
    }

    int AvlTree::countLevels(){
        return this->countLevels(this->root);
    }

    int AvlTree::countNodes(AvlNode* p){
          if(p == nullptr)
                return 0;
          else
                return (countNodes(p->left) + countNodes(p->right)+1);
    }

    int AvlTree::countNodes(){
        return this->countNodes( root);
    }

    int AvlTree::countLeftNodes(AvlNode* p) {
        if(p == nullptr)
              return 0;
        else
            return (countLeftNodes(p->left) + countLeftNodes(p->right)) + (p->left != NULL && p->right == NULL)? 1 : 0;
    }

    int AvlTree::countLeftNodes(){
        return this->countLeftNodes(this->root);
    }

    void AvlTree::_graphWalk(AvlNode* p, QTextStream *stream) {
        if (p != nullptr){
                *stream << "\t\t" << "n" << p->element << "[label=\"" << p->element <<"\"];" << endl;

            if(p->left != nullptr){
                *stream << "\t\tn" << p->element << "--" << "n" << p->left->element << ";" << endl;
                this->_graphWalk(p->left, stream);
            }else{
                *stream << "\t\t" << "n" << p->element << "leftNull" << "[style=\"filled\",label=\"NULL\"];" << endl;
                *stream << "\t\tn" << p->element << "--" << "n" << p->element << "leftNull" << endl;
            }

            if(p->right != nullptr){
                *stream << "\t\tn" << p->element << "--" << "n" << p->right->element << ";" << endl;
                this->_graphWalk(p->right, stream);
            }else{
                *stream << "\t\t" << "n" << p->element << "rightNull" << "[style=\"filled\",label=\"NULL\"];" << endl;
                *stream << "\t\tn" << p->element << "--" << "n" << p->element << "rightNull" << endl;
            }
        }
    }

    QByteArray AvlTree::_prepareGraph(){
        QByteArray a = QByteArray();

        QTextStream stream(&a, QIODevice::ReadWrite);
        stream << "graph ""{" << endl;
        stream << "\tnode[fontsize=10,margin=0,width=\".4\", height=\".3\"];" << endl;
        //stream << "\tsubgraph cluster17{" << endl;

        this->_graphWalk(this->root, &stream);
        stream << "\t}\n" << "}" << endl;
        stream.flush();

        return a;
    }

    void AvlTree::show(){
        QProcess* p = new QProcess();
        QByteArray a = this->_prepareGraph();

        p->setProcessChannelMode(QProcess::MergedChannels);
        p->start("dot", QStringList() << "-Tpng");
        p->write(a);

        QByteArray data;
        QPixmap pixmap = QPixmap();

        while(p->waitForReadyRead(100)){
            data.append(p->readAll());
        }

        pixmap.loadFromData(data);
        this->_scene->clear();
        this->_scene->addPixmap(pixmap);
        this->_view->show();
    }
