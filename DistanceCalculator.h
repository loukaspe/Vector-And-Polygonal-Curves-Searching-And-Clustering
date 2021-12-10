
#ifndef DISTANCECALCULATOR_H
#define DISTANCECALCULATOR_H

#include "DataLine.h"


class DistanceCalculator {    
public:
    const bool calculate_root;
    
    DistanceCalculator(bool calculate_root);
    
    float calculateDistance(DataLine & a, DataLine & b);
};

#endif /* DISTANCECALCULATOR_H */

