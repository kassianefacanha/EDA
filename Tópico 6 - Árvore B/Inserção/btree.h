#ifndef BTREE_H
#define BTREE_H
#include <iostream>
#include <queue>
#include "bnode.h"

class Btree {
private:
    Bnode *root;                // ponteiro para o node raiz
    int d;                      // grau minimo da arvore
    Bnode *clear(Bnode *node);  // libera todos os nodes e deixa arvore vazia

public:
    Btree(int d);               // Construtor
    ~Btree();                   // Destrutor
    void insert(int k);         // Insere uma chave k na arvore 
    void remove(int k);         // Remove uma chave k da arvore
    bool contains(int k);       // Devolve true se k estiver na arvore e false caso contrario
    void printKeysInOrder();    // Imprime as chaves da arvore em ordem simetrica
    void printNodesByLevels();  // Imprime as chaves por nivel
};

Btree::Btree(int d) {
    this->d = d;
    root = new Bnode(d, true); // Aloca memoria para root node
}

Btree::~Btree() {
    root = clear(root);
}

Bnode *Btree::clear(Bnode *node) {
    if(node->leaf == true) {
        delete node;
        return nullptr;
    }
    else {
        for(int i = 0; i <= node->n; i++) {
            node->c[i] = clear(node->c[i]);
        }
        delete node;
        return nullptr;
    }
}

void Btree::printKeysInOrder() { 
    root->printKeysInOrder();
}

void Btree::printNodesByLevels() {
    std::queue<Bnode*> fila;
    fila.push(root);
    int levelEnded = 1;
    while(!fila.empty()) {
        if(levelEnded == 0) {
            levelEnded = fila.size();
            std::cout << "\n" << std::endl;
        }
        Bnode *node = fila.front();
        fila.pop();
        std::cout << "[";
        int i = 0;
        for(; i < node->n; i++) {
            std::cout << node->key[i];
            if(i < node->n-1) 
                std::cout << ",";
            if(!node->leaf)
                fila.push(node->c[i]);
        }
        if(!node->leaf)
            fila.push(node->c[i]);
        std::cout << "] ";
        levelEnded--; 
    }
    std::cout << std::endl;
}

bool Btree::contains(int k) {
    int i;
    Bnode *node = root->search(k,i);
    return (node != nullptr);
}

void Btree::insert(int k) {
    // TODO
    Bnode * raiz = root;
    if(root->n==2*d -1){
        Bnode* s = new Bnode(d, false);
        root = s;
        s->setn(0);
        s->setcc(0, raiz);
        s->splitChild(0);
        s->insertNonFull(k);
    }else root->insertNonFull(k);
}

#endif