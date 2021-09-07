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
	DisjointSets *p = new DisjointSets(n);

	while(true) {
		int pri, seg;
		cin >> pri;
		cin >> seg;
		if(pri == 0 && seg == 0) break;
		p->unionSets(pri, seg);	    	
	}
	// PRINT
	int u;
	while(cin>>u)
		p->printSet(u);

	return 0;
} 