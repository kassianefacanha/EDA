#ifndef DSETS_H
#define DSETS_H
#include <vector>
#include <iostream>
#include <string>
#include <unordered_map>
#include <list>

/**
 * Implementation of the disjoint-sets data structure
 * using path compression and union by rank
 */
class DisjointSets {
public:
    explicit DisjointSets( int numElements );
    int findSet( int x );
    void unionSets( int x, int y );
    void printSet( int elem );
private:
    struct Node { int parent; int rank; int prox;};
    std::vector<Node> sets;
};

/**
 * Construct the disjoint sets object.
 * numElements is the initial number of disjoint sets.
 */ 
DisjointSets::DisjointSets( int numElements ) {
    sets.resize( numElements );
    for( int i = 0; i < numElements; ++i ) {
        sets[i].parent = i;
        sets[i].rank = 1;
        sets[i].prox = i;
    }
}

/**
 * Performs a find-Set with path compression.
 * Returns the representative of the set containing x.
 */
int DisjointSets::findSet( int x ) {
    if ( sets[x].parent != x )
        sets[x].parent = findSet( sets[x].parent );
    return sets[x].parent;
}

/**
 * Union of two disjoint sets using union by rank
 */
void DisjointSets::unionSets( int x, int y ) {
    int xroot = findSet(x);
    int yroot = findSet(y);
    if( sets[xroot].rank > sets[yroot].rank ){
        sets[yroot].parent = xroot;
        int temp = sets[xroot].prox;
        sets[xroot].prox = sets[yroot].prox;
        sets[yroot].prox = temp;
    }
    else {
        sets[xroot].parent = yroot;
        int temp = sets[yroot].prox;
        sets[yroot].prox = sets[xroot].prox;
        sets[xroot].prox = temp;
        if(sets[xroot].rank == sets[yroot].rank)
            ++sets[yroot].rank;
    }
}

void DisjointSets::printSet(int elem){
        int x = findSet(elem), y;
        y=x;
        std::cout << "{ ";
        std::cout << x << " ";
        x = sets[x].prox;
        while(y != x) {
            std::cout << x << " ";
            x = sets[x].prox;
        }
        std::cout << "}"<<std::endl;;


}

#endif