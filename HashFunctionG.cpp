#include "HashFunctionG.h"
#include "HashFunctionCalculator.h"
#include "Generator.h"

HashFunctionG::HashFunctionG() {

}

HashFunctionG::HashFunctionG(const HashFunctionG& orig) {

}

HashFunctionG::~HashFunctionG() {
    delete [] r;
}

void HashFunctionG::setup(int K) {
    k = K;
    
    r = new int[k];
    
    Generator gen;
    for (int i=0;i<k;i++) {
        r[i] = gen.generate_r();
    }
}

int HashFunctionG::value(int hi[]) {
    unsigned M = 4294967291;
    HashFunctionCalculator calc;
    return calc.g(hi, r, M, k);
}
