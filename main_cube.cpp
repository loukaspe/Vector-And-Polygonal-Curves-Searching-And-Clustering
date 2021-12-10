#include <cmath>
#include <cstdlib>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>

#include "CommandLineParser.h"
#include "FileReader.h"
#include "HashTable.h"
#include "NearestNeighbourSolver.h"
#include "Logger.h"

using namespace std;

void log(stringstream *logs, Logger* logger);

int main(int argc, char** argv) {

    CommandLineParser parser;

    parser.parseCube(argc, argv);
    parser.W = 500;

    FileReader inputReader;
    FileReader queryReader;

    inputReader.load(parser.inputfile.c_str());
    queryReader.load(parser.queryfile.c_str());

    cout << "Input N: " << inputReader.N << endl;
    cout << "Query N: " << queryReader.N << endl;


    NearestNeighbourSolver solver(inputReader.set, queryReader.set);

    cout << "Brute force running ... " << endl;

    int t_bf[queryReader.set.lines.size()];
    int t_cube[queryReader.set.lines.size()];
    int no_of_g = (int) log2(inputReader.set.lines.size());

    parser.T = (int) pow(2, no_of_g);

    cout << "Brute force running ... " << endl;
    vector<NearestNeighbourSolver::NearestNeighbor> * result_bf = solver.bruteForce(parser.no_nearest_neighbors, t_bf);

    cout << "Cube running ... " << endl;
    vector<NearestNeighbourSolver::NearestNeighbor> * result_cube = solver.cube(parser.no_nearest_neighbors, no_of_g, parser.max_points_to_control, parser.probes, parser.T, parser.noFunctions, parser.W, t_cube);

    Logger *logger = new Logger(parser.outputfile);
    stringstream ss;

    for (unsigned int i = 0; i < queryReader.set.lines.size(); i++) {
        cout << "_____________________________________________________ \n";
        ss << "Query #" << i << ": " << endl;
        log(&ss, logger);

        for (int j = 0; j < parser.no_nearest_neighbors; j++) {
            if ((unsigned) j < result_cube[i].size()) {
                ss << "Nearest neighbor-" << j << ":" << "\t" << result_cube[i][j].index << endl;
                log(&ss, logger);

                ss << "distanceHypercube" << ":" << "\t" << sqrt(result_cube[i][j].distance) << endl;
                log(&ss, logger);
                ss << "tHypercube : " << t_cube[i] << " ms " << endl;
                log(&ss, logger);
            }

            ss << "distanceTrue" << ":" << "\t" << sqrt(result_bf[i][j].distance) << endl;
            log(&ss, logger);

            ss << "tTrue : " << t_bf[i] << " ms " << endl;
            log(&ss, logger);
        }

        unsigned j = 0;

        ss << "R-near neighbors:" << endl;
        cout << "R = " << parser.radius << endl;
        log(&ss, logger);

        while (sqrt(result_bf[i][j].distance) < parser.radius && j < result_bf[i].size()) {
            ss << result_bf[i][j].index << endl;
            log(&ss, logger);
            j++;
        }
    }

    logger->close();

    return 0;
}

void log(stringstream *logs, Logger* logger) {
    cout << logs->str();
    logger->log(logs->str());
    logs->str(std::string());
}
