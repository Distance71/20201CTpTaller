#ifndef _RANDOMGENERATE_H_
#define _RANDOMGENERATE_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctime>

using namespace std;
// Se encarga de devolver un intervalo random

class RandomGenerate {

    public:
    RandomGenerate();
    static unsigned int generate(unsigned int intervals);
    ~RandomGenerate();
};

#endif
