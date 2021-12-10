#include "HashFunctionH.h"
#include "Generator.h"
#include "HashFunctionCalculator.h"

HashFunctionH::HashFunctionH() {

}

HashFunctionH::HashFunctionH(const HashFunctionH& orig) {

}

HashFunctionH::~HashFunctionH() {

}

void HashFunctionH::setup(int w, int d) {
    Generator gen;

    t = gen.generate_t(w);
    u = gen.generate_u(d);
    W = w;
}

int HashFunctionH::value(DataLine & x) {
    HashFunctionCalculator calc;

    return calc.h(x, u, t, W);
}

