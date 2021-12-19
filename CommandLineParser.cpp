#include "CommandLineParser.h"

#include <iostream>
#include <string>

using namespace std;

const string MEAN_FRECHET_UPDATE = "Mean_Frechet";
const string MEAN_VECTOR_UPDATE = "Mean_Vector";
const string CLASSIC_ASSIGNMENT = "Classic";
const string LSH_ASSIGNMENT = "LSH";
const string HYPERCUBE_ASSIGNMENT = "Hypercube";
const string LSH_FRECHET_ASSIGNMENT = "LSH_Frechet";

void CommandLineParser::parseLSH(int argc, char *argv[]) {
    noFunctions = 4;
    nohashtables = 5;
    no_nearest_neighbors = 1;

    for (int i = 1; i < argc; i++) {
        if (argv[i] == std::string("-k")) {
            noFunctions = atoi(argv[i + 1]);
        }

        if (argv[i] == std::string("-L")) {
            nohashtables = atoi(argv[i + 1]);
        }
    }

    cout << "Input file    : " << inputfile << endl;
    cout << "Query file    : " << queryfile << endl;
    cout << "Output file   : " << outputfile << endl;
    cout << "Functions  (k): " << noFunctions << endl;
    cout << "Hashtables (L): " << nohashtables << endl;
}

void CommandLineParser::parseCube(int argc, char *argv[]) {
    noFunctions = 14;
    max_points_to_control = 10;
    no_nearest_neighbors = 1;
    probes = 2;

    for (int i = 1; i < argc; i++) {
        if (argv[i] == std::string("-k")) {
            noFunctions = atoi(argv[i + 1]);
        }

        if (argv[i] == std::string("-M")) {
            max_points_to_control = atoi(argv[i + 1]);
        }

        if (argv[i] == std::string("-probes")) {
            probes = atoi(argv[i + 1]);
        }
    }

    cout << "Input file    : " << inputfile << endl;
    cout << "Query file    : " << queryfile << endl;
    cout << "Output file   : " << outputfile << endl;
    cout << "Functions  (k): " << noFunctions << endl;
    cout << "Max points to control (M): " << max_points_to_control << endl;
    cout << "Probes (probes): " << probes << endl;
}

void CommandLineParser::parseFrechet(int argc, char *argv[]) {
    no_nearest_neighbors = 1;
    noFunctions = 4;
    nohashtables = 5;
    metric = "";

    for (int i = 1; i < argc; i++) {
        if (argv[i] == std::string("-d") || argv[i] == std::string("-delta")) {
            delta = atof(argv[i + 1]);
        }

        if (argv[i] == std::string("-m") || argv[i] == std::string("-metric")) {
            metric = argv[i + 1];
        }
    }

    if (metric == "" || (metric != "discrete" && metric != "continuous")) {
        cout << "Please define a valid metric by -metric option."
                "\nOptions are:\n1. discrete, \n2. continuous.\n";
        exit(1);
    }

    cout << "Input file    : " << inputfile << endl;
    cout << "Query file    : " << queryfile << endl;
    cout << "Output file   : " << outputfile << endl;
    cout << "d (delta): " << delta << endl;
    cout << "metric (metric): " << metric << endl;
}

void CommandLineParser::parseClustering(int argc, char *argv[]) {
    inputfile = "";
    configurationfile = "";
    outputfile = "";
    silhouette = false;
    complete = false;

    // parse input file, configuration file, output file
    parseBasicClusteringParams(argc, argv);
    checkForEmptyBasicClusteringParamsError();

    for (int i = 1; i < argc; i++) {
        if (argv[i] == std::string("-update")) {
            update = argv[i + 1];
        }

        if (argv[i] == std::string("-assignment")) {
            assignment = argv[i + 1];
        }

        if (argv[i] == std::string("-complete")) {
            complete = true;
        }

        if (argv[i] == std::string("-silhouette")) {
            silhouette = true;
        }
    }

    checkForEligibleUpdateAndAssignmentCombinations();

    cout << "Input file    : " << inputfile << endl;
    cout << "Configuration file    : " << configurationfile << endl;
    cout << "Output file   : " << outputfile << endl;
    cout << "Update: " << update << endl;
    cout << "Assignment: " << assignment << endl;
    cout << "Complete: " << complete << endl;
    cout << "Silhouette: " << silhouette << endl;
}

void CommandLineParser::parseSearch(int argc, char *argv[]) {
    algorithm = "";
    inputfile = "";
    queryfile = "";
    outputfile = "";

    // parse algorithm, input file, query file, output file
    parseBasicSearchParams(argc, argv);
    checkForEmptyBasicSearchParamsError();

    if (algorithm == "LSH") {
        parseLSH(argc, argv);
        return;
    }

    if (algorithm == "Hypercube") {
        parseCube(argc, argv);
        return;
    }

    if (algorithm == "Frechet") {
        parseFrechet(argc, argv);
        return;
    }
}

void CommandLineParser::parseBasicSearchParams(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (argv[i] == string("-algorithm")) {
            algorithm = argv[i + 1];
        }

        if (argv[i] == string("-i")) {
            inputfile = argv[i + 1];
        }

        if (argv[i] == string("-q")) {
            queryfile = argv[i + 1];
        }

        if (argv[i] == string("-o")) {
            outputfile = argv[i + 1];
        }
    }
}

void CommandLineParser::checkForEmptyBasicSearchParamsError() {
    if (algorithm == "" || (algorithm != "LSH" && algorithm != "Hypercube" && algorithm != "Frechet")) {
        cout << "Please define a valid algorithm by -algorithm option.\n"
                "Options are:\n1. LSH, \n2. Hypercube or \n3. Frechet\n";
        exit(1);
    }

    if (inputfile == "") {
        cout << "Please define an input file by -i option.\n";
        exit(1);
    }

    if (queryfile == "") {
        cout << "Please define a query file by -q option.\n";
        exit(1);
    }

    if (outputfile == "") {
        cout << "Please define an output file by -o option.\n";
        exit(1);
    }
}

void CommandLineParser::parseBasicClusteringParams(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
        if (argv[i] == string("-i")) {
            inputfile = argv[i + 1];
        }

        if (argv[i] == string("-c")) {
            configurationfile = argv[i + 1];
        }

        if (argv[i] == string("-o")) {
            outputfile = argv[i + 1];
        }
    }
}

void CommandLineParser::checkForEmptyBasicClusteringParamsError() {
    if (inputfile == "") {
        cout << "Please define an input file by -i option.\n";
        exit(1);
    }

    if (configurationfile == "") {
        cout << "Please define a configuration file by -c option.\n";
        exit(1);
    }

    if (outputfile == "") {
        cout << "Please define an output file by -o option.\n";
        exit(1);
    }
}

void CommandLineParser::checkForEligibleUpdateAndAssignmentCombinations() {
    if (!(
            (assignment == CLASSIC_ASSIGNMENT && update == MEAN_VECTOR_UPDATE)
            || (assignment == LSH_ASSIGNMENT && update == MEAN_VECTOR_UPDATE)
            || (assignment == HYPERCUBE_ASSIGNMENT && update == MEAN_VECTOR_UPDATE)
            || (assignment == CLASSIC_ASSIGNMENT && update == MEAN_FRECHET_UPDATE)
            || (assignment == LSH_FRECHET_ASSIGNMENT && update == MEAN_FRECHET_UPDATE)
    )) {
        cout << "Please an eligible combination for clustering assignment and update.\n";
        exit(1);
    }
}