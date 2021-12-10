#ifndef HASHFUNCTIONCALCULATOR_H
#define HASHFUNCTIONCALCULATOR_H

#include "DataLine.h"


class HashFunctionCalculator {
public:
    unsigned mod(int m, unsigned n);

    int h(DataLine & x, DataLine & u, int t, int W);
    
    unsigned g(int hi[], int ri[], unsigned M, int k );
    
    int t(int fi, int T);
};

#endif /* HASHFUNCTIONCALCULATOR_H */

