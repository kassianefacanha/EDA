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
    virtual int m() = 0;

    virtual std::list<int>& neighbors(int v) = 0; 

    virtual std::list<Edge>& incidentEdges(int v) = 0;

    virtual void setEdgeWeight(int v1, int v2, int wgt) = 0;

    virtual void addEdge(int v1, int v2) = 0;

    virtual void delEdge(int v1, int v2) = 0;

    virtual bool isEdge(int v1, int v2) = 0;

    virtual int weight(int v1, int v2) = 0;

    virtual int getMark(int v) = 0;

    virtual void setMark(int v, int value) = 0;

    virtual bool colore(int vert, int color[]) = 0;
    
    virtual bool isBipartite() = 0;
};

class MGraph : public Graph{
private:
    int N;        
    int M;       
    int **matrix; 
    int *mark;    

    void checkVertex(int v){
        if (v < 0 || v > N - 1){
            throw runtime_error("Intervalo de valor de vertice invalido");
        }
    }

public:
    // Construtor
    MGraph(int n){
        if (n <= 0){
            throw runtime_error("Tamanho Invalido");
        }
        N = n;
        M = 0;
        mark = new int[n];
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
        delete[] mark;
        for (int i = 0; i < N; i++){
            delete[] matrix[i];
        }
        delete matrix;
    }

    int n(){
        return N;
    }
    int m(){
        return M;
    }

    list<int> &neighbors(int v){
        list<int> *lis = new list<int>();
        for (int i = 0; i < N; i++){
            if (matrix[v][i] != 0){
                lis->push_back(i);
            }
        }
        return *lis;
    }

    void setEdgeWeight(int v1, int v2, int wgt){
        if (wgt < 0){
            throw runtime_error("Peso negativo");
        }
        if (!isEdge(v1, v2)){
            ++M;
        }
        matrix[v1][v2] = wgt;
        matrix[v2][v1] = wgt;
    }

    void addEdge(int v1, int v2){
        setEdgeWeight(v1, v2, 1);
    }

    void delEdge(int v1, int v2){
        if (isEdge(v1, v2)){
            M--;
            matrix[v1][v2] = 0;
        }
    }

    bool isEdge(int v1, int v2){
        return (matrix[v1][v2] > 0);
    }

    int weight(int v1, int v2){
        if (isEdge(v1, v2)){
            return matrix[v1][v2];
        }
        else{
            return 0;
        }
    }

    int getMark(int v){
        return mark[v];
    }


    void setMark(int v, int value){
        checkVertex(v);
        mark[v] = value;
    }

    list<Edge> &incidentEdges(int v){
        list<Edge> *lis = new list<Edge>();
        for (int i = 0; i < N; i++){
            if (matrix[v][i] != 0){
                lis->push_back(Edge(i, matrix[v][i]));
            }
        }
        return *lis;
    }

    bool isBipartite(){
        int color[N];
        for (int i = 0; i < N; ++i){
            color[i] = -1;
        }
        

        for (int i = 0; i < N; i++){
            if (color[i] == -1){
                if (colore(i, color) == false){
                    cout << "NAO" << endl;
                    return false;
                }
            }
        }

        
        cout << "SIM" << endl;
        for (int i = 0; i < N; i++){
            if (color[i] == 1){
                cout << i << " R" << endl;
            }
            else{
                cout << i << " B" << endl;
            }
        }

        return true;
    }


    bool colore(int vert, int color[]){
        color[vert] = 1;
        
        queue<int> q;
        q.push(vert);

       
        while (!q.empty()){
            
            int u = q.front();
            q.pop();

          
            if (isEdge(u, u)){
                return false;
            }
            
          
            for (int v = 0; v < N; ++v){
               
                if (isEdge(u, v) && color[v] == -1){
                    color[v] = 1 - color[u];
                    q.push(v);
                }

               
                else if (isEdge(u, v) && color[v] == color[u]){
                    return false;
                }
            }
        }

        return true;
    }
};

#endif