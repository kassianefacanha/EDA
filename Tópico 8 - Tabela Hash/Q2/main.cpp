// Este arquivo ja esta finalizado. Nao mexa nele
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "PriorityQueue.h"
using namespace std;

int main() {
    PriorityQueue<double> fila(20);

    while(true) {
		string cmd;
		getline(cin, cmd);

		stringstream ss{ cmd };
		vector<string> tokens;
		string buffer;

		while(ss >> buffer) 
			tokens.push_back(buffer);
		
		// exit
		if(tokens[0] == "exit") {
			cout << "saindo..." << endl;
			break;
		}
		// push a1 a2 ... an
		else if(tokens[0] == "push") {
			for(size_t i = 1; i < tokens.size(); ++i) 
                fila.push( std::stof(tokens[i]) );
		}
		// pop
		else if(tokens[0] == "pop") {
			fila.pop();
		}
		// top
		else if(tokens[0] == "top") {
			cout << fila.top() << endl;
		}
		// size
		else if(tokens[0] == "size") {
			cout << "size: " << fila.size() << endl;
		}
		// empty
		else if(tokens[0] == "empty") {
			cout << "is empty? " << boolalpha << fila.empty() << endl;
		}
		// createNewHeap a1 a2 ... an
		else if(tokens[0] == "createNewHeap") {
			vector<double> arr;
			for(size_t i = 1; i < tokens.size(); ++i) 
                arr.push_back( std::stof(tokens[i]) );
            PriorityQueue<double> fila2(arr);
            while(!fila2.empty()) {
                cout << fila2.top() << " ";
                fila2.pop();
            }
		}
	}

	return 0;
}