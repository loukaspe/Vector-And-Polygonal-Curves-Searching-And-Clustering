#include "InnerProductCalculator.h"
#include "errors.h"

float InnerProductCalculator::calculateInnerProduct(DataLine & a, DataLine & b) {
    int d1 = a.getDimension();
    int d2 = b.getDimension();
    //
    //    if (d1 != d2) {
    //        printf("DIMENSION_MISMATCH_PRODUCT \n");
    //        exit(DIMENSION_MISMATCH_PRODUCT);
    //    }

    int d = min(d1, d2);

    int dm = max(d1, d2);

    float product = 0.0f;

    for (int i = 0; i < d; i++) {
        product = product + a.data[i] * b.data[i];
    }

    for (int i = d; i < dm; i++) {
        float v1 = 1000000;
        float v2 = 1000000;
        
        if (a.data.size() > (unsigned) i) {
            v1 =a.data[i];
        }
        
        if (b.data.size() > (unsigned) i) {
            v2 =b.data[i];
        }

        product = product + v1*v2;
    }
    return product;
}

