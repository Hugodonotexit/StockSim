#include "randomGen.h"

randomGen::randomGen() {};
/*
Xi'an 2017, Sampling from Skew Normal Distribution, Stack Exchange, 
viewed 2 May 2024, 
<https://stats.stackexchange.com/questions/316314/sampling-from-skew-normal-distribution>.
*/
float randomGen::priceRandomGen(float mean, float stdDev, float skewness) {
    std::random_device randSeed;  
    std::mt19937 gen(randSeed());  
    std::normal_distribution<> norDist(0, 1);
    double norDistValue[2] = {fabs(norDist(gen)), norDist(gen)};
    float skewValue = (norDistValue[0] * skewness + norDistValue[1]) / sqrt(1+ skewness * skewness); 
    float skewNormalValue = mean + stdDev * skewValue;
    return skewNormalValue;
}

bool randomGen::eventRandomGen(float chance) {
    std::random_device randSeed;  
    std::mt19937 gen(randSeed()); 
    std::bernoulli_distribution dist(chance); 
    return dist(gen);
}

randomGen::~randomGen() {};