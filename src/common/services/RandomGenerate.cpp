#include "RandomGenerate.h"

RandomGenerate::RandomGenerate(){};

RandomGenerate::~RandomGenerate(){};

//TODO revisar por q siempre devuelve el mismo nro no tiene sentido
unsigned int RandomGenerate::generate(unsigned int intervals){
    srand((unsigned) time(0));
    return (1 + (rand() % intervals));
}

