#ifndef MATRIZ_H
#define MATRIZ_H

class MGrafo{
   private: 
    int N;
    int **M;

    public:MGrafo(int n){
        N = n;
        M = new int *[n];
        for (int i = 0; i < n; i++){
            M[i] = new int[n];
            for(int j = 0; j < n ; j++){
                M[i][j]= 0;
            }
        }
    }

    void addAresta(int a, int b){
         M[a][b]= 1;
    }

    MGrafo *GTransposto(){
        MGrafo *GrafoT = new MGrafo(N);
         for (int i = 0; i < N; i++){
            for(int j = 0; j < N ; j++){
                if(M[i][j] == 1){
                    GrafoT->addAresta(j,i);
                }
               
            }
        }
        return GrafoT;

    }
    void print(){
        for (int i = 0; i < N; i++){
            for(int j = 0; j < N ; j++){
                if(M[i][j] == 1){
                   std::cout << i << " " << j << std::endl;
                }
            }
        }
    }
     

};

#endif