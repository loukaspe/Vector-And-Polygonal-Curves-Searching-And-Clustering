
#ifndef GRID_H
#define GRID_H

#include <vector>

using namespace std;

class Grid {
public:
    vector<double> t;
    double delta;

    void setup(double _delta, int dimensions);
};
#endif /* GRID_H */

