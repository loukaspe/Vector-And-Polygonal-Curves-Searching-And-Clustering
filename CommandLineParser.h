#ifndef COMMANDLINEPARSER_H
#define COMMANDLINEPARSER_H

#include <string>

using namespace std;

class CommandLineParser {
public:
    // LSH
    
    // Cube
    
    // Clustering
    string inputfile, queryfile, outputfile, configurationfile, method;
    int noFunctions, nohashtables, no_nearest_neighbors, max_points_to_control, probes;
    int radius;
    int W;
    int T;
    bool complete;
    
    void parseLSH(int argc, char * argv[]);
    
    void parseCube(int argc, char * argv[]);
    
    void parseClustering(int argc, char * argv[]);
    
};

#endif /* COMMANDLINEPARSER_H */

