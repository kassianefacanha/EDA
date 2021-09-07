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
    void makeSets(int x);
    void MCA(int u);
private:
    enum {white, black};
    struct Node { 
        int parent; 
        int rank; 
        int distance;
	    int color;
	    int ancestor;
	    std::vector<int> children;

	    Node() : distance(0), color(white), ancestor(-1) {}};
        struct mca { 
        int p, v;
        int ancestor;
        };
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

void DisjointSets::makeSets(int x)
{
	sets[x].parent = x; 
    sets[x].rank = 0;
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


void DisjointSets::MCA(int u) {
    std::vector<mca>& lcas;
	makeSets(u);
	sets[u].ancestor = u;
	std::vector<int>& children = sets[u].children;
	for (size_t i = 0, j = children.size(); i < j; i++) {
		int v = children[i];
		MCA(children[i]);
		unionSets(u, v);
		sets[findSet(u)].ancestor = u;
	}
	sets[u].color = black;
	for (size_t i = 0, j = children.size(); i < j; i++) {
	    mca& l = lcas[i];
		if (l.p == u && sets[l.v].color == black) {
			l.ancestor = sets[findSet(l.v)].ancestor;
            std::cout << "menor ancestral comum de" << l.p << " e " << l.v <<" é" << l.ancestor;
		}
		else if (l.v == u && sets[l.p].color == black) {
			l.ancestor = sets[findSet(l.p)].ancestor;
             std::cout << "menor ancestral comum de" << l.p << " e " << l.v <<" é" << l.ancestor;
		}
	}
}
#endif