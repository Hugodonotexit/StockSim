#ifndef RANDOMGEN_H
#define RANDOMGEN_H
#include <random>

class randomGen
{
private:
    std::random_device randSeed;
public:
    randomGen();
    float priceRandomGen(float, float, float);
    bool eventRandomGen(float);
    ~randomGen();
};


#endif