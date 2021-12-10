#ifndef NEARESTNEIGHBOUR_H
#define NEARESTNEIGHBOUR_H

#include "DataSet.h"
#include "HashTable.h"


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

    vector<NearestNeighbourSolver::NearestNeighbor> * cube(unsigned N, int no_of_g, int max_points_to_control, int probes, int T, int noFunctions, int W, int t[]);

    HashTable * prepareHashtables(int nohashtables, int T, int noFunctions, int W);

    vector<NearestNeighbourSolver::NearestNeighbor> * lsh(HashTable * hashtables, DataSet & query, int nohashtables, int T, int noFunctions, int W);

    HashTable * prepareHyperCube(int no_of_g, int T, int noFunctions, int W);

    vector<NearestNeighbourSolver::NearestNeighbor> * cube(HashTable * hashtables, DataSet & query, int no_of_g, int max_points_to_control, int probes, int T, int noFunctions, int W);
};

#endif /* NEARESTNEIGHBOUR_H */