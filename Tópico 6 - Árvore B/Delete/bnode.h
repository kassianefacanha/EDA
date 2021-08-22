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

    // Funcao que concatena o filho c[i] e o filho c[i+1].
    // A soma do numero de chaves de c[i] e c[i+1] eh menor que 2d-1.
    // Apos essa operacao ser realizada, o node c[i] fica como no maximo 2d-1 chaves 
    // e o node c[i+1] eh liberado (deleted). 
    // Apos essa operacao, a chave key[i] que separava c[i] e c[i+1] no pai, deixa de
    // existir no pai e passa a fazer parte do filho c[i]
    // Com isso, o pai deve ter seus atributos também atualizados.
    void concatenate(int i);

    // Funcao que redistribui as chaves do filho c[a] para o filho c[b] deste node
    // O filho c[b] tem menos do que d-1 chaves e, apos esta operacao, passa a ter
    // exatamente uma chave a mais e o filho c[a] passa a ter uma chave a menos.
    // Alem disso, a chave que separa estes dois irmaos adjacentes tambem eh modificada,
    // porem, o pai fica com a mesma quantidade de chaves. Essa operacao nao eh propagavel.
    // ja que o numero de chaves do pai permanece o mesmo.
    void redistributeFromTo(int a, int b);

    // Recebe como argumento o valor de chave k e remove esta chave da 
    // arvore enraizada neste node se e somente se a chave estiver na arvore;
    // caso contrario, nao faz nada e a arvore permanece como estava.
    // Esta funcao deve ajustar os nos que foram visitados toda vez que for necessario, 
    // pois a arvore deve permanecer uma arvore-B apos cada remocao.
    // Ou seja, essa funcao deve fazer o rebalanceamento do no visitado.
    void removeKey(int k);

    // Esta funcao eh chamada dentro da funcao "removeKey(int k)" descrita acima.
    // Recebe como entrada um ponteiro para um ancestral 'node' tal que
    // node->key[indexKey] eh a chave que queremos remover da arvore.
    // Porem, quando esta funcao for chamada, sabemos que 'node' nao eh um no folha.
    // Portanto, esta funcao encontrara a chave Z sucessora da chave node->key[indexKey], 
    // copiara a chave Z em node->key[indexKey] e, entao, removera a chave Z do no 
    // original ao qual ela pertencia. 
    // Tanto esta funcao quanto a funcao removeKey(int k) devem ajustar os nos que foram
    // visitados toda vez que for necessario.
    // O parametro 'rightChild' eh o ponteiro para o filho direito da chave 'node->key[indexKey]'
    void removeSuccessor(Bnode *node, int indexKey, Bnode *rightChild);

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
    // TODO - Copie da atividade anterior
    int i=1;
    while(i<=n && k > key[i-1]) i++;
    if(i<= n && k == key[i-1]) {
        index = i-1;
        return this;
    }
    else if(leaf) return nullptr;
    return c[i-1]->search(k, index);
}

void Bnode::splitChild(int i) 
{
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
    // TODO - copie da atividade anterior
}

void Bnode::insertNonFull(int k) 
{
    // TODO - copie da atividade anterior
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

void Bnode::concatenate(int i) 
{
    // TODO
    Bnode *p = c[i];
    Bnode *q = c[i+1];
    p->setkey(p->getn(), key[i]);
    for(int j=0; j<q->getn(); j++){
        p->setkey(p->getn()+1+j, q->getkey(j));
    }
    for(int j=0;j<=q->getn();j++)
        p->setcc(p->getn()+1+j, q->getcc(j));
    p->setn(p->getn()+q->getn()+1);
    q->setn(0);
    delete q;
    for(int j=i; j<=n-2; j++)
        key[j] = key[j+1];
    for(int j=i+1; j<=n-1;j++){
        c[j] = c[j+1];
    }
    n--;
}

void Bnode::redistributeFromTo(int a, int b) 
{
    // TODO
    if(a < b){
        Bnode * l=c[a];
        Bnode * r=c[b];
        for(int j=r->getn(); j>1; j--)
            r->setkey(j, r->getkey(j-1));
        r->setkey(0, key[a]);
        for(int j=r->getn();j>1;j--)
            r->setcc(j, r->getcc(j-1));
        r->setcc(0, l->getcc(l->getn()));
        r->setn(r->getn()+1);
        key[a]=l->getkey(l->getn()-1);
        l->setn(l->getn()-1);
    }else{
        Bnode *r = c[a];
        Bnode *l = c[b];
        l->setkey(l->getn(), key[a-1]);
        l->setcc(l->getn()+1, r->getcc(0));
        l->setn(l->getn()+1);
        key[a-1] = r->getkey(0);
        for(int j=0; j<r->getn()-2; j++)
            r->setkey(j, r->getkey(j+1));
        for(int j=0;j<r->getn()-1;j++)
            r->setcc(j, r->getcc(j+1));
        r->setn(r->getn()-1);
    }
}

void Bnode::removeKey(int k) 
{    
    // TODO
    int a=0;
    if(leaf){
        for(int i=0; i<n; i++)
            if(key[i] == k){
                while(i<n-1){
                    key[i]=key[i+1];
                    i++;
                }
                n--;
            }
    }else{
        int i=0;
        while(i<n && key[i] < k)
            i++;
        if(i!=n && key[i]==k){
            removeSuccessor(this, i, c[i+1]);
            a=1;
        }
        else c[i]->removeKey(k);
        if(c[i+a]->getn() < d-1){
            if(i+1+a <= n && c[i+1+a]->getn() > d-1)
                redistributeFromTo(i+1+a, i+a);
            else if(a==1 && i >=0 && c[i]->getn() > d-1)
                redistributeFromTo(i, i+1);
            else if(i-1 >= 0 && c[i-1]->getn() > d-1)
                redistributeFromTo(i-1, i);
            else if(i+1+a<=n)
                concatenate(i+a);
            else concatenate(i+a-1);
        }
    }
}

void Bnode::removeSuccessor(Bnode *node, int indexKey, Bnode *child) 
{
    // TODO
    if(child->getleaf()){
        node->setkey(indexKey, child->getkey(0));
        for(int i=0;i<child->getn()-1; i++)
            child->setkey(i, child->getkey(i+1));
        child->setn(child->getn()-1);
    }
    else removeSuccessor(node, indexKey, child->getcc(0));

    //parte em que usa concat e redistrue
    if((!child->getleaf()) && child->getcc(0)->getn() < d-1){
        if(d >=2 && child->getcc(1)->getn() > d -1)
            child->redistributeFromTo(1,0);
        else child->concatenate(0);
    }
}

#endif