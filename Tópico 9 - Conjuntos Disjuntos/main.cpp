#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "DisjointSets.h"

using namespace std;

int main() 
{
	DisjointSets p;
	
	int itr = 0;
	while(true) {
		string line, word;
		getline(cin, line);
		stringstream ss { line };
		vector<string> tokens;
        
		// pegando valor
		while(ss >> word)
			tokens.push_back(word);
		
		// makeset
		for(size_t i = 1; i < tokens.size(); ++i)
			p.makeset( std::stoi(tokens[i]) );	
		
		// unions
		if(itr >= 12){
			int u1 = std::stoi(tokens[1]);
			int u2 = std::stoi(tokens[2]);
			p.unionSets(u1,u2);		    
			
			// finds
    		int e1 = std::stoi(tokens[1]);
    		int e2 = std::stoi(tokens[2]);
    		if(p.find(e1) == p.find(e2)) 
    			cout << " SIM" << endl;
    		else 
    			cout<< " NAO" << endl;
		}
		
		itr++;
		
	}

	return 0;
}