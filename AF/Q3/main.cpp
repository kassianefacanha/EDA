#include <iostream>
#include "grafo.h"
#include <sstream>
#include <string>
#include <list>


using namespace std;


int main(){
    Graph *grafo, *transposto;
    int d, key1, key2;
    cin >> d;
    while(true){
        grafo = new MGraph(d); //MATRIZ
       grafo = new LGraph(d);//LISTA
        cin >>key1;
        cin >>key2;
        while(key1!=0 || key2!=0){
            grafo->addEdge(key1,key2);
            cin >>key1;
            cin.ignore();
            cin >>key2;
            cin.ignore();
        }
        transposto = grafo->transpose();
        transposto->print();
        delete grafo;
        delete transposto; 
        cin >> d;
        if(d==0) return 0;             
    }
    return 0;
}