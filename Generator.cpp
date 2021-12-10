#include "Generator.h"

float Generator::generateNormalVariable(float mean, float variance) {
    return nrandom(mean, variance);

}

float Generator::generateUniformVariable(int min, int max) {
    return urandom(min, max);
}

DataLine Generator::generate_u(int d) {
    DataLine v;

    for (int i = 0; i < d; i++) {
        float value = generateNormalVariable(0, 1);
        v.data.push_back(value);
    }

    return v;
}

float Generator::generate_t(int W) {
    return generateUniformVariable(0, W - 1);
}

int Generator::generate_r() {
    return generateUniformVariable(0, INT32_MAX - 1);
}

