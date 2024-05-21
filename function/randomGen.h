#ifndef RANDOMGEN_H
#define RANDOMGEN_H
#include <random>

class randomGen
{
private:
    std::random_device randSeed;
    std::mt19937 seed;
public:
    randomGen();
    float priceRandomGen(float, float, float);
    double RandGen(double, double);
    bool eventRandomGen(float);
    ~randomGen();
};


#endif