#ifndef BNODE_H
#define BNODE_H
#include <iostream>

class Bnode {
private:
    int d;          // grau minimo
    int n;          // numero atual de chaves
    int *key;       // vetor de chaves
    Bnode **c;      // vetor de ponteiros para filhos
    bool leaf;      // 'true' se o node eh uma folha, 'false' caso contrario

public:
    // Construtor
    Bnode(int d, bool leaf);

    // Destrutor
    ~Bnode();
    int getd(){
        return d;
    }
    int getn(){
        return n;
    }
    int getkey(int i){
        return key[i];
    }
    Bnode* getcc(int i){
        return c[i];
    }
    bool getleaf(){
        return leaf;
    }
    void setleaf(bool l){
        leaf = l;
    }
    void setn(int m){
        n = m;
    }
    void setcc(int i, Bnode * node){
        c[i] = node;
    }
    void setkey(int i, int j){
        key[i] = j;
    }
    // Funcao que busca a chave k na subarvore 
    // enraizada neste no. Se a chave existir, retorna
    // o ponteiro para o no e o valor do indice da chave
    // na variavel index. Caso contrario, retorna nullptr
    // e o valor de index eh indefinido.
    Bnode *search(int k, int& index);

    // Imprime todas as chaves da arvore enraizada neste node
    void printKeysInOrder();

    // Funcao que divide o filho c[i] deste node.  
    // O node apontado por c[i] deve estar cheio 
    // quando esta funcao eh chamada.
    void splitChild(int i);

    // Funcao que insere uma nova chave na subarvore 
    // enraizada neste node. Supomos que o node nao esta 
    // cheio quando esta funcao eh chamada 
    void insertNonFull(int k);   

    // Faz Btree uma classe amiga desta, para que possamos acessar
    // os membros privados desta classe nas funções de Btree. 
    friend class Btree; 
};

Bnode::Bnode(int d, bool leaf) {
    this->d = d;            // grau minimo do node
    this->leaf = leaf;      // indica se node eh folha
    n = 0;                  // no inicio o node nao tem chaves
    key = new int[2*d - 1]; // o node pode ter no maximo 2d-1 chaves
    c = new Bnode*[2*d];    // o node pode ter no maximo 2d filhos
}

Bnode::~Bnode() {
    delete[] key;
    delete[] c;
}

void Bnode::printKeysInOrder() { 
    int i;
    for (i = 0; i < n; i++) { 
        // Se este node nao for folha, entao, antes de imprimir key[i], 
        // imprima a subarvore enraizada no filho c[i]. 
        if (leaf == false) 
            c[i]->printKeysInOrder();
        std::cout << " " << key[i]; 
    } 
  
    // Imprima a subarvore enraizada em c[n]  
    if (leaf == false) 
        c[i]->printKeysInOrder(); 
} 

Bnode *Bnode::search(int k, int& index) {
    // TODO
    int i=1;
    while(i<=n && k > key[i-1]) i++;
    if(i<= n && k == key[i-1]) {
        index = i-1;
        return this;
    }
    else if(leaf) return nullptr;
    return c[i-1]->search(k, index);
}


void Bnode::splitChild(int i) {
    // TODO
    Bnode * y = c[i];
    Bnode * z = new Bnode(d,y->getleaf());  //considero que o i vai variar de 0 até no numero filhos -1 
    z->setn(d-1);
    for(int j=0; j<d-1; j++)
        z->setkey(j, y->getkey(j+d));
    if(!y->getleaf())
        for(int j=0; j<d;j++)
            z->setcc(j, y->getcc(j+d));
    y->setn(d-1);
    for(int j = n+1; j > i+1; j--)
        c[j] = c[j-1];
    c[i+1] = z;
    for(int j = n; j>i;j--)
        key[j] = key[j-1];
    key[i] = y->getkey(d-1);
    n++;
}

void Bnode::insertNonFull(int k) {
    // TODO
    int i = n;
    if(leaf){
        while(i > 0 && k < key[i-1]){
            key[i] = key[i-1];
            i--;
        }
        key[i] = k;
        n++;
    }else{
        while(i>0 && k < key[i-1])
            i--;
        i++;
        if(c[i-1]->getn() == 2*d-1){
            splitChild(i-1);
            if(k > key[i-1])
                i++;
        }
        c[i-1]->insertNonFull(k);
    }

}

#endif