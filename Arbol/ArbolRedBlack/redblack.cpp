#include "redblack.h"
#include <bits/stdc++.h>
#include <iostream>
#include <QGraphicsView>
#include <QTextStream>
#include <QProcess>
using namespace std ;

Node::Node(int data) {
    this->data = data;
    color = RED;
    left = right = parent = nullptr;
}

RBTree::RBTree() {
    root = nullptr;
}

Node* RBTree::getNode(int value) {
    Node * node = root;
    while (node != nullptr && value != node->data) {
        if (value < node->data)
            node = node->left;
        else
            node = node->right;
    }
    return node;
}

int RBTree::getColor(Node *&node) {
    if (node == nullptr)
        return BLACK;
    return node->color;
}

void RBTree::setColor(Node *&node, int color) {
    if (node == nullptr)
        return;
    node->color = color;
}

void RBTree::insertValue(int n) {
    Node *node = new Node(n);
    Node *y = nullptr;
    Node *x = root;
    while (x != nullptr) {
        y = x;
        if (node->data < x->data)
            x = x->left;
        else
            x = x->right;
    }
    node->parent = y;
    if(y == nullptr)
        root = node;
    else if (node->data < y->data)
        y->left = node;
    else
        y->right = node;
    fixInsertRBTree(node);
}

void RBTree::rotateLeft(Node *&ptr) {
    Node *right_child = ptr->right;
    ptr->right = right_child->left;

    if (ptr->right != nullptr)
        ptr->right->parent = ptr;

    right_child->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = right_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = right_child;
    else
        ptr->parent->right = right_child;

    right_child->left = ptr;
    ptr->parent = right_child;
}

void RBTree::rotateRight(Node *&ptr) {
    Node *left_child = ptr->left;
    ptr->left = left_child->right;

    if (ptr->left != nullptr)
        ptr->left->parent = ptr;

    left_child->parent = ptr->parent;

    if (ptr->parent == nullptr)
        root = left_child;
    else if (ptr == ptr->parent->left)
        ptr->parent->left = left_child;
    else
        ptr->parent->right = left_child;

    left_child->right = ptr;
    ptr->parent = left_child;
}

void RBTree::transplant(Node *destNode, Node *sourceNode){
    if (destNode->parent == nullptr)
        root = sourceNode;
    else if (destNode == destNode->parent->left)
        destNode->parent->left = sourceNode;
    else
        destNode->parent->right = sourceNode;
    sourceNode->parent = destNode->parent;
}

void RBTree::fixInsertRBTree(Node *&ptr) {
    Node *parent = nullptr;
    Node *grandparent = nullptr;
    while (ptr != root && getColor(ptr) == RED && getColor(ptr->parent) == RED) {
        parent = ptr->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left) {
            Node *uncle = grandparent->right;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            } else {
                if (ptr == parent->right) {
                    rotateLeft(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateRight(grandparent);
                swap(parent->color, grandparent->color);
                ptr = parent;
            }
        } else {
            Node *uncle = grandparent->left;
            if (getColor(uncle) == RED) {
                setColor(uncle, BLACK);
                setColor(parent, BLACK);
                setColor(grandparent, RED);
                ptr = grandparent;
            } else {
                if (ptr == parent->left) {
                    rotateRight(parent);
                    ptr = parent;
                    parent = ptr->parent;
                }
                rotateLeft(grandparent);
                swap(parent->color, grandparent->color);
                ptr = parent;
            }
        }
    }
    setColor(root, BLACK);
}

void RBTree::fixDeleteRBTree(Node *&node) {
    if (node == nullptr)
        return;
    if (node == root) {
        root = nullptr;
        return;
    }
    if (getColor(node) == RED || getColor(node->left) == RED || getColor(node->right) == RED) {
        Node *child = node->left != nullptr ? node->left : node->right;
        if (node == node->parent->left) {
            node->parent->left = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            delete (node);
        } else {
            node->parent->right = child;
            if (child != nullptr)
                child->parent = node->parent;
            setColor(child, BLACK);
            delete (node);
        }
    } else {
        Node *sibling = nullptr;
        Node *parent = nullptr;
        Node *ptr = node;
        setColor(ptr, DOUBLE_BLACK);
        while (ptr != root && getColor(ptr) == DOUBLE_BLACK) {
            parent = ptr->parent;
            if (ptr == parent->left) {
                sibling = parent->right;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateLeft(parent);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if(getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(sibling->right) == BLACK) {
                            setColor(sibling->left, BLACK);
                            setColor(sibling, RED);
                            rotateRight(sibling);
                            sibling = parent->right;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->right, BLACK);
                        rotateLeft(parent);
                        break;
                    }
                }
            } else {
                sibling = parent->left;
                if (getColor(sibling) == RED) {
                    setColor(sibling, BLACK);
                    setColor(parent, RED);
                    rotateRight(parent);
                } else {
                    if (getColor(sibling->left) == BLACK && getColor(sibling->right) == BLACK) {
                        setColor(sibling, RED);
                        if (getColor(parent) == RED)
                            setColor(parent, BLACK);
                        else
                            setColor(parent, DOUBLE_BLACK);
                        ptr = parent;
                    } else {
                        if (getColor(sibling->left) == BLACK) {
                            setColor(sibling->right, BLACK);
                            setColor(sibling, RED);
                            rotateLeft(sibling);
                            sibling = parent->left;
                        }
                        setColor(sibling, parent->color);
                        setColor(parent, BLACK);
                        setColor(sibling->left, BLACK);
                        rotateRight(parent);
                        break;
                    }
                }
            }
        }
        if (node == node->parent->left)
            node->parent->left = nullptr;
        else
            node->parent->right = nullptr;
        delete(node);
        setColor(root, BLACK);
    }
}

Node* RBTree::deleteBST(Node *&root, int data) {
    if (root == nullptr)
        return root;

    if (data < root->data)
        return deleteBST(root->left, data);

    if (data > root->data)
        return deleteBST(root->right, data);

    if (root->left == nullptr || root->right == nullptr)
        return root;

    Node *temp = minValueNode(root->right);
    root->data = temp->data;
    return deleteBST(root->right, temp->data);
}

void RBTree::deleteValue(int data) {
    Node *node = deleteBST(root, data);
    fixDeleteRBTree(node);
}

Node *RBTree::minValueNode(Node *&node) {
    Node *ptr = node;
    while (ptr->left != nullptr)
        ptr = ptr->left;
    return ptr;
}

Node* RBTree::maxValueNode(Node *&node) {
    Node *ptr = node;
    while (ptr->right != nullptr)
        ptr = ptr->right;
    return ptr;
}

//Implementacion eliminar como libro Cormen

void RBTree::remove(int value) {
    Node * node = getNode(value);
    Node * temp = node;
    Node * temp2;
    int origColor = getColor(temp);
    if (node->left == nullptr) {
        temp2 = node->right;
        transplant(node, node->right);
    } else if (node->right == nullptr) {
        temp2 = node->left;
        transplant(node, node->left);
    } else {
        temp = minValueNode(node->right);
        origColor = temp->color;
        temp2 = temp->right;
        if (temp->parent == node) {
            temp2->parent = temp;
        } else {
            transplant(temp, temp->right);
            temp->right = node->right;
            temp->right->parent = temp;
        }
        transplant(node, temp);
        temp->left = node->left;
        temp->left->parent = temp;
        temp->color = node->color;
    }
    if (origColor == Color::BLACK)
        deleteFixup(temp2);
}

void RBTree::deleteFixup(Node * node) {
    Node * temp;
    while (node != this->root && node->color == Color::BLACK) {
        if (node == node->parent->left) {
            temp = node->parent->right;
            if (temp->color == Color::RED) {
                temp->color = Color::BLACK;
                node->parent->color = Color::RED;
                rotateLeft(node->parent);
                temp = node->parent->right;
            }
            if (temp->left->color == Color::BLACK && temp->right->color == Color::BLACK) {
                temp->color = Color::RED;
                node = node->parent;
            } else {
                if (temp->right->color == Color::BLACK) {
                    temp->left->color = Color::BLACK;
                    temp->color = Color::RED;
                    rotateRight(temp);
                    temp = node->parent->right;
                }
                temp->color = node->parent->color;
                node->parent->color = Color::BLACK;
                temp->right->color = Color::BLACK;
                rotateLeft(node->parent);
                node = this->root;
            }
        } else {
            temp = node->parent->left;
            if (temp->color == Color::RED) {
                temp->color = Color::BLACK;
                node->parent->color = Color::RED;
                rotateRight(node->parent);
                temp = node->parent->left;
            }
            if (temp->right->color == Color::BLACK && temp->left->color == Color::BLACK) {
                temp->color = Color::RED;
                node = node->parent;
            } else {
                if (temp->left->color == Color::BLACK) {
                    temp->right->color = Color::BLACK;
                    temp->color = Color::RED;
                    rotateLeft(temp);
                    temp = node->parent->left;
                }
                temp->color = node->parent->color;
                node->parent->color = Color::BLACK;
                temp->left->color = Color::BLACK;
                rotateRight(node->parent);
                node = this->root;
            }
        }
    }
    node->color = Color::BLACK;
}

//*******

    void RBTree::init(QGraphicsScene* scene, QGraphicsView* view){
        this->root = nullptr ;
        this->_scene = scene;
        this->_view = view;
    }

    int RBTree::countLevels(Node* p){
            int h1 = 0, h2 = 0;
            if(p == nullptr) return 0;
            if(p->left)
                h1 = countLevels(p->left);
            if(p->right)
                h2 = countLevels(p->right);
            return(max(h1,h2)+1);
    }

    int RBTree::countLevels(){
        return this->countLevels(this->root);
    }

    int RBTree::countNodes(Node* p){
          if(p == nullptr)
                return 0;
          else
                return (countNodes(p->left) + countNodes(p->right)+1);
    }

    int RBTree::countNodes(){
        return this->countNodes( root);
    }

    int RBTree::countLeftNodes(Node* p) {
        if(p == nullptr)
              return 0;
        else
            return (countLeftNodes(p->left) + countLeftNodes(p->right)) + (p->left != NULL && p->right == NULL)? 1 : 0;
    }

    int RBTree::countLeftNodes(){
        return this->countLeftNodes(this->root);
    }

    void RBTree::_graphWalk(Node* p, QTextStream *stream) {
        if (p != nullptr){
            if(p->color == BLACK)
                *stream << "\t\t" << "n" << p->data << "[label=\"" << p->data <<"\", fillcolor=\"black\", style=\"filled\",color=\"black\"];" << endl;
            if(p->color == RED)
                *stream << "\t\t" << "n" << p->data << "[label=\"" << p->data <<"\", fillcolor=\"red\", style=\"filled\", color=\"red\"];" << endl;
            if(p->left != nullptr){
                *stream << "\t\tn" << p->data << "--" << "n" << p->left->data << ";" << endl;
                this->_graphWalk(p->left, stream);
            }else{
                *stream << "\t\t" << "n" << p->data << "leftNull" << "[style=\"filled\",fillcolor=\"black\", style=\"filled\", label=\"NIL\"];" << endl;
                *stream << "\t\tn" << p->data << "--" << "n" << p->data << "leftNull" << endl;
            }

            if(p->right != nullptr){
                *stream << "\t\tn" << p->data << "--" << "n" << p->right->data << ";" << endl;
                this->_graphWalk(p->right, stream);
            }else{
                *stream << "\t\t" << "n" << p->data << "rightNull" << "[style=\"filled\",fillcolor=\"black\", style=\"filled\", label=\"NIL\"];" << endl;
                *stream << "\t\tn" << p->data << "--" << "n" << p->data << "rightNull" << endl;
            }
        }
    }

    QByteArray RBTree::_prepareGraph(){
        QByteArray a = QByteArray();

        QTextStream stream(&a, QIODevice::ReadWrite);
        stream << "graph ""{" << endl;
        stream << "\tnode[fontsize=10 , margin=0,width=\".4\", fontcolor=\"white\",height=\".3\"];" << endl;
        //stream << "\tsubgraph cluster17{" << endl;

        this->_graphWalk(this->root, &stream);
        stream << "\t}\n" << "}" << endl;
        stream.flush();

        return a;
    }

    void RBTree::show(){
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
