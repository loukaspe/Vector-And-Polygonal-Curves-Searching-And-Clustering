#include "DistanceCalculator.h"
#include "errors.h"

#include <cmath>

DistanceCalculator::DistanceCalculator(bool calculate_root):calculate_root(calculate_root) {
    
}

float DistanceCalculator::calculateDistance(DataLine & a, DataLine & b) {
    int d1 = a.getDimension();
    int d2 = b.getDimension();
    
    if (d1 != d2) {
        exit(DIMENSION_MISMATCH_DISTANCE);
    }
    
    float dist = 0.0f;
    
    for (int i=0;i<d1;i++) {
        dist = dist + (a.data[i] - b.data[i])*(a.data[i] - b.data[i]);
    }
    
    if (calculate_root) {
        dist = sqrt(dist);
    }
    
    return dist;
}

