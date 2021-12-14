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





float DistanceCalculator::calculateDistanceContinuous(DataCurve &a, DataCurve&b) {
    return 0.0f;
}

float DistanceCalculator::calculateDistance(DataCurve &a, DataCurve&b) { // Discrete Frechet
    unsigned curve1_complexity = a.x.size();
    unsigned curve2_complexity = b.x.size();

    vector<vector<float>> dists_a(curve1_complexity, vector<float>(curve2_complexity));
    vector<vector<float>> dists(curve1_complexity, vector<float>(curve2_complexity));

    for (unsigned i = 0; i < curve1_complexity; ++i) {
        for (unsigned j = 0; j < curve2_complexity; ++j) {
            float x1 = a.x[i];
            float y1 = a.y[i];

            float x2 = b.x[j];
            float y2 = b.y[j];

            dists[i][j] = (x1-x2)*(x1-x2) + (y1-y2)*(y1-y2);
        }
    }

    for (unsigned i = 0; i < curve1_complexity; ++i) {
        for (unsigned j = 0; j < curve2_complexity; ++j) {
            if (i == 0 and j == 0) {
                dists_a[i][j] = dists[i][j];
            } else if (i == 0 and j > 0) {
                dists_a[i][j] = max(dists_a[i][j-1], dists[i][j]);
            } else if (i > 0 and j == 0) {
                dists_a[i][j] = max(dists_a[i-1][j], dists[i][j]);
            } else {
                dists_a[i][j] = max(min(min(dists_a[i-1][j], dists_a[i-1][j-1]), dists_a[i][j-1]), dists[i][j]);
            }
        }
    }

    return sqrt(dists_a[curve1_complexity - 1][curve2_complexity - 1]);;
}

