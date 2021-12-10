#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <set>
#include <vector>

#include "DataLine.h"
#include "HashFunctionG.h"
#include "HashFunctionH.h"

using namespace std;

class HashTable {
    class HashItem {
    public:
        unsigned g;
        DataLine * addr;
    };
public:
    HashTable();
    virtual ~HashTable();

    vector<vector<HashItem>> table;
    
    HashFunctionG g;
    HashFunctionH * h;
    int K;
    int T;
            
    void setup(int t, int k, int W, int d);
    
    void add(DataLine * line);
    
    set<int> getNeighbors(DataLine & query);
private:

};

#endif /* HASHTABLE_H */

