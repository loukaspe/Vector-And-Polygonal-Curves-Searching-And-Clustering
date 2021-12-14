#ifndef NEARESTNEIGHBOUR_H
#define NEARESTNEIGHBOUR_H

#include "DataSet.h"
#include "HashTable.h"
#include "HashTableCube.h"


class NearestNeighbourSolver {
private:
    DataSet & input;
    DataSet & query;
public:
    class NearestNeighbor {
    public:
        int index;
        float distance;

        NearestNeighbor(int index, float distance) : index(index), distance(distance) {
        }

        NearestNeighbor& operator=(const NearestNeighbor& right) {
            // Check for self-assignment!
            if (this == &right) // Same object?
                return *this; // Yes, so skip assignment, and just return *this.
            // Deallocate, allocate new space, copy values...

            this->index = right.index;
            this->distance = right.distance;

            return *this;
        }
    };

    NearestNeighbourSolver(DataSet & input);
    NearestNeighbourSolver(DataSet & input, DataSet & query);
    virtual ~NearestNeighbourSolver();

    vector<NearestNeighbourSolver::NearestNeighbor> * bruteForce(unsigned N, int t[]);

    vector<NearestNeighbourSolver::NearestNeighbor> * lsh(unsigned N, int nohashtables, int T, int noFunctions, int W, int t[]);

    vector<NearestNeighbourSolver::NearestNeighbor> * cube(unsigned N, int max_points_to_control, int probes, int noFunctions, int W, int t[]);

    HashTable * prepareHashtables(int nohashtables, int T, int noFunctions, int W);

    vector<NearestNeighbourSolver::NearestNeighbor> * lsh(HashTable * hashtables, DataSet & query, int nohashtables, int T, int noFunctions, int W);

    HashTableCube * prepareHyperCube(int no_of_g, int T, int noFunctions, int W);

    vector<NearestNeighbourSolver::NearestNeighbor> * cube(HashTableCube * hashtables, DataSet & query, int no_of_g, int max_points_to_control, int probes, int T, int noFunctions, int W);

    // Frechet
    vector<NearestNeighbourSolver::NearestNeighbor> * frechet(unsigned N, int nohashtables, int T, int noFunctions, int W, int t[], string metric, double delta);

//    vector<NearestNeighbourSolver::NearestNeighbor> * frechet(HashTable * hashtables, DataSet & query, int nohashtables, int T, int noFunctions, int W, string metric, double delta);


};

#endif /* NEARESTNEIGHBOUR_H */