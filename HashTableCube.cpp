#include "HashTableCube.h"
#include "HashFunctionG.h"
#include "HashFunctionH.h"
#include "HashFunctionF.h"

#include <iostream>

using namespace std;

vector<int> HashTableCube::getRelativeBuckets(int x, int max_points_to_control, int probes, int bits) {
    vector<int> buckets;
    int numberOfBits;
    int i = 0;

    while (true) {
        numberOfBits = this->countBits(i);
        if (numberOfBits > bits) {
            break;
        }

        if (this->calculateHammingDistance(x, i) <= probes) {
            buckets.push_back(i);
        }

        i++;
    }

    return buckets;
}

HashTableCube::HashTableCube() {

}

HashTableCube::~HashTableCube() {
    delete [] h;

    delete [] f;
}

void HashTableCube::setup(int _k, int W, int d) {
    k = _k;
    T = 1 << k;

    f = new HashFunctionF[k]();

    h = new HashFunctionH[k]();

    for (int i = 0; i < k; i++) {
        h[i].setup(W, d);
    }

    for (int i = 0; i < T; i++) {
        table.push_back(vector<HashItem>());
    }
}

void HashTableCube::add(DataLine * line) {
    int bucket = 0;

    int hi[k] = {0};
    int fi[k] = {0};

    for (int i = 0; i < k; i++) {
        if (i > 0) {
            bucket = bucket << 1;
        }
        hi[i] = h[i].value(*line);
        fi[i] = f[i].value(hi[i]);

        unsigned bit = fi[i]; // 0 or 1

        bucket += bit;
    }

    HashItem item;
    item.g = bucket;
    item.addr = line;

    table[bucket].push_back(item);
}

set<int> HashTableCube::getNeighbors(DataLine & query, int max_points_to_control, int probes) {
    set<int> offsets;

    int bucket = 0;

    int hi[k] = {0};
    int fi[k] = {0};

    for (int i = 0; i < k; i++) {
        if (i > 0) {
            bucket = bucket << 1;
        }
        hi[i] = h[i].value(query);
        fi[i] = f[i].value(hi[i]);

        unsigned bit = fi[i]; // 0 or 1

        bucket += bit;
    }


    vector<int> buckets = getRelativeBuckets(bucket, max_points_to_control, probes, k);

    for (unsigned int i = 0; i < buckets.size(); i++) {
        int bucket = buckets[i];
        for (unsigned int i = 0; i < table[bucket].size(); i++) {
            offsets.insert(table[bucket][i].addr->offset);
        }
    }

    return offsets;
}

int HashTableCube::calculateHammingDistance(int n1, int n2) {
    int x = n1 ^ n2;
    int setBits = 0;

    while (x > 0) {
        setBits += x & 1;
        x >>= 1;
    }

    return setBits;
}

int HashTableCube::countBits(unsigned int number) {
    unsigned int count = 0;
    while (number) {
        count++;
        number >>= 1;
    }
    return count;
}