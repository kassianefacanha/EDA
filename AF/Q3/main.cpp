#include <iostream>
#include "matriz.h"
#include "lista.h"

using namespace std;

int main() {

    std::cout << "Digite 1 para Matriz " << std::endl;
     std::cout << "Digite 2 para Lista " << std::endl;
        int n;
        cin >> n;
     if(n==1){
        int n2;
        cin >> n2;
        MGrafo *grafo = new MGrafo(n2);
         MGrafo *grafoT ; 
         int a, b;
            cin >> a;
            cin >> b;
        while(a != 0 || b != 0 ){
            grafo->addAresta(a, b);
            cin >> a;
            cin >> b;
           

        }

    std::cout << "GRAFO TRANSPOSTO " << std::endl;
     grafoT=grafo->GTransposto();   
     grafoT->print();
	
    
    }else if(n==2){
          int n2;
        cin >> n2;
        LGrafo *grafo = new LGrafo(n2);
        LGrafo *grafoT;
         int a, b;
            cin >> a;
            cin >> b;
        while(a != 0 || b != 0 ){
            grafo->addAresta(a, b);
            cin >> a;
            cin >> b;
           

        }
    std::cout << "GRAFO TRANSPOSTO " << std::endl;
     grafoT=grafo->GTransposto();   
     grafoT->print();
	


     }else{
        std::cout << "Numero invalido" ;
        return 0;


     }
    
	}
		
