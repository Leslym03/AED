#include "splay.h"
#include <bits/stdc++.h>
#include <iostream>
#include <QGraphicsView>
#include <QTextStream>
#include <QProcess>
using namespace std ;

SplayTree::SplayTree() {
    root = nullptr;
}

SplayTree::~SplayTree() {
    Clear(root);
}

SplayTree::Node* SplayTree::RotateLeft(Node *node) {
    Node *right = node->right;
    node->right = right->left;
    right->left = node;
    return right;
}

SplayTree::Node* SplayTree::RotateRight(Node *node) {
    Node *left = node->left;
    node->left = left->right;
    left->right = node;
    return left;
}

SplayTree::Node* SplayTree::Splay(Node *node, const int& value) {
    if (node == nullptr || node->value == value)
        return node;
    if (value < node->value) {
        if (node->left == nullptr)
            return node;
        if (value < node->left->value) {
            node->left->left = Splay(node->left->left, value);
            node = RotateRight(node);
        }
        else if (value > node->left->value) {
            node->left->right = Splay(node->left->right, value);
            if (node->left->right)
                node->left = RotateLeft(node->left);
        }
        return (node->left == nullptr)? node : RotateRight(node);
    }
    else {
        if (node->right == nullptr)
            return node;
        if (value < node->right->value) {
            node->right->left = Splay(node->right->left, value);
            if (node->right->left)
                node->right = RotateRight(node->right);
        }
        else if (value > node->right->value) {
            node->right->right = Splay(node->right->right, value);
            node = RotateLeft(node);
        }
        return (node->right == nullptr) ? node : RotateLeft(node);
    }
}


SplayTree::Node* SplayTree::Insert(Node *node, const int& value) {
    if (node == nullptr) {
        node = new Node;
        node->value = value;
        node->left = nullptr;
        node->right = nullptr;
        return node;
    }
    node = Splay(node, value);
    Node *newNode = new Node;
    newNode->value = value;
    if (value < node->value) {
        newNode->right = node;
        newNode->left = node->left;
        node->left = nullptr;
    }
    else {
        newNode->left = node;
        newNode->right = node->right;
        node->right = nullptr;
    }
    return newNode;
}

SplayTree::Node* SplayTree::Remove(Node *node, const int& value) {
    if (node == nullptr)
        return nullptr;
    node = Splay(node, value);
    if (value != node->value)
        return node;
    Node *tmp;
    if (node->left == nullptr) {
        tmp = node;
        node = node->right;
    }
    else {
        tmp = node;
        node = Splay(node->left, value);
        node->right = tmp->right;
    }
    delete tmp;
    return node;
}

void SplayTree::Insert(const int& value) {
    root = Insert(root, value);
}

void SplayTree::Remove(const int& value) {
    root = Remove(root, value);
}

bool SplayTree::Find(const int& value) {
    root = Splay(root, value);
    if (root == nullptr)
        return false;
    return root->value == value;
}

void SplayTree::Clear() {
    Clear(root);
}

void SplayTree::Clear(Node* &node) {
    if (node == nullptr)
        return;
    Clear(node->left);
    Clear(node->right);
    delete node;
    node = nullptr;
}


    //*******

        void SplayTree::init(QGraphicsScene* scene, QGraphicsView* view){
            this->root = nullptr ;
            this->_scene = scene;
            this->_view = view;
        }

        int SplayTree::countLevels(Node* p){
                int h1 = 0, h2 = 0;
                if(p == nullptr) return 0;
                if(p->left)
                    h1 = countLevels(p->left);
                if(p->right)
                    h2 = countLevels(p->right);
                return(max(h1,h2)+1);
        }

        int SplayTree::countLevels(){
            return this->countLevels(this->root);
        }

        int SplayTree::countNodes(Node* p){
              if(p == nullptr)
                    return 0;
              else
                    return (countNodes(p->left) + countNodes(p->right)+1);
        }

        int SplayTree::countNodes(){
            return this->countNodes( root);
        }

        int SplayTree::countLeftNodes(Node* p) {
            if(p == nullptr)
                  return 0;
            else
                return (countLeftNodes(p->left) + countLeftNodes(p->right)) + (p->left != NULL && p->right == NULL)? 1 : 0;
        }

        int SplayTree::countLeftNodes(){
            return this->countLeftNodes(this->root);
        }

        void SplayTree::_graphWalk(Node* p, QTextStream *stream) {
            if (p != nullptr){
                    *stream << "\t\t" << "n" << p->value << "[label=\"" << p->value <<"\"];" << endl;

                if(p->left != nullptr){
                    *stream << "\t\tn" << p->value << "--" << "n" << p->left->value << ";" << endl;
                    this->_graphWalk(p->left, stream);
                }else{
                    *stream << "\t\t" << "n" << p->value << "leftNull" << "[style=\"filled\",label=\"NULL\"];" << endl;
                    *stream << "\t\tn" << p->value << "--" << "n" << p->value << "leftNull" << endl;
                }

                if(p->right != nullptr){
                    *stream << "\t\tn" << p->value << "--" << "n" << p->right->value << ";" << endl;
                    this->_graphWalk(p->right, stream);
                }else{
                    *stream << "\t\t" << "n" << p->value << "rightNull" << "[style=\"filled\",label=\"NULL\"];" << endl;
                    *stream << "\t\tn" << p->value << "--" << "n" << p->value << "rightNull" << endl;
                }
            }
        }

        QByteArray SplayTree::_prepareGraph(){
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

        void SplayTree::show(){
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
