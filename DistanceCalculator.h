
#ifndef DISTANCECALCULATOR_H
#define DISTANCECALCULATOR_H

#include "DataLine.h"


#include <string>

using namespace std;


class DistanceCalculator {    
public:
    const bool calculate_root;
    
    DistanceCalculator(bool calculate_root);
    
    float calculateDistance(DataLine & a, DataLine & b, string metric = "eulidean"); // L2
    
    float calculateDistance(DataCurve &a, DataCurve&b); // Frechet discrete
    
    float calculateDistanceContinuous(DataCurve &a, DataCurve&b); // Frechet continuous
    
    DataCurve *  meanCurve(DataCurve &a, DataCurve&b);
};

#endif /* DISTANCECALCULATOR_H */

