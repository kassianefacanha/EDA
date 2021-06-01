#include <iostream>
#include <string>
#include <sstream>
#include "bst.h"
using namespace std;

int main()
{
	BST arv;
	string addkeys, remkeys;
	int value;
    
	getline(cin, addkeys); // ler as chaves a serem adicionadas

	stringstream ss { addkeys };

	while(ss >> value) 
		arv.add(value);

    getline(cin, remkeys); // ler as chaves a serem removidar
	
    stringstream sss { remkeys };

	while(sss >> value) {
		arv.remove(value);
        arv.preorder();
	}

	return 0;
}