#ifndef GENERATOR_H
#define GENERATOR_H

#include <random>

#include "DataLine.h"

// https://stackoverflow.com/questions/288739/generate-random-numbers-uniformly-over-an-entire-range

template<typename T>
T urandom(T range_from, T range_to) {
    static std::random_device rand_dev;
    static std::mt19937 generator(rand_dev());
    std::uniform_int_distribution<T> distr(range_from, range_to);
    return distr(generator);
}

template<typename T>
T urandomf(T range_from, T range_to) {
    static std::random_device rand_dev;
    static std::mt19937 generator(rand_dev());
    std::uniform_real_distribution<T> distr(range_from, range_to);
    return (float) distr(generator);
}

template<typename T>
T nrandom(T m, T e) {
    static std::default_random_engine generator;
    std::normal_distribution<double> distr(m, e);
    return distr(generator);
}

class Generator {
public:
    float generateNormalVariable(float mean, float variance); // N(0,1)

    float generateUniformVariable(int min, int max); // U(min,max)

    DataLine generate_u(int d);

    float generate_t(int W);

    int generate_r();

};

#endif /* GENERATOR_H */

