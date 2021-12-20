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

// "${OUTPUT_PATH}" -i input_small_id -c cluster.conf -o output.txt -complete false -silhouette false -update Mean_Vector -assignment Classic

int main(int argc, char** argv) {

    CommandLineParser parser;
      
    parser.parseClustering(argc, argv);
    
    parser.delta = 1;

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

    int t[1] = {0};

    if (parser.assignment == "Classic" || parser.assignment == "classic") {
        if (parser.update == "Mean_Vector") {
            result = solver.lloyd(number_of_clusters, t);
        } else {
            result = solver.lloyd_with_curves(number_of_clusters, t);
        }
    }

    if (parser.assignment == "LSH" || parser.assignment == "lsh") {
        result = solver.lsh(number_of_clusters, t, number_of_vector_hash_tables, number_of_vector_hash_functions, W);
    }

    if (parser.assignment == "Hypercube" || parser.assignment == "hypercube") {
        result = solver.cube(number_of_clusters, t, number_of_vector_hash_functions, W, max_number_M_hypercube, number_of_hypercube_dimensions, number_of_probes);
    }

    if (parser.assignment == "LSH_Frechet") {
        result = solver.lsh_frechet_with_curves(number_of_clusters, t, number_of_vector_hash_tables, number_of_vector_hash_functions, W, parser.delta);
    }

    if (parser.silhouette) {
        if (parser.update == "Mean_Vector") {
            solver.silhouette(result, number_of_clusters, t);
        } else {
            solver.silhouette_with_curves(result, number_of_clusters, t);
        }
    }

    if (parser.update == "Mean_Vector") {
        solver.print(result, number_of_clusters, parser.complete, t);
    } else {
        solver.print_with_curves(result, number_of_clusters, parser.complete, t);
    }


    

    logger->close();

    return 0;
}