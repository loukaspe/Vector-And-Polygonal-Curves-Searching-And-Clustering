#include "DistanceCalculator.h"
#include "errors.h"

#include <cmath>

DistanceCalculator::DistanceCalculator(bool calculate_root) : calculate_root(calculate_root) {

}

float DistanceCalculator::calculateDistance(DataLine & a, DataLine & b) {
    int d1 = a.getDimension();
    int d2 = b.getDimension();

    if (d1 != d2) {
        exit(DIMENSION_MISMATCH_DISTANCE);
    }

    float dist = 0.0f;

    for (int i = 0; i < d1; i++) {
        dist = dist + (a.data[i] - b.data[i])*(a.data[i] - b.data[i]);
    }

    if (calculate_root) {
        dist = sqrt(dist);
    }

    return dist;
}

float DistanceCalculator::calculateDistanceContinuous(DataCurve &a, DataCurve&b) {
    // TODO

    // files from fred:

    // repo: https://github.com/derohde/Fred/blob/master/src/frechet.cpp
    //  types.hpp, config.cpp/hpp, curve.cpp/hpp, frechet.cpp/hpp, interval.cpp/hpp, point.cpp/hpp, simplification.cpp/hpp.
    return 0.0f;
}

static float ** makeMatrix(int rows, int columns) {
    float ** array = new float*[rows];

    for (int i = 0; i < rows; i++) {
        array[i] = new float[columns];
    }
    return array;
}

static void destroyMatrix(float** array, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        delete [] array[i];
    }
    delete [] array;
}

float DistanceCalculator::calculateDistance(DataCurve &a, DataCurve&b) { // Discrete Frechet
    int curve1_complexity = (int) a.x.size();
    int curve2_complexity = (int) b.x.size();

    float ** dists_a = makeMatrix(curve1_complexity, curve2_complexity);
    float ** dists = makeMatrix(curve1_complexity, curve2_complexity);

    for (int i = 0; i < curve1_complexity; ++i) {
        for (int j = 0; j < curve2_complexity; ++j) {
            float dx = a.x[i] - b.x[j];
            float dy = a.y[i] - b.y[j];

            dists[i][j] = dx * dx + dy*dy;
        }
    }

    for (int i = 0; i < curve1_complexity; ++i) {
        for (int j = 0; j < curve2_complexity; ++j) {
            if (i == 0 and j == 0) {
                dists_a[i][j] = dists[i][j];
            } else if (i == 0 and j > 0) {
                dists_a[i][j] = max(dists_a[i][j - 1], dists[i][j]);
            } else if (i > 0 and j == 0) {
                dists_a[i][j] = max(dists_a[i - 1][j], dists[i][j]);
            } else {
                dists_a[i][j] = max(min(min(dists_a[i - 1][j], dists_a[i - 1][j - 1]), dists_a[i][j - 1]), dists[i][j]);
            }
        }
    }

    float dist = sqrt(dists_a[curve1_complexity - 1][curve2_complexity - 1]);

    destroyMatrix(dists_a, curve1_complexity, curve2_complexity);
    destroyMatrix(dists, curve1_complexity, curve2_complexity);

    return dist;
}

DataCurve DistanceCalculator::meanCurve(DataCurve &a, DataCurve&b) {
    int curve1_complexity = (int) a.x.size();
    int curve2_complexity = (int) b.x.size();

    float dists_a[curve1_complexity][curve2_complexity];
    float dists[curve1_complexity][curve2_complexity];

    for (int i = 0; i < curve1_complexity; ++i) {
        for (int j = 0; j < curve2_complexity; ++j) {
            float dx = a.x[i] - b.x[j];
            float dy = a.y[i] - b.y[j];

            dists[i][j] = dx * dx + dy*dy;
        }
    }

    for (int i = 0; i < curve1_complexity; ++i) {
        for (int j = 0; j < curve2_complexity; ++j) {
            if (i == 0 and j == 0) {
                dists_a[i][j] = dists[i][j];
            } else if (i == 0 and j > 0) {
                dists_a[i][j] = max(dists_a[i][j - 1], dists[i][j]);
            } else if (i > 0 and j == 0) {
                dists_a[i][j] = max(dists_a[i - 1][j], dists[i][j]);
            } else {
                dists_a[i][j] = max(min(min(dists_a[i - 1][j], dists_a[i - 1][j - 1]), dists_a[i][j - 1]), dists[i][j]);
            }
        }
    }

    DataCurve res;

    int p = curve1_complexity - 1; // m1
    int q = curve2_complexity - 1; // m2

    int mx = (a.x[p] + b.x[p]) / 2;
    int my = (a.y[p] + b.y[p]) / 2;

    res.x.push_back(mx);
    res.y.push_back(my);


    while (p > 0 && q > 0) {
        float dist1 = dists_a[p - 1][q];
        float dist2 = dists_a[p][q - 1];
        float dist3 = dists_a[p - 1][q - 1];

        if (dist1 < dist2 && dist1 < dist3) {
            --p;
        } else if (dist2 < dist1 && dist2 < dist3) {
            --q;
        } else {
            --p;
            --q;
        }

        int mx = (a.x[p] + b.x[p]) / 2;
        int my = (a.y[p] + b.y[p]) / 2;

        res.x.push_back(mx);
        res.y.push_back(my);
    }

    while (p > 0 && q != 0) {
        --p;

        int mx = (a.x[p] + b.x[p]) / 2;
        int my = (a.y[p] + b.y[p]) / 2;

        res.x.push_back(mx);
        res.y.push_back(my);
    }

    while (p != 0 && q > 0) {
        --q;

        int mx = (a.x[p] + b.x[p]) / 2;
        int my = (a.y[p] + b.y[p]) / 2;

        res.x.push_back(mx);
        res.y.push_back(my);
    }

    return res;
}

