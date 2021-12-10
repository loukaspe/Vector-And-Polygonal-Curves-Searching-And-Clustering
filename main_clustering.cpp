#include <cmath>
#include <cstdlib>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <chrono>

#include "CommandLineParser.h"
#include "FileReader.h"
#include "HashTable.h"
#include "NearestNeighbourSolver.h"
#include "ClusteringSolver.h"
#include "ParametersFileReader.h"
#include "Logger.h"

using namespace std;

int main(int argc, char** argv) {

    CommandLineParser parser;

    parser.parseClustering(argc, argv);

    ParametersFileReader *parametersFileReader = new ParametersFileReader();
    parametersFileReader->loadParameters(parser.configurationfile);

    int number_of_clusters = parametersFileReader->getNumberOfClusters();
    int number_of_vector_hash_tables = parametersFileReader->getNumberOfVectorHashTables();
    int number_of_vector_hash_functions = parametersFileReader->getNumberOfVectorHashFunctions();
    int max_number_M_hypercube = parametersFileReader->getMaxNumberMHypercube();
    int number_of_hypercube_dimensions = parametersFileReader->getNumberOfHypercubeDimensions();
    int number_of_probes = parametersFileReader->getNumberOfProbes();

    int W = 500;

    Logger *logger = new Logger(parser.outputfile);
    stringstream ss;

    FileReader inputReader;

    inputReader.load(parser.inputfile);

    cout << "Input N: " << inputReader.N << endl;

    ClusteringSolver solver(inputReader.set, parser.outputfile);

    ClusteringSolver::Cluster * result = nullptr;

    int t[1] = { 0 };

    if (parser.method == "Classic" || parser.method == "classic") {
        result = solver.lloyd(number_of_clusters, t);
    }

    if (parser.method == "LSH" || parser.method == "lsh") {
        result = solver.lsh(number_of_clusters, t, number_of_vector_hash_tables, number_of_vector_hash_functions, W);
    }

    if (parser.method == "Hypercube" || parser.method == "hypercube") {
        result = solver.cube(number_of_clusters, t, number_of_vector_hash_tables, number_of_vector_hash_functions, W, max_number_M_hypercube, number_of_hypercube_dimensions, number_of_probes);
    }

    solver.silhouette(result, number_of_clusters, t);

    solver.print(result, number_of_clusters, parser.complete, t);

    logger->close();

    return 0;
}