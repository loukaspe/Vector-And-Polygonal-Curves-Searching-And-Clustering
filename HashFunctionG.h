#ifndef HASHFUNCTIONG_H
#define HASHFUNCTIONG_H

class HashFunctionG {
public:
    HashFunctionG();
    HashFunctionG(const HashFunctionG& orig);
    virtual ~HashFunctionG();
    
    int * r;
    int k;
    
    void setup(int k);
    
    int value(int h[]);
    
};

#endif /* HASHFUNCTIONG_H */

