#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "DisjointSets.h"

using namespace std;

int main() 
{
	int n;
	cin >> n;
	std::vector<mca> mcas(n);
	DisjointSets *p = new DisjointSets(n);
		for (int i = 0; i < n; i++) {
			int prim, seg;
			cin >> prim;
			cin >> seg;
			prim--, seg--;
			mcas[i].p = prim; mcas[i].v = seg;
		}
	
	int u;
	while(true){
cin>>u;
p->MCA(u, mcas);

	}
		

	return 0;

}