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

    parser.parseLSH(argc, argv);
    parser.W = 500;

    Logger *logger = new Logger(parser.outputfile);
    stringstream ss;

    FileReader inputReader;
    FileReader queryReader;

    inputReader.load(parser.inputfile.c_str());
    queryReader.load(parser.queryfile.c_str());

    parser.T = inputReader.N / 8;

    cout << "Input N: " << inputReader.N << endl;
    cout << "Query N: " << queryReader.N << endl;


    NearestNeighbourSolver solver(inputReader.set, queryReader.set);

    cout << "Brute force running ... " << endl;

    int t_bf[queryReader.set.lines.size()];
    int t_lsh[queryReader.set.lines.size()];

    vector<NearestNeighbourSolver::NearestNeighbor> * result_bf = solver.bruteForce(parser.no_nearest_neighbors, t_bf);

    cout << "LSH running ... " << endl;
    vector<NearestNeighbourSolver::NearestNeighbor> * result_lsh = solver.lsh(parser.no_nearest_neighbors, parser.nohashtables, parser.T, parser.noFunctions, parser.W, t_lsh);


    for (unsigned int i = 0; i < queryReader.set.lines.size(); i++) {
        cout << "_____________________________________________________ \n";
        ss << "Query #" << i << ": " << endl;
        log(&ss, logger);

        for (int j = 0; j < parser.no_nearest_neighbors; j++) {
            ss << "Nearest neighbor-" << j << ":" << "\t" << result_lsh[i][j].index << endl;
            log(&ss, logger);
//            ss << "distanceLSH" << j << ":" << "\t" << result_lsh[i][j].index << "\t" << inputReader.set.lines[result_lsh[i][j].index].id << "\t" << sqrt(result_lsh[i][j].distance) << endl;
            ss << "distanceLSH" << ":" << "\t" << sqrt(result_lsh[i][j].distance) << endl;
            log(&ss, logger);
//            ss << "distanceTrue" << j << ":" << "\t" << result_bf[i][j].index << "\t" << inputReader.set.lines[result_bf[i][j].index].id << "\t" << sqrt(result_bf[i][j].distance) << endl;
            ss << "distanceTrue" << ":" << "\t" << sqrt(result_bf[i][j].distance) << endl;
            log(&ss, logger);

            ss << "tTrue : " << t_bf[i] << " ms " << endl;
            log(&ss, logger);

            ss << "tLSH : " << t_lsh[i] << " ms " << endl;
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