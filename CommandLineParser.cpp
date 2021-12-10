#include "CommandLineParser.h"

#include <iostream>
#include <string>

using namespace std;

void CommandLineParser::parseLSH(int argc, char * argv[]) {
    
    noFunctions = 4;
    nohashtables = 5;
    no_nearest_neighbors = 1;
//    max_points_to_control = 10;
//    probes = 2;
//    radius = 10000;
//    complete = false;   
    
    for (int i = 1; i < argc; i++) {
        if (argv[i] == std::string("-i")) {
            inputfile = argv[i + 1];
        }

        if (argv[i] == std::string("-q")) {
            queryfile = argv[i + 1];
        }

        if (argv[i] == std::string("-k")) {
            noFunctions = atoi(argv[i + 1]);
        }

        if (argv[i] == std::string("-L")) {
            nohashtables = atoi(argv[i + 1]);
        }

        if (argv[i] == std::string("-o")) {
            outputfile = argv[i + 1 ];
        }

        if (argv[i] == std::string("-N")) {
            no_nearest_neighbors = atoi(argv[i + 1]);
        }

        if (argv[i] == std::string("-R")) {
            radius = atof(argv[i + 1]);
        }
    }
    
    cout << "Input file    : " << inputfile << endl;
    cout << "Query file    : " << queryfile << endl;
    cout << "Output file   : " << outputfile << endl;
    cout << "Functions  (k): " << noFunctions << endl;
    cout << "Hashtables (L): " << nohashtables << endl;
    cout << "NN            : " << no_nearest_neighbors << endl;
    cout << "Radius     (R): " << radius << endl;
}

void CommandLineParser::parseCube(int argc, char * argv[]) {
    for (int i = 1; i < argc; i++) {

        if (argv[i] == std::string("-i")) {
            inputfile = argv[i + 1 ];
        }

        if (argv[i] == std::string("-q")) {
            queryfile = argv[i + 1 ];
        }

        if (argv[i] == std::string("-k")) {
            noFunctions = atoi(argv[i + 1 ]);
        }

        if (argv[i] == std::string("-M")) {
            max_points_to_control = atoi(argv[i + 1 ]);
        }

        if (argv[i] == std::string("-probes")) {
            probes = atoi(argv[i + 1 ]);
        }

        if (argv[i] == std::string("-o")) {
            outputfile = argv[i + 1 ];
        }

        if (argv[i] == std::string("-N")) {
            no_nearest_neighbors = atoi(argv[i + 1 ]);
        }

        if (argv[i] == std::string("-R")) {
            radius = atoi(argv[i + 1 ]);
        }
    }
}

void CommandLineParser::parseClustering(int argc, char * argv[]) {
    for (int i = 1; i < argc; i++) {

        if (argv[i] == std::string("-i")) {
            inputfile = argv[i + 1 ];
        }

        if (argv[i] == std::string("-c")) {
            configurationfile = argv[i + 1 ];
        }

        if (argv[i] == std::string("-o")) {
            outputfile = argv[i + 1 ];
        }

        if (argv[i] == std::string("-complete")) {
            complete = argv[i + 1 ];
        }

        if (argv[i] == std::string("-m")) {
            method = argv[i + 1 ];
        }
    }
}