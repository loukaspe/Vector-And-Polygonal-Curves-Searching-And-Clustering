#ifndef CLUSTERINGSOLVER_H
#define CLUSTERINGSOLVER_H

#include <vector>

#include "DataSet.h"
#include "DataLine.h"
#include "ClusteringSolver.h"
#include "Generator.h"
#include "DistanceCalculator.h"
#include "NearestNeighbourSolver.h"
#include "Logger.h"

using namespace std;

class ClusteringSolver {
public:

    class Cluster {
    public:
        vector<int> indices;
        DataLine * center;
        double silhouette;
    };

private:
    DataSet & input;
    string algorithm;
    string outputFile;

    void printInitialState(ClusteringSolver::Cluster * initialState, int clusters);
    ClusteringSolver::Cluster * initialization(int clusters);
    ClusteringSolver::Cluster * update(ClusteringSolver::Cluster * now, int clusters);
public:
    ClusteringSolver(DataSet & input, string outputFile);
    virtual ~ClusteringSolver();

    ClusteringSolver::Cluster * lloyd(int clusters, int t[]);
    ClusteringSolver::Cluster * lsh(int clusters, int t[], int number_of_vector_hash_tables, int number_of_vector_hash_functions, int W);
    ClusteringSolver::Cluster * cube(int clusters, int t[], int number_of_vector_hash_tables, int number_of_vector_hash_functions, int W, int max_number_M_hypercube, int number_of_hypercube_dimensions, int number_of_probes);

    void print(ClusteringSolver::Cluster * initialState, int clusters, bool complete, int t[]);

    void silhouette(ClusteringSolver::Cluster * lastState, int clusters, int t[]);
};

void log(stringstream *logs, Logger* logger);

#endif /* CLUSTERINGSOLVER_H */