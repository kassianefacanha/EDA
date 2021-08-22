#ifndef AVL_H
#define AVL_H
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

// Definicao de dois tipos de dados
// Tkey - tipo da chave
// Tvalue - tipo do valor associado a chave
typedef int Tkey;
typedef std::string Tvalue;

/******************************************
 * Definicao do struct Node
 ******************************************/
struct Node {
    Tkey key;
    Tvalue value;
    int height;
    Node *left;
    Node *right;

    Node (Tkey k, Tvalue v, int h, Node *l, Node *r)
        : key(k), value(v), height(h), left(l), right(r)
        { }

    ~Node() { cout << "removido: " << key << endl; }
};

/****************************************
 *  Definicao da classe AVL
 ****************************************/
class AVL {
public:
    AVL();                            
    void add(Tkey k, Tvalue v);        
    bool contains(Tkey k, Tvalue *v);  
    void remove(Tkey k);                        
    void bshow();
    void inorder();
    ~AVL();
private:
    Node *root;
    Node *clear(Node *node);
    Node *contains(Node *node, Tkey k);
    void bshow(Node *node, std::string heranca);

    // Funcoes para insercao de nodes
    Node *add(Node *p, Tkey k, Tvalue v);
    int height(Node *node);
    int balance(Node *node);
    Node *rightRotation(Node *p);
    Node *leftRotation(Node *p);
    Node *fixup_node(Node *p, Tkey k);

    // Funcoes para remocao de nodes
    Node *remove(Node *node, Tkey k);
    Node *remove_successor(Node *root, Node *node);
    Node *fixup_deletion(Node *p);
    void inorder(Node *node);
};

/**************************************
 * Implementacao da classe AVL
 **************************************/
AVL::AVL() {
    root = nullptr;
}

AVL::~AVL() {
    root = clear(root);
}

Node *AVL::clear(Node *node) {
    if(node != nullptr) {
        node->left = clear(node->left);
        node->right = clear(node->right);
        delete node;
    }
    return nullptr;
}

int AVL::height(Node *node) {
    if(node == nullptr) 
        return 0;
    else 
        return node->height;
}

int AVL::balance(Node *node) {
    if(node == nullptr) 
        return 0;
    else 
        return height(node->right) - height(node->left);
}

bool AVL::contains(Tkey k, Tvalue *v) {
    Node *aux = contains(root, k);
    if(aux != nullptr) {
        *v = aux->value;
        return true;
    }
    return false;
}

Node *AVL::contains(Node *node, Tkey k) {
    if(node == nullptr) // arvore vazia
        return nullptr;
    if(k == node->key) // achamos o node
        return node;
    if(k < node->key) // vai para a esquerda
        return contains(node->left, k);
    else // vai para a direita
        return contains(node->right, k);
}

Node *AVL::rightRotation(Node *p) {
    Node *u = p->left;
    p->left = u->right;
    u->right = p;
    // atualiza altura dos nodes
    p->height = 1 + max(height(p->left),height(p->right));
    u->height = 1 + max(height(u->left),height(u->right));
    return u; // nova raiz
}

Node *AVL::leftRotation(Node *p) {
    Node *u = p->right;
    p->right = u->left;
    u->left = p;
    // atualiza altura dos nodes
    p->height = 1 + max(height(p->left),height(p->right));
    u->height = 1 + max(height(u->left),height(u->right));
    return u; // nova raiz
}

void AVL::add(Tkey k, Tvalue v) {
    root = add(root, k, v);
}

// Insere um node (k,v) na arvore enraizada no node p
Node *AVL::add(Node *p, Tkey k, Tvalue v) {
    if(p == nullptr) // subarvore vazia
        return new Node(k, v, 1, nullptr, nullptr);
    if(k == p->key) // chave repetida
        return p;
    if(k < p->key)
        p->left = add(p->left, k, v);
    else 
        p->right = add(p->right, k, v);
    
    // atualiza altura deste node ancestral p
    p->height = 1 + max(height(p->left),height(p->right));
    
    p = fixup_node(p, k); // regula o node p

    return p;
}

// Conserta o fator de balanceamento de um node p
Node *AVL::fixup_node(Node *p, Tkey k) {
    int bal = balance(p); // obtem balanco de p
    // Caso 1(a): rotacao direita
    if(bal < -1 && k < p->left->key)
        return rightRotation(p);
    // Caso 1(b): rotacao dupla direita
    else if(bal < -1 && k > p->left->key) {
        p->left = leftRotation(p->left);
        return rightRotation(p);
    }
    // Caso 2(a): rotacao esquerda
    else if(bal > 1 && k > p->right->key)
        return leftRotation(p);
    // Caso 2(b): rotacao dupla esquerda 
    else if(bal > 1 && k < p->right->key) {
        p->right = rightRotation(p->right);
        return leftRotation(p);
    }
    return p;
}

void AVL::bshow() {
    bshow(root, "");
}

void AVL::bshow(Node *node, std::string heranca) {
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

void AVL::remove(Tkey k) {
    root = remove(root, k);
}

Node *AVL::remove(Node *node, Tkey k) {
    if(node == nullptr) // node nao encontrado
        return nullptr;
    if(k < node->key) 
        node->left = remove(node->left, k);
    else if(k > node->key)
        node->right = remove(node->right, k);
    // encontramos no node
    else if(node->left == node->right) {
        delete node;
        return nullptr;
    }
    else if(!node->right || !node->left) {
        Node *child = node->left ? node->left : node->right;
        delete node;
        return child;
    } 
    else
        node->right = remove_successor(node, node->right);
    
    // Atualiza a altura do node e regula o node
    node = fixup_deletion(node); 
    return node;
}

Node *AVL::remove_successor(Node *root, Node *node) {
    if(node->left != nullptr)
        node->left = remove_successor(root, node->left);
    else {
        root->key = node->key;
        root->value = node->value;
        Node *aux = node->right;
        delete node;
        return aux;
    }
    // Atualiza a altura do node e regula o node
    node = fixup_deletion(node);
    return node;
}

Node *AVL::fixup_deletion(Node *node) {
    node->height = 1 + max(height(node->left), height(node->right));

    int bal = balance(node);

    // node pode estar desregulado, ha 4 casos a considerar
    if(bal > 1 && balance(node->right) >= 0) {
        return leftRotation(node);
    }
    else if(bal > 1 && balance(node->right) < 0) {
        node->right = rightRotation(node->right);
        return leftRotation(node);
    }
    else if(bal < -1 && balance(node->left) <= 0) {
        return rightRotation(node);
    }
    else if(bal < -1 && balance(node->left) > 0) { 
        node->left = leftRotation(node->left);
        return rightRotation(node);
    }
    return node;
}

void AVL::inorder() {
    inorder(root);
}

void AVL::inorder(Node *node) {
    if(node != nullptr) {
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }
}

#endif