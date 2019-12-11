#include<iostream>
#include <vector>
#include <fstream>
using namespace std;

Node::Node(int t1, bool leaf1) {
    t = t1;
    leaf = leaf1;

    keys.reserve(2*t-1);
    childs.reserve(2*t);
    n = 0;
}

void Node::traverse() {
    int i;
    for (i = 0; i < n; i++){
        if (leaf == false)
            childs[i]->traverse();

        cout << " " << keys[i];
    }

    if (leaf == false)
        childs[i]->traverse();
}

Node *Node::search(int k) {
    int i = 0;
    while (i < n && k > keys[i])
        i++;

    if (keys[i] == k)
        return this;

    if (leaf == true)
        return NULL;

    return childs[i]->search(k);
}

void Tree::insert(int k) {
    if (root == NULL) {
        root = new Node(t, true);
        root->keys[0] = k;
        root->n = 1;
    } else  {
        if (root->n == 2*t-1){
            Node *s = new Node(t, false);

            s->childs[0] = root;

            s->splitChild(0, root);

            int i = 0;
            if (s->keys[0] < k)
                i++;
            s->childs[i]->insertNonFull(k);

            root = s;
        }
        else 
            root->insertNonFull(k);
    }
}

int Tree::minimum( Node *x) {
    return (x->leaf==true) ? x->keys[0] : minimum(x->childs[0]);
}

int Tree::maximum(Node *x) {
    return (x->leaf==true) ? x->keys[x->n-1] : maximum(x->childs[x->n]);
}

void Node::insertNonFull(int k) {
    int i = n-1;

    if (leaf == true) {
        while (i >= 0 && keys[i] > k){
            keys[i+1] = keys[i];
            i--;
        }
        keys[i+1] = k;
        n = n+1;
    }
    else {
        while (i >= 0 && keys[i] > k)
            i--;

        if (childs[i+1]->n == 2*t-1) {
            splitChild(i+1, childs[i+1]);
            if (keys[i+1] < k)
                i++;
        }
        childs[i+1]->insertNonFull(k); 
    }
}

void Node::splitChild(int i, Node *y){
    Node *z = new Node(y->t, y->leaf);
    z->n = t - 1;

    for (int j = 0; j < t-1; j++)
        z->keys[j] = y->keys[j+t];

    if (y->leaf == false){
        for (int j = 0; j < t; j++)
            z->childs[j] = y->childs[j+t];
    }
    y->n = t - 1; 

    for (int j = n; j >= i+1; j--)
        childs[j+1] = childs[j];

    childs[i+1] = z;

    for (int j = n-1; j >= i; j--)
        keys[j+1] = keys[j];

    keys[i] = y->keys[t-1];
    n = n + 1;
}

int main(){
    Tree t(3);

    fstream inputFile;
    inputFile.open("data.txt", ios::in);

    int choice = 1;	
    int value = 0; 	

    while (choice != 0) {
        system("cls");
        if (t.getRoot()==NULL) cout << "\nAny elements";
        else {
            t.traverse();
        }

        cout << "\n1. Agregar nodo: ";
        cout << "\n3. Cargar datos del archivo: ";
        cout << "\n4. Minimo: ";
        cout << "\n5. Maximo: ";
        cout << "\n0. Salir.\n";

        cin >> choice;

        switch (choice){
            case 0:
                inputFile.close();
                system("PAUSE");
                return 0;
                break;
            case 1:
                cout << "\nType value ";
                cin >> value;
                t.insert(value);
                break;
            case 3:
                while (inputFile >> value) t.insert(value);
                cout << "\nCargando Datos";
                break;
            case 4:
                cout << "Minimo valor es: " << t.minimum(t.getRoot()) << endl;
                break;
            case 5:
                cout << "Maximo valor es: " << t.maximum(t.getRoot()) << endl;
                system("pause");
                break;
			default:
                break;
        }
    }

    t.insert(10);
    t.insert(20);
    t.insert(5);
    t.insert(6);
    t.insert(12);
    t.insert(30);
    t.insert(7);
    t.insert(17);

    cout << "El recorrido del árbol construido es ";
    t.traverse();

    int k = 6;
    (t.search(k) != NULL)? cout << "\nPresente" : cout << "\nNo Presente";

    k = 15;
    (t.search(k) != NULL)? cout << "\nPresente" : cout << "\nNo Presente";

    return 0;
}