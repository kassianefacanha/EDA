#ifndef BST_H
#define BST_H
#include <iostream>
#include <string>
#include <stack>
#include <climits>
using namespace std;

/*****************************
 * Definicao do struct Node
 *****************************/
struct Node {
    int key;
    Node *left;
    Node *right;
    Node *parent;

    // Construtor
    Node(int k, Node* l = nullptr, Node* r = nullptr, Node* p = nullptr) {
        this->key = k;
        this->left = l;
        this->right = r;
        this->parent = p;
    }
    // Destrutor
    ~Node() {
        cout << "Node removed: " << this->key << endl;
    }
};

/************************
 * Declaracao da classe
 ************************/
class BST {
public:
    BST();
    BST(int k);
    void bshow();
    bool add(int k);
    int minimum();           // ---> Implementar
    int maximum();           // ---> Implementar
    int predecessor(int k);  // ---> Implementar
    int successor(int k);    // ---> Implementar
    ~BST();
private:
    Node *root;
    void bshow(Node *node, std::string heranca);
    Node *minimum(Node *node);       // ---> Implementar
    Node *maximum(Node *node);       // ---> Implementar
    Node *successor(Node *node);     // ---> Implementar
    Node *predecessor(Node *node);     // ---> Implementar
    Node *clear(Node *node);
    Node *search(int k);
};

/*****************************
 * Implementacao da classe
 *****************************/
// Construtor 
BST::BST() {
    root = nullptr;
}

// Construtor 
BST::BST(int k) {
    root = new Node(k);
}

void BST::bshow(){
    bshow(root, "");
}

void BST::bshow(Node *node, std::string heranca) {
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow(node->right , heranca + "r");
    for(int i = 0; i < (int) heranca.size() - 1; i++)
        std::cout << (heranca[i] != heranca[i + 1] ? "│   " : "    ");
    if(heranca != "")
        std::cout << (heranca.back() == 'r' ? "┌───" : "└───");
    if(node == nullptr){
        std::cout << "#" << std::endl;
        return;
    }
    std::cout << node->key << std::endl;
    if(node != nullptr && (node->left != nullptr || node->right != nullptr))
        bshow(node->left, heranca + "l");
}

Node *BST::clear(Node *node) {
    if(node != nullptr) {
        node->left = clear(node->left);
        node->right = clear(node->right);
        delete node;
    }
    return nullptr;
}

BST::~BST() {
    root = clear(root);
}

// Funcao publica 'add'
// Esta funcao deve obrigatoriamente ser iterativa.
// Esta funcao adiciona um no com chave k na arvore e: 
// (1) devolve true em caso de sucesso;
// (2) devolve false caso contrario.
// Lembre-se que nao podem haver chaves repetidas na nossa arvore.
bool BST::add(int k) {
    //TODO: adicione aqui o codigo feito no exercicio anterior
       Node *curr = root;
    Node *parent = nullptr;
 
    if (root == nullptr){
        root = new Node(k);
        return true;
    }

    while (curr != nullptr) {
        parent = curr;
    if (curr->key == k) return false;
        if (k < curr->key) {
            curr = curr->left;
        }else {
            curr = curr->right;
        }
    }
 
    if (k < parent->key) {
        parent->left = new Node(k);
        parent->left-> parent = parent;
    }
    else {
        parent->right = new Node(k);
        parent->right-> parent = parent;
    }
    
   return true;
}

// Funcao privada 'search'
// Esta funcao devolve o ponteiro para o no que 
// contem a chave k se ela existir na arvore;
// caso contrario, devolve nullptr;
Node *BST::search(int k) {
    //TODO: adicione aqui o codigo feito no exercicio anterior
      Node *curr = root;

    while (curr != nullptr && curr->key != k) {
        
        if (k < curr->key) {
            curr = curr->left;
        }else {
            curr = curr->right;
        }
    }
return curr;
}

// Funcao publica (obrigatoriamente iterativa)
// Devolve o menor valor de chave da arvore.
int BST::minimum() {
    // TODO
return minimum(root)->key;
}


// Funcao privada (obrigatoriamente iterativa)
// Recebe como argumento o ponteiro para a raiz de uma arvore
// e devolve o ponteiro para o no com a menor chave na arvore.
// Se a arvore for vazia, devolve nullptr

Node *BST::minimum(Node *node) {
    // TODO
	if(node == NULL) return NULL;
    while(node->left != NULL)
        node = node->left;
    return node;
}

// Funcao publica (obrigatoriamente iterativa)
// Devolve o maior valor de chave da arvore
int BST::maximum() {
    // TODO
    return  maximum(root)-> key;
}

// Funcao privada (obrigatoriamente iterativa)
// Recebe como argumento o ponteiro para a raiz de uma arvore
// e devolve o ponteiro para o no com a maior chave na arvore.
// Se a arvore for vazia, devolve nullptr
Node *BST::maximum(Node *node) {
    // TODO
	if(node == NULL) return NULL;
    while(node->right != NULL)
        node = node->right;
    return node;
}

// Funcao publica (obrigatoriamente iterativa)
// Recebe um inteiro k como argumento e:
// (1) devolve INT_MAX se a chave k nao esta presente na arvore ou 
// se k esta presente na arvore mas nao tem sucessor
// (2) caso contrario, devolve o valor inteiro da 
// chave sucessora de k quando esta existe
int BST::successor(int k) {
    // TODO

  Node * aux;
  aux=successor(search(k));
  if (aux == NULL){
        return INT_MAX;
    } 
return aux->key;
  
}
// Funcao privada (obrigatoriamente iterativa)
// Recebe um ponteiro para um Node e:
// (1) devolve nullptr quando node nao tem sucessor; ou
// (2) caso contrario, devolve o ponteiro para o no sucessor de node.
Node *BST::successor(Node *node) {
    // TODO
    if (!node) return nullptr;
    return minimum(node->right);
}
// Funcao publica (obrigatoriamente iterativa)
// Recebe um inteiro k como argumento e:
// (1) devolve INT_MIN se a chave k nao esta presente na arvore ou 
// se k esta presente na arvore mas nao tem antecessor;
// (2) caso contrario, devolve o valor inteiro da chave 
// antecessora de k quando esta existe.
int BST::predecessor(int k) {
    // TODO
  Node * aux;
  aux=predecessor(search(k));
  if (aux == NULL){
        return INT_MIN; 
    } 
return aux->key;
 
}

// Funcao privada (obrigatoriamente iterativa)
// Recebe um ponteiro para um Node e:
// (1) devolve nullptr quando node nao tem antecessor; ou
// (2) caso contrario, devolve o ponteiro para o no antecessor de node.
Node *BST::predecessor(Node *node) {
    // TODO
    if (!node) return nullptr;
	if(node->left != nullptr) return maximum(node->left);
Node * y = node->parent;
while(y!=NULL && node == y->left){
	node = y;
	y = y->parent;
}
return y;
}
#endif 