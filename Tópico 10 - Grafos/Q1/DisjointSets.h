#ifndef DS_H_2021
#define DS_H_2021
#include <iostream>
#include <string>
#include <unordered_map>
#include <list>

struct Representative;

struct Node {
    string element; // guarda o valor do elemento
    Node *next; // ponteiro para o proximo node na lista
    Representative *repr; // ponteiro para o representante
};

struct Representative {
    Node *head; // ponteiro para o primeiro node na lista
    Node *tail; // ponteiro para o ultimo node da lista
    string size; // numero de elementos na lista
};

// Classe que implementa conjuntos disjuntos usando 
// listas encadeadas e heuristica de uniao ponderada
class DisjointSets {
    
private:
    std::unordered_map<string, Node*> nodeAddress; // tabela hash
    
    
public:
    // funcao Make-Set
    // cria um conjunto somente com o elemento 'elem' do tipo string.
    // Um conjunto eh composto por um objeto Representative e um objeto Node.
    // Um par (elem, Node*) deve ser armazenado na tabela hash 'nodeAddress'
    void makeset(const string& elem); 

    // funcao Find
    // Devolve um ponteiro para o representante de 'elem'
    // A fim de encontrar o Node que contem 'elem', deve ser usada a tabela hash 'nodeAddress'
    Representative* find(const string& elem);

    // funcao Union
    // Se 'elem1' e 'elem2' nao estiverem no mesmo conjunto,
    // entao os seus conjuntos serao unidos. Eles terao um mesmo representante.
    // Supoe que esta funcao eh sempre chamada para dois elementos em conjuntos disjuntos
    // Um dos Representative não será mais usado e deve ser deletado
    void unionSets(const string& elem1, const string& elem2);
    
    // funcao prstringSet
    // imprime na tela todos os elementos que estao no mesmo conjunto que 'elem'
    // no formato: { e1 e2 e3 ... en }
    // onde cada elemento eh separado por espacos em branco
    void prstringSet(const string& elem);
    
    // Destrutor
    ~DisjointSets() {
        // percorre todos os elementos da tabela hash e libera todos os 
        // elementos do tipo Node que foram alocados dinamicamente.
        // A tabela hash em si nao precisa ser liberada ja que ela foi 
        // alocada estaticamente pelo proprio compilador. Ele se encarrega de libera-la.
        // Note que essa implementacao tem um problema pois os elementos do tipo
        // Representative nao sao liberados aqui no destrutor. Isso deve ser consertado futuramente.
        // Voce consegue visualizar alguma solucao?
        for(auto it = nodeAddress.begin(); it != nodeAddress.end(); ++it) {
            delete it->second;
        }
    }
    
};

void DisjointSets::makeset(const string& elem){
    
    Representative *newRepr = new Representative;
  
    newRepr->head = new Node;
    newRepr->tail = newRepr->head;
    nodeAddress[elem] = newRepr->head;
    newRepr->head->element = elem;
    newRepr->head->repr = newRepr;
    newRepr->head->next = NULL;
}

Representative *DisjointSets::find(const string& elem) {
    Node *newNode = nodeAddress[elem];
    return (newNode->repr);
}

void DisjointSets::unionSets(const string& elem1, const string& elem2) {

    
        Representative *vol1 = find(elem1); 
    	Representative *vol2 = find(elem2);
    	  Node *newN = vol2->head;
        while (newN != 0){
            newN->repr =vol1;
            newN = newN->next;
    
      
        (vol1->tail)->next = vol2->head;
        vol1->tail = vol2->tail;
      
        delete vol2;
  
  
}


#endif