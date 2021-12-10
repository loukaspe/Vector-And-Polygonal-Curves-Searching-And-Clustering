
#ifndef HASHFUNCTIONF_H
#define HASHFUNCTIONF_H

#include <map>

using namespace std;

class HashFunctionF {
public:
    HashFunctionF();
    HashFunctionF(const HashFunctionF& orig);
    virtual ~HashFunctionF();
    
    int value(int g); // 0 or 1
private:
    map<int,int> memory; // {-1, +1}
    

};

#endif /* HASHFUNCTIONF_H */

