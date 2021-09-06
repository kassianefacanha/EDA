#ifndef DSETS_H
#define DSETS_H
#include <vector>

/**
 * Implementation of the disjoint-sets data structure
 * using path compression and union by rank
 */
class DisjointSets {
public:
    explicit DisjointSets( int numElements );
    int findSet( int x );
    void unionSets( int x, int y );
private:
    struct Node { int parent; int rank; };
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
    if( sets[xroot].rank > sets[yroot].rank )
        sets[yroot].parent = xroot;
    else {
        sets[xroot].parent = yroot;
        if(sets[xroot].rank == sets[yroot].rank)
            ++sets[yroot].rank;
    }
}

#endif