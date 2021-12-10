#include "InnerProductCalculator.h"
#include "errors.h"

float InnerProductCalculator::calculateInnerProduct(DataLine & a, DataLine & b) {
    int d1 = a.getDimension();
    int d2 = b.getDimension();

    if (d1 != d2) {
        exit(DIMENSION_MISMATCH_PRODUCT);
    }

    float product = 0.0f;

    for (int i = 0; i < d1; i++) {
        product = product + a.data[i]*b.data[i];
    }

    return product;
}

