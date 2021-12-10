#include <cstring>
#include "ParametersFileReader.h"

int ParametersFileReader::getNumberOfClusters() const {
    return number_of_clusters;
}

int ParametersFileReader::getNumberOfVectorHashTables() const {
    return number_of_vector_hash_tables;
}

int ParametersFileReader::getNumberOfVectorHashFunctions() const {
    return number_of_vector_hash_functions;
}

int ParametersFileReader::getMaxNumberMHypercube() const {
    return max_number_M_hypercube;
}

int ParametersFileReader::getNumberOfHypercubeDimensions() const {
    return number_of_hypercube_dimensions;
}

int ParametersFileReader::getNumberOfProbes() const {
    return number_of_probes;
}

void ParametersFileReader::loadParameters(string fileName) {
    ifstream file_handler;
    string line;
    string variableName;
    string variableValue;

    file_handler.open(fileName);

    if (file_handler.is_open()) {
        while (getline(file_handler, line)) {
            stringstream ss(line.c_str());
            line = ss.str();

            if(!std::getline(ss, variableName, ':')) {
                cout << "Something went wrong while reading file";
                exit(1);
            }

            ss >> variableValue;

            if (variableName == "number_of_clusters") {
                this->number_of_clusters = atoi(variableValue.c_str());
                continue;
            }

            if (variableName == "number_of_vector_hash_tables") {
                this->number_of_vector_hash_tables = atoi(variableValue.c_str());
                continue;
            }

            if (variableName == "number_of_vector_hash_functions") {
                this->number_of_vector_hash_functions = atoi(variableValue.c_str());
                continue;
            }

            if (variableName == "max_number_M_hypercube") {
                this->max_number_M_hypercube = atoi(variableValue.c_str());
                continue;
            }

            if (variableName == "number_of_hypercube_dimensions") {
                this->number_of_hypercube_dimensions = atoi(variableValue.c_str());
                continue;
            }

            if (variableName == "number_of_probes") {
                this->number_of_probes = atoi(variableValue.c_str());
                continue;
            }
        }

        file_handler.close();
    } else {
        cout << "Something went wrong while reading file";
        exit(1);
    }

}

ParametersFileReader::ParametersFileReader() {
    // Sets default values for variables
    this->number_of_clusters = 10;
    this->number_of_vector_hash_tables = 3;
    this->number_of_vector_hash_functions = 4;
    this->max_number_M_hypercube = 10;
    this->number_of_hypercube_dimensions = 3;
    this->number_of_probes = 10;
}
