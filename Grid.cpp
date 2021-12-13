#include <vector>

#include "Grid.h"
#include "Generator.h"

void Grid::setup(double _delta, int dimensions) {
    for (int i = 0; i < dimensions; i++) {
        double ti = urandomf<double>(0,_delta);
        t.push_back(ti);
    }

    delta = _delta;
}