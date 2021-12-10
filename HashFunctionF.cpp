#include "HashFunctionF.h"

HashFunctionF::HashFunctionF() {

}

HashFunctionF::HashFunctionF(const HashFunctionF& orig) {

}

HashFunctionF::~HashFunctionF() {

}

 int HashFunctionF::value(int g) {
     if (memory[g] == 0) {
         int y = rand()%2;
         
         if (y==0){
             memory[g] = -1; //0 
         } else {
             memory[g] = 1; // 1
         }
         
         return y;
     } else {
         if (memory[g] == -1) {
             return 0;
         } else {
             return 1;
         }
     }
 }

