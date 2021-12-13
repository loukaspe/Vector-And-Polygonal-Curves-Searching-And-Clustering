#ifndef HASHTABLE_CURVE_H
#define HASHTABLE_CURVE_H

#include <set>
#include <vector>

#include "DataLine.h"
#include "HashFunctionG.h"
#include "HashFunctionH.h"
#include "Grid.h"

using namespace std;

class HashTableCurve {
    class HashItem {
    public:
        unsigned g;
        DataLine * addr;
    };
public:
    HashTableCurve();
    virtual ~HashTableCurve();

    vector<vector<HashItem>> table;

    HashFunctionG g;
    HashFunctionH * h;
    int K;
    int T;

    Grid grid;

    void setup(int t, int k, int W, int d, double delta);

    void add(DataLine * line);

    set<int> getNeighbors(DataLine & query);
private:

};

#endif /* HASHTABLE_H */

