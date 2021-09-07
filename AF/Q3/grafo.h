#ifndef Grafo_h
#define Grafo_h
#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <queue>

using namespace std;

class Edge {
private:
    int vertex; 
    int weight;
public:
    Edge() { vertex = -1; weight = -1; }
    explicit Edge(int v, int w) { vertex = v; weight = w; }
    int getVertex() const { return vertex; }
    int getWeight() const { return weight; }
    void setVertex(int v) { vertex = v; }
    void setWeight(int w) { weight = w; }
};


class Graph {
public:
    Graph() {} 
    virtual ~Graph() {} 

    virtual int n() = 0;

    virtual void addEdge(int v1, int v2) = 0;

    virtual void print() =0;

    virtual Graph * transpose()=0;


};

class MGraph : public Graph{
private:
    int N;        
    int M;       
    int **matrix;    

    void checkVertex(int v){
        if (v < 0 || v > N - 1){
               cout << "Intervalo invalido"<< endl;
        }
    }

public:
    // Construtor
    MGraph(int n){
        if (n <= 0){
              cout << "Tamanho invalido"<< endl;
        }
        N = n;
        matrix = new int *[n];
        for (int i = 0; i <= n - 1; i++){
            matrix[i] = new int[n];
        }

        for (int i = 0; i <= n - 1; i++){
            for (int j = 0; j <= n - 1; j++){
                matrix[i][j] = 0;
            }
        }
    }

   
    ~MGraph(){
        for (int i = 0; i < N; i++){
            delete[] matrix[i];
        }
        delete matrix;
    }

    int n(){
        return N;
    }
    void addEdge(int v1, int v2){
        matrix[v1][v2] = 1;
    }

    Graph * transpose(){
        Graph * transposto = new MGraph(N);

        for(int i=0; i<N; i++){
            for(int j=0;j<N;j++)
                if(matrix[i][j]==1)
                transposto->addEdge(j,i);
        }
        return transposto;
    }
    void print(){
        for(int i=0; i< N; i++){
            for(int j=0;j<N;j++)
                if(matrix[i][j]==1) cout<<i<< " "<<j<<endl;
        }
    }
};

class LGraph : public Graph {
private:
    int N; 				
	list<int> *liste;

public:
    explicit LGraph(int n) {
		this->N = n; 				
		liste = new list<int>[N]; 	
	}
     ~LGraph() /*override*/ {
		  delete[] liste;
	}
    int n(){
        return N;
    }
    void addEdge(int v1, int v2){
        liste[v1].push_back(v2);
    }
    Graph * transpose(){
        Graph * transposto = new LGraph(N);
        list<int>::iterator it;

        for(int i=0; i<N; i++){
            for(it = liste[i].begin(); it !=liste[i].end();it++)
                transposto->addEdge(*it,i);
        }
        return transposto;
    }
    void print(){
        list<int>::iterator it;
         for(int i=0; i<N; i++){
            for(it = liste[i].begin(); it !=liste[i].end();it++)
                cout<<i << " "<<*it <<endl;
        }
    }

};

#endif