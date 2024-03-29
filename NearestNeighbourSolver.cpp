#include "NearestNeighbourSolver.h"
#include "DistanceCalculator.h"
#include "HashTable.h"
#include "HashTableCube.h"
#include "HashTableCurve.h"

#include <algorithm>
#include <chrono>

NearestNeighbourSolver::NearestNeighbourSolver(DataSet & input) : input(input), query(input) {

}

NearestNeighbourSolver::NearestNeighbourSolver(DataSet & input, DataSet & query) : input(input), query(query) {

}

NearestNeighbourSolver::~NearestNeighbourSolver() {

}

bool compareNearestNeighbor(NearestNeighbourSolver::NearestNeighbor i1, NearestNeighbourSolver::NearestNeighbor i2) {
    return (i1.distance < i2.distance);
}

vector<NearestNeighbourSolver::NearestNeighbor> * NearestNeighbourSolver::bruteForce(unsigned N, int t[]) {
    unsigned q = query.lines.size();
    vector<NearestNeighbor> * data = new vector<NearestNeighbor>[q];

    DistanceCalculator calc(false);

    for (unsigned int i = 0; i < query.lines.size(); i++) {
        auto start = chrono::steady_clock::now();

        for (unsigned int j = 0; j < input.lines.size(); j++) {
            double dist = calc.calculateDistance(query.lines[i], input.lines[j]);

            NearestNeighbor n(j, dist);
            data[i].push_back(n);

        }

        sort(data[i].begin(), data[i].end(), compareNearestNeighbor);

        if (data[i].size() > N) {
            data[i].resize(N, NearestNeighbor(-1, -1));
        }

        auto end = chrono::steady_clock::now();

        t[i] = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    }

    return data;
}

vector<NearestNeighbourSolver::NearestNeighbor> * NearestNeighbourSolver::lsh(unsigned N, int nohashtables, int T, int noFunctions, int W, int t[]) {
    unsigned q = query.lines.size();
    unsigned d = input.lines[0].data.size();

    vector<NearestNeighbor> * data = new vector<NearestNeighbor>[q];

    DistanceCalculator calc(false);


    HashTable hashtables[nohashtables];

    for (int i = 0; i < nohashtables; i++) {
        hashtables[i].setup(T, noFunctions, W, d);
    }

    for (unsigned int i = 0; i < input.lines.size(); i++) {
        for (int l = 0; l < nohashtables; l++) {
            hashtables[l].add(&input.lines[i]);
        }
    }


    for (unsigned int i = 0; i < query.lines.size(); i++) {
        set<int> hits;

        auto start = chrono::steady_clock::now();

        for (int l = 0; l < nohashtables; l++) {
            set<int> offsets = hashtables[l].getNeighbors(query.lines[i]);

            for (auto x : offsets) {
                hits.insert(x);
            }
        }

        for (auto offset : hits) {
            double dist = calc.calculateDistance(query.lines[i], input.lines[offset]);

            NearestNeighbor n(offset, dist);
            data[i].push_back(n);

        }

        sort(data[i].begin(), data[i].end(), compareNearestNeighbor);

        if (data[i].size() > N) {
            data[i].resize(N, NearestNeighbor(-1, -1));
        }

        auto end = chrono::steady_clock::now();

        t[i] = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    }

    return data;
}

vector<NearestNeighbourSolver::NearestNeighbor> * NearestNeighbourSolver::cube(unsigned N, int max_points_to_control, int probes, int noFunctions, int W, int t[]) {
    unsigned q = query.lines.size();
    unsigned d = input.lines[0].data.size();

    vector<NearestNeighbor> * data = new vector<NearestNeighbor>[q];

    DistanceCalculator calc(false);

    HashTableCube hashtables[1];

    hashtables[0].setup(noFunctions, W, d);

    for (unsigned int i = 0; i < input.lines.size(); i++) {
        hashtables[0].add(&input.lines[i]);
    }


    for (unsigned int i = 0; i < query.lines.size(); i++) {
        set<int> hits;

        auto start = chrono::steady_clock::now();

        set<int> offsets = hashtables[0].getNeighbors(query.lines[i], probes);

        for (auto x : offsets) {
            hits.insert(x);
        }

        for (auto offset : hits) {
            double dist = calc.calculateDistance(query.lines[i], input.lines[offset]);

            NearestNeighbor n(offset, dist);
            data[i].push_back(n);

        }

        sort(data[i].begin(), data[i].end(), compareNearestNeighbor);

        if (data[i].size() > N) {
            data[i].resize(N, NearestNeighbor(-1, -1));
        }

        auto end = chrono::steady_clock::now();

        t[i] = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    }


    return data;
}


// clustering

HashTable * NearestNeighbourSolver::prepareHashtables(int nohashtables, int T, int noFunctions, int W) {
    unsigned d = input.lines[0].data.size();

    HashTable * hashtables = new HashTable[nohashtables];

    for (int i = 0; i < nohashtables; i++) {
        hashtables[i].setup(T, noFunctions, W, d);
    }

    for (unsigned int i = 0; i < input.lines.size(); i++) {
        for (int l = 0; l < nohashtables; l++) {
            hashtables[l].add(&input.lines[i]);
        }
    }

    return hashtables;
}

HashTableCube * NearestNeighbourSolver::prepareHyperCube(int no_of_g, int T, int noFunctions, int W) {
    unsigned q = query.lines.size();
    unsigned d = input.lines[0].data.size();

    HashTableCube * hashtables = new HashTableCube[1];

    hashtables[0].setup(noFunctions, W, d);

    for (unsigned int i = 0; i < input.lines.size(); i++) {
        hashtables[0].add(&input.lines[i]);
    }

    return hashtables;
}

vector<NearestNeighbourSolver::NearestNeighbor> * NearestNeighbourSolver::lsh(HashTable * hashtables, DataSet & query, int nohashtables, int T, int noFunctions, int W) {
    unsigned q = query.lines.size();
    unsigned d = input.lines[0].data.size();

    vector<NearestNeighbor> * data = new vector<NearestNeighbor>[q];

    DistanceCalculator calc(false);

    for (unsigned int i = 0; i < query.lines.size(); i++) {
        set<int> hits;

        for (int l = 0; l < nohashtables; l++) {
            set<int> offsets = hashtables[l].getNeighbors(query.lines[i]);

            for (auto x : offsets) {
                hits.insert(x);
            }
        }

        for (auto offset : hits) {
            double dist = calc.calculateDistance(query.lines[i], input.lines[offset]);

            NearestNeighbor n(offset, dist);
            data[i].push_back(n);

        }

        sort(data[i].begin(), data[i].end(), compareNearestNeighbor);
    }

    return data;
}

vector<NearestNeighbourSolver::NearestNeighbor> * NearestNeighbourSolver::cube(HashTableCube * hashtables, DataSet & query, int no_of_g, int max_points_to_control, int probes, int T, int noFunctions, int W) {
    unsigned q = query.lines.size();
    unsigned d = input.lines[0].data.size();

    vector<NearestNeighbor> * data = new vector<NearestNeighbor>[q];

    DistanceCalculator calc(false);

    for (unsigned int i = 0; i < query.lines.size(); i++) {
        set<int> hits;
        set<int> offsets = hashtables[0].getNeighbors(query.lines[i], probes);

        for (auto x : offsets) {
            hits.insert(x);
        }

        for (auto offset : hits) {
            double dist = calc.calculateDistance(query.lines[i], input.lines[offset]);

            NearestNeighbor n(offset, dist);
            data[i].push_back(n);
        }

        sort(data[i].begin(), data[i].end(), compareNearestNeighbor);
    }

    return data;
}

// Search Frechet - NN

vector<NearestNeighbourSolver::NearestNeighbor> * NearestNeighbourSolver::frechet(unsigned N, int nohashtables, int T, int noFunctions, int W, int t[], string metric, double delta) {
    unsigned q = query.lines.size();
    unsigned d = input.lines[0].data.size();

    vector<NearestNeighbor> * data = new vector<NearestNeighbor>[q];

    DistanceCalculator calc(false);


    HashTableCurve hashtables[nohashtables];

    for (int i = 0; i < nohashtables; i++) {
        hashtables[i].setup(T, noFunctions, W, d, delta);
    }

    for (unsigned int i = 0; i < input.lines.size(); i++) {
        input.lines[i].curve.setup(input.lines[i].data); // vector to curve
    }

    for (unsigned int i = 0; i < query.lines.size(); i++) {
        query.lines[i].curve.setup(query.lines[i].data); // vector to curve
    }

    for (unsigned int i = 0; i < input.lines.size(); i++) {
        for (int l = 0; l < nohashtables; l++) {
            hashtables[l].add(&input.lines[i], 2*d);
        }
    }


    for (unsigned int i = 0; i < query.lines.size(); i++) {
        set<int> hits;

        auto start = chrono::steady_clock::now();

        for (int l = 0; l < nohashtables; l++) {
            set<int> offsets = hashtables[l].getNeighbors(query.lines[i], 2*d);

            for (auto x : offsets) {
                hits.insert(x);
            }
        }

        for (auto offset : hits) {
            double dist = calc.calculateDistance(query.lines[i].curve, input.lines[offset].curve);

            NearestNeighbor n(offset, dist);
            data[i].push_back(n);

        }

        sort(data[i].begin(), data[i].end(), compareNearestNeighbor);

        if (data[i].size() > N) {
            data[i].resize(N, NearestNeighbor(-1, -1));
        }

        auto end = chrono::steady_clock::now();

        t[i] = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
    }

    return data;
}

vector<NearestNeighbourSolver::NearestNeighbor> * NearestNeighbourSolver::frechet(HashTableCurve * hashtables, DataSet & query, int nohashtables, int T, int noFunctions, int W, double delta) {
    unsigned q = query.lines.size();
    unsigned d = input.lines[0].data.size();

    vector<NearestNeighbor> * data = new vector<NearestNeighbor>[q];

    DistanceCalculator calc(false);

    for (unsigned int i = 0; i < query.lines.size(); i++) {
        set<int> hits;

        for (int l = 0; l < nohashtables; l++) {
            set<int> offsets = hashtables[l].getNeighbors(query.lines[i], 2*d);

            for (auto x : offsets) {
                hits.insert(x);
            }
        }

        for (auto offset : hits) {
            double dist = calc.calculateDistance(query.lines[i].curve, input.lines[offset].curve);

            NearestNeighbor n(offset, dist);
            data[i].push_back(n);

        }

        sort(data[i].begin(), data[i].end(), compareNearestNeighbor);
    }

    return data;
}

