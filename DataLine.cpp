#include "DataLine.h"

int DataLine::getDimension() {
    return (int) data.size();
}

void DataLine::padding(unsigned dimension) {
    while (data.size() < dimension) {
        data.push_back(1000000);
    }
}