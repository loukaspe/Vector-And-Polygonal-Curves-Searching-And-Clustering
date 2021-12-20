#include <cmath>
#include <cstdlib>
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <cfloat>

#include "CommandLineParser.h"
#include "FileReader.h"
#include "HashTable.h"
#include "NearestNeighbourSolver.h"
#include "Logger.h"

using namespace std;

static void log(stringstream *logs, Logger* logger);


// "${OUTPUT_PATH}" -i nasd_input.csv -q nasd_query.csv -k 14 -M 10 -probes 2 -o output.txt -algorithm Hypercube

int main(int argc, char** argv) {

    CommandLineParser parser;

    parser.parseSearch(argc, argv);
    parser.W = 200;

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

    cout << "Dim input: " << inputReader.set.lines[0].getDimension() << endl;
    cout << "Dim query: " << queryReader.set.lines[0].getDimension() << endl;

    int t_bf[queryReader.set.lines.size()];
    int t_algorithm[queryReader.set.lines.size()];

    vector<NearestNeighbourSolver::NearestNeighbor> * result_bf = solver.bruteForce(parser.no_nearest_neighbors, t_bf, parser.metric);

    double max_ratio = 0;

    if (parser.algorithm == "LSH") {
        cout << "LSH running ... " << endl;

        vector<NearestNeighbourSolver::NearestNeighbor> * result_lsh = solver.lsh(parser.no_nearest_neighbors, parser.nohashtables, parser.T, parser.noFunctions, parser.W, t_algorithm);

        for (unsigned int i = 0; i < queryReader.set.lines.size(); i++) {
            cout << "_____________________________________________________ \n";
            ss << "\nQuery " << i << ": " << endl << "Algorithm: " << parser.algorithm << endl;
            log(&ss, logger);

            for (int j = 0; j < parser.no_nearest_neighbors; j++) {
                if ((unsigned) j < result_lsh[i].size()) {
                    ss << "Approximate  Nearest neighbor-" << j << ":" << "\t" << result_lsh[i][j].index << endl;
                    log(&ss, logger);

                    ss << "distanceLSH" << ":" << "\t" << sqrt(result_lsh[i][j].distance) << endl;
                    log(&ss, logger);

                    ss << "distanceApproximate" << ":" << "\t" << sqrt(result_lsh[i][j].distance) << endl;
                    log(&ss, logger);

                    cout << "tLSH : " << t_algorithm[i] << " ns " << endl;
                }

                ss << "True Nearest neighbor-" << j << ":" << "\t" << result_bf[i][j].index << endl;
                log(&ss, logger);

                ss << "distanceTrue" << ":" << "\t" << sqrt(result_bf[i][j].distance) << endl;
                log(&ss, logger);

                cout << "tTrue : " << t_bf[i] << " ns " << endl;

                if ((unsigned) j < result_lsh[i].size()) {
                    double ratio = sqrt(result_lsh[i][j].distance) / sqrt(result_bf[i][j].distance);

                    if (ratio > max_ratio) {
                        max_ratio = ratio;
                    }
                }
            }
        }
    }

    if (parser.algorithm == "Hypercube") {
        cout << "Cube running ... " << endl;

        vector<NearestNeighbourSolver::NearestNeighbor> * result_cube = solver.cube(parser.no_nearest_neighbors, parser.max_points_to_control, parser.probes, parser.noFunctions, parser.W, t_algorithm);

        for (unsigned int i = 0; i < queryReader.set.lines.size(); i++) {
            cout << "_____________________________________________________ \n";
            ss << "\nQuery " << i << ": " << endl << "Algorithm: " << parser.algorithm << endl;
            log(&ss, logger);

            for (int j = 0; j < parser.no_nearest_neighbors; j++) {
                if ((unsigned) j < result_cube[i].size()) {
                    ss << "Approximate Nearest neighbor-" << j << ":" << "\t" << result_cube[i][j].index << endl;
                    log(&ss, logger);

                    ss << "distanceApproximate" << ":" << "\t" << sqrt(result_cube[i][j].distance) << endl;
                    log(&ss, logger);

                    cout << "tHypercube : " << t_algorithm[i] << " ns " << endl;
                }

                ss << "True Nearest neighbor-" << j << ":" << "\t" << result_bf[i][j].index << endl;
                log(&ss, logger);

                ss << "distanceTrue" << ":" << "\t" << sqrt(result_bf[i][j].distance) << endl;
                log(&ss, logger);

                cout << "tTrue : " << t_bf[i] << " ns " << endl;

                if ((unsigned) j < result_cube[i].size()) {
                    double ratio = sqrt(result_cube[i][j].distance) / sqrt(result_bf[i][j].distance);

                    if (ratio > max_ratio) {
                        max_ratio = ratio;
                    }
                }
            }
        }
    }

    if (parser.algorithm == "Frechet") {
        cout << "Frechet running ... " << endl;
        vector<NearestNeighbourSolver::NearestNeighbor> * result_frechet = solver.frechet(parser.no_nearest_neighbors, parser.nohashtables, parser.T, parser.noFunctions, parser.W, t_algorithm, parser.metric, parser.delta);

        for (unsigned int i = 0; i < queryReader.set.lines.size(); i++) {
            cout << "_____________________________________________________ \n";
            ss << "\nQuery " << i << ": " << endl << "Algorithm: " << parser.algorithm << endl;
            log(&ss, logger);

            for (int j = 0; j < parser.no_nearest_neighbors; j++) {
                if ((unsigned) j < result_frechet[i].size()) {
                    ss << "Approximate  Nearest neighbor-" << j << ":" << "\t" << result_frechet[i][j].index << endl;
                    log(&ss, logger);

                    ss << "distanceApproximate" << ":" << "\t" << result_frechet[i][j].distance << endl;
                    
                    log(&ss, logger);

                    cout << "tFrechet : " << t_algorithm[i] << " ns " << endl;
                }

                ss << "True Nearest neighbor-" << j << ":" << "\t" << result_bf[i][j].index << endl;
                log(&ss, logger);

                ss << "distanceTrue" << ":" << "\t" << result_bf[i][j].distance << endl;
                log(&ss, logger);

                cout << "tTrue : " << t_bf[i] << " ns " << endl;

                if ((unsigned) j < result_frechet[i].size()) {
                    double ratio = result_frechet[i][j].distance/result_bf[i][j].distance;

                    if (ratio > max_ratio) {
                        max_ratio = ratio;
                    }
                }
            }
        }
    }


    double avg_t_bf = 0.0;
    double avg_t_algorithm = 0.0;

    for (unsigned int i = 0; i < queryReader.set.lines.size(); i++) {
        avg_t_bf += t_bf[i];
        avg_t_algorithm += t_algorithm[i];
    }

    avg_t_bf /= queryReader.set.lines.size();
    avg_t_algorithm /= queryReader.set.lines.size();

    ss << "\ntApproximateAverage: " << avg_t_algorithm << " ns " << endl;
    log(&ss, logger);

    ss << "tTrueAverage: " << avg_t_bf << " ns " << endl;
    log(&ss, logger);

    ss << "MAF: " << max_ratio << endl;
    log(&ss, logger);

    logger->close();

    return 0;
}

void log(stringstream *logs, Logger* logger) {
    cout << logs->str();
    logger->log(logs->str());
    logs->str(std::string());
}
