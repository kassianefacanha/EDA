#include <iostream>
#include "grafo.h"
#include "grafo.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <list>
#include <queue>

using namespace std;


void trataDado(string dados, Graph *grafo);

int main(){
    Graph *grafo;
    fstream myfile;
    string line;
    myfile.open("grafos.txt");
   
    getline(myfile, line);
    int n = stoi(line);
    grafo = new MGraph(n);

    while (myfile.good()){ 
        getline(myfile, line);
        if (line != "") { 
            if (line != "0 0"){
                trataDado(line, grafo);
            }
            else{
                grafo->isBipartite();
                grafo->~Graph();
                getline(myfile, line);
                int n = stoi(line);
                if (n != 0){
                    grafo = new MGraph(n);
                }
                else{
                    getline(myfile, line);
                }
            }
        }
    }
    return 0;
}


void trataDado(string dados, Graph *grafo){

    int n1, n2;
    stringstream aux;
    aux << dados; 
    getline(aux, dados, ' '); 
    n1 = stoi(dados); 
    getline(aux, dados, '\n'); 
    n2 = stoi(dados); 
    
    grafo->addEdge(n1, n2);
    grafo->addEdge(n2, n1); 
}