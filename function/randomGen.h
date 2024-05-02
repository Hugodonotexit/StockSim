#ifndef RANDOMGEN_H
#define RANDOMGEN_H
#include <random>

class randomGen
{
public:
    randomGen();
    float priceRandomGen(float, float, float);
    bool eventRandomGen(float);
    ~randomGen();
};


#endif