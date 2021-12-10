#include "Logger.h"

Logger::Logger(string logFilename): logFileName(logFilename) {
    this->logFile.open(logFileName, ios::out | ios::app);
}

void Logger::log(string output) {
    if(this->logFile.is_open()) {
        this->logFile << output;
        return;
    }

    this->logFile.open(logFileName, ios::out | ios::app);
    this->logFile << output;
}

void Logger::close() {
    this->logFile.close();
}

Logger::~Logger() {
    this->close();
}
