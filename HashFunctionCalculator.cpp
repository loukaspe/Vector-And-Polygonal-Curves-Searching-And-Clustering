#include <cmath>

#include "HashFunctionCalculator.h"
#include "InnerProductCalculator.h"

int HashFunctionCalculator::h(DataLine & p, DataLine & u, int t, int W) {
    InnerProductCalculator calc;

    float result = floor((calc.calculateInnerProduct(p, u) + t) / W);

    return (int) result;
}

unsigned HashFunctionCalculator::g(int hi[], int ri[], unsigned M, int k) {
    int result = 0;

    for (int i = 0; i < k; i++) {
        result = result + mod(hi[i] * ri[i], M);
    }

    return mod(result, M);
}

int HashFunctionCalculator::t(int fi, int T) {
    return fi % T;
}

unsigned HashFunctionCalculator::mod(int m, unsigned n) { // m mod n
    return (unsigned) ( (long)m + (long) n) % n;
}