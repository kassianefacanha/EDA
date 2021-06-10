#ifndef BST_H
#define BST_H
#include <iostream>
#include <string>
using namespace std;

/***********************************
 * Definicao do struct Node
 ***********************************/
struct Node {
    int key;
    Node *left;
    Node *right;
    Node *parent;

    Node(int k, Node *l = nullptr, Node *r = nullptr, Node *p = nullptr)
        : key(k), left(l), right(r), parent(p)
        { }

    ~Node() {
        cout << "Node removed: " << this->key << endl;
    }
};

/***********************************
 * Declaracao da classe
 ***********************************/
class BST {
public:
    BST();
    BST(int k);
    void bshow();
    bool add(int k); 
    void preorder();
    void remove(int key);   // ---> Implementar
    ~BST();
private:
    Node *root;
    void bshow(Node *node, std::string heranca);
    Node *clear(Node *node); 
    void preorder(Node *node);
};

/************************************
 * Implementacao da classe
 ************************************/
BST::BST() {
    root = nullptr;
}

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

// Percorre os nos da arvore em pre-ordem, imprimindo os pais
void BST::preorder() {
    preorder(root);
}

void BST::preorder(Node *node) {
    if(node != nullptr) {
        if(node->parent != nullptr)
            cout << "pai de " << node->key << " = " << node->parent->key << endl;
        preorder(node->left);
        preorder(node->right);
    }
}

// Funcao publica 'add'
// Esta funcao deve obrigatoriamente ser iterativa.
// Esta funcao adiciona um no com chave k na arvore e: 
// (1) devolve true em caso de sucesso;
// (2) devolve false caso contrario.
// Lembre-se que nao podem haver chaves repetidas na nossa arvore.
bool BST::add(int k) {
    // TODO: adicione aqui o codigo feito no primeiro exercicio
    
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

// Funcao publica iterativa 'remove'
// Recebe como entrada uma chave e a remove da arvore binaria de busca
// de modo que a arvore resultante continua binaria de busca
// O algoritmo de remocao aqui deve seguir o que foi visto em sala.
void BST::remove(int k) {

    Node* curr = root;
    Node* prev = NULL;

    while (curr != NULL && curr->key != k) {
        prev = curr;
        if (k < curr->key)
            curr = curr->left;
        else
            curr = curr->right;
    }
    if (curr == NULL) {
        cout << "Key não encontrada" ;
    }
 
    if (curr->left == NULL || curr->right == NULL) {
        Node* newCurr;
        if (curr->left == NULL)
            newCurr = curr->right;
        else
            newCurr = curr->left;

        if (curr == prev->left)
            prev->left = newCurr;
        else
            prev->right = newCurr;
	if(newCurr != NULL) newCurr->parent = prev;

        delete(curr);
    }
 
    else {
         Node* p = NULL;
        Node* temp;
        if(curr->right != NULL){
		temp = curr->right;
        	while (temp->left != NULL) {
           	 p = temp;
            	temp = temp->left;
        	}
 }else{
	temp = curr->parent;
	p = curr;
	while(temp != NULL && p == temp->right){
	p = temp;
	temp = temp->parent;
}
}
        if (temp->parent != NULL)
            temp->parent->left = temp->right;
        else
            curr->right = temp->right;
 
        int troca = temp->key;
	temp->key = curr->key;
	curr->key=troca; 
        delete(temp);
    }
    
}
#endif 