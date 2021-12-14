#ifndef DATACURVE_H
#define DATACURVE_H

#include <vector>
#include <string>

#include "Grid.h"

using namespace std;

class DataCurve {
public:
    int offset;
    string id;

    vector<float> x;
    vector<float> y;

    void setup(vector<float> & data);
    vector<float> concatenate();

    DataCurve snap(Grid & grid);

    bool equals(DataCurve & other);
private:

};


#endif /* DATACURVE_H */

