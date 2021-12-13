#include "HashTableCurve.h"
#include "HashFunctionG.h"
#include "HashFunctionH.h"

#include <iostream>

using namespace std;


HashTableCurve::HashTableCurve() {

}

HashTableCurve::~HashTableCurve() {
    delete [] h;
}

void HashTableCurve::setup(int t, int k, int W, int d, double delta) {
    K = k;
    T = t;

    g.setup(k);

    h = new HashFunctionH[k];

    for (int i=0;i<k;i++) {
        h[i].setup(W, d);
    }

    for (int i=0;i<t;i++) {
        table.push_back(vector<HashItem>());
    }

    grid.setup(delta, 2);
}

void HashTableCurve::add(DataLine * line) {
    int hi[K] = { 0 };



    for (int i=0;i<K;i++) {
        hi[i] = h[i].value(*line);
    }

    unsigned g_output = g.value(hi);
    unsigned bucket = g_output % T;

    HashItem item;
    item.g = g_output;
    item.addr = line;


    table[bucket].push_back(item);
}

set<int> HashTableCurve::getNeighbors(DataLine & query) {
    set<int> offsets;

    int hi[K] = { 0 };

    for (int i=0;i<K;i++) {
        hi[i] = h[i].value(query);
    }

    unsigned g_output = g.value(hi);
    unsigned bucket = g_output % T;

    for (unsigned int i=0;i<table[bucket].size();i++) {
        if (table[bucket][i].g == g_output) {
            offsets.insert(table[bucket][i].addr->offset);
        }
    }

    return offsets;
}