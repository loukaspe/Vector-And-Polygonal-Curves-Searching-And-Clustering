#ifndef VECTOR_SEARCHING_AND_CLUSTERING_LOGGER_H
#define VECTOR_SEARCHING_AND_CLUSTERING_LOGGER_H

#include <string>
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>

using namespace std;

class Logger {
public:
    Logger(string);
    void close();
    void log(string);

    virtual ~Logger();

private:
    string logFileName;
    ofstream logFile;
};


#endif
