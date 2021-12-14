#include "DataCurve.h"
#include <cmath>

using namespace std;

void DataCurve::setup(vector<float> & data) {
    for (unsigned int i = 0; i < data.size(); i++) {
        x.push_back(i + 1);
        y.push_back(data[i]);
    }
}

vector<float> DataCurve::concatenate() {
    vector<float> vec;

    for (unsigned int i = 0; i < x.size(); i++) {
        vec.push_back(x[i]);
        vec.push_back(y[i]);
    }

    return vec;

}

// xi' = floor((x-t)/δ + 1/2)*δ + t

DataCurve DataCurve::snap(Grid & grid) {
    DataCurve gridcurve;

    double tx = grid.t[0];
    double ty = grid.t[1];
    double delta = grid.delta;

    for (unsigned int i = 0; i < x.size(); i++) {
        float snapped_x = floor((x[i] - tx) / delta + 1 / 2.0f) * delta + tx;
        float snapped_y = floor((y[i] - ty) / delta + 1 / 2.0f) * delta + ty;

        if (gridcurve.x.size() == 0) {
            gridcurve.x.push_back(snapped_x);
            gridcurve.y.push_back(snapped_y);
        } else {
            int lastpos = gridcurve.x.size() - 1;

            if (gridcurve.x[lastpos] != snapped_x && gridcurve.x[lastpos] != snapped_y) {
                gridcurve.x.push_back(snapped_x);
                gridcurve.y.push_back(snapped_y);
            }
        }
    }

    return gridcurve;
}

bool DataCurve::equals(DataCurve & other) {
    if (this->x.size() != other.x.size() || this->y.size() != other.y.size()) {
        return false;
    }

    for (unsigned int i = 0; i < x.size(); i++) {
        if (this->x[i] != other.x[i] || this->y[i] != other.y[i]) {
            return false;
        }
    }
    return true;
}