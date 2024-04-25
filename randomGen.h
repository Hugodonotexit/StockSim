#ifndef RANDOMGEN_H
#define RANDOMGEN_H
#include <random>

using namespace std;

float randomGen(float mean, float stdDev) {
    random_device randSeed;
    mt19937 gen(randSeed());
    normal_distribution<> normalDist(mean, stdDev);
    return normalDist(gen);
}

#endif