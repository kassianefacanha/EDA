/******************************************************
 * Este arquivo já está implementado. Nao mexa nele
 ******************************************************/
#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include "bnode.h"
#include "btree.h"

using namespace std;

int main() {
    int grau; // grau minimo da arvore B
    int chave;
    string linha;

    cin >> grau; // ler o grau 
    cin.ignore();
    getline(cin, linha); // ler uma linha de texto contendo todas as chaves a serem inseridas

    stringstream ss { linha };

    Btree arv(grau); // cria arvore B vazia

    while(ss >> chave)
        arv.insert(chave); // insere chaves na arvore B

    arv.printNodesByLevels(); // imprime os nodes por nivel
    
    return 0;
}