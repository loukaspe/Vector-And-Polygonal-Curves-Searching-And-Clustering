#ifndef PARAMETERSFILEREADER_H
#define PARAMETERSFILEREADER_H

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

using namespace std;

class ParametersFileReader {
public:
    ParametersFileReader();

    void loadParameters(string fileName);

    int getNumberOfClusters() const;

    int getNumberOfVectorHashTables() const;

    int getNumberOfVectorHashFunctions() const;

    int getMaxNumberMHypercube() const;

    int getNumberOfHypercubeDimensions() const;

    int getNumberOfProbes() const;

private:
    int number_of_clusters;
    int number_of_vector_hash_tables;
    int number_of_vector_hash_functions;
    int max_number_M_hypercube;
    int number_of_hypercube_dimensions;
    int number_of_probes;
};

#endif
