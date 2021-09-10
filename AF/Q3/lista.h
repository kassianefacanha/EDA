#ifndef LISTA_H
#define LISTA_H
#include <iostream>
#include <list>

using namespace std;
class LGrafo{
    private: int N;
    list<int> *lista;   

    public:LGrafo(int n){
        N = n;
        lista = new list<int> [N];

    }
    void addAresta(int a, int b){
        lista[a].push_back(b);
    }
    LGrafo *GTransposto(){
          LGrafo *GrafoT = new LGrafo(N);
          for(int i = 0; i < N; i++){
              for(const auto& p :  lista[i]){
                GrafoT->addAresta(p,i);
              }
          }
        return GrafoT;
    }

      void print(){
        for (int i = 0; i < N; i++){
            for(const auto& p : lista[i]){
                   std::cout << i << " " << p << std::endl;
                }
        }
    }

};
#endif