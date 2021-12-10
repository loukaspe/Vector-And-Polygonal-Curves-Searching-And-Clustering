
#ifndef HASHFUNCTIONH_H
#define HASHFUNCTIONH_H

#include "DataLine.h"


class HashFunctionH {
public:
    HashFunctionH();
    HashFunctionH(const HashFunctionH& orig);
    virtual ~HashFunctionH();
    
    DataLine u;
    float t;
    int W;
    
    
    void setup(int W, int d);
    
    int value(DataLine & x);

};


#endif /* HASHFUNCTIONH_H */

