#ifndef HASHTABLE_CUBE_H
#define HASHTABLE_CUBE_H

#include <set>
#include <vector>

#include "DataLine.h"
#include "HashFunctionG.h"
#include "HashFunctionH.h"
#include "HashFunctionF.h"

using namespace std;

class HashTableCube {
    class HashItem {
    public:
        unsigned g;
        DataLine * addr;
    };
public:
    HashTableCube();
    virtual ~HashTableCube();

    vector<vector<HashItem>> table;
    
    HashFunctionH * h;
    HashFunctionF * f;
    int k;
    int T;
            
    void setup(int k, int W, int d);
    
    void add(DataLine * line);
    
    set<int> getNeighbors(DataLine & query, int max_points_to_control, int probes);
private:
    vector<int> getRelativeBuckets(int x, int max_points_to_control, int probes, int bits);

    int calculateHammingDistance(int n1, int n2);

    int countBits(unsigned int number);
};

#endif /* HASHTABLE_H */

