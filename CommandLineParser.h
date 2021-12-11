#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

#include <string>

using namespace std;

class CommandLineParser {
public:
    string inputfile, queryfile, outputfile, configurationfile, method, algorithm, metric, assignment, update;
    int noFunctions, nohashtables, no_nearest_neighbors, max_points_to_control, probes, radius, W, T;
    bool complete, silhouette;
    float delta;

    void parseLSH(int argc, char * argv[]);

    void parseCube(int argc, char * argv[]);

    void parseFrechet(int argc, char * argv[]);

    void parseClustering(int argc, char * argv[]);

    void parseSearch(int argc, char * argv[]);

private:
    void checkForEmptyBasicSearchParamsError();

    void parseBasicSearchParams(int argc, char * argv[]);

    void checkForEmptyBasicClusteringParamsError();

    void parseBasicClusteringParams(int argc, char * argv[]);

    void checkForEligibleUpdateAndAssignmentCombinations();
};

#endif /* COMMANDLINEPARSER_H */

