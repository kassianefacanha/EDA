#include <iostream>
#include <sstream>
#include "bnode.h"
#include "btree.h"

using namespace std;

int main() {
    int d, key;
    string outkeys, inkeys;

    cin >> d;
    cin.ignore();

    Btree arv(d);

    getline(cin, inkeys);
    
    getline(cin, outkeys);

    stringstream ss { inkeys };

    while(ss >> key) arv.insert(key);

    arv.printNodesByLevels();

    cout << "--------------" << endl;

    stringstream rr { outkeys };

    while(rr >> key) arv.remove(key);

    arv.printNodesByLevels();
    
    return 0;
}