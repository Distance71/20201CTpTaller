#include "RandomGenerate.h"

RandomGenerate::RandomGenerate(){};

RandomGenerate::~RandomGenerate(){};

unsigned int RandomGenerate::generate(unsigned int intervals){
    return (1 + (rand() % intervals));
}

