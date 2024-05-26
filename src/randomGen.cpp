#include "../include/randomGen.h"

randomGen::randomGen() {
    std::mt19937 gen1(this->randSeed());
    this->seed = gen1;
};
/*
Xi'an 2017, Sampling from Skew Normal Distribution, Stack Exchange, 
viewed 2 May 2024, 
<https://stats.stackexchange.com/questions/316314/sampling-from-skew-normal-distribution>.
*/
float randomGen::priceRandomGen(float mean, float stdDev, float skewness) {
    std::normal_distribution<> norDist(0, 1);
    double norDistValue[2] = {fabs(norDist(this->seed)), norDist(this->seed)};
    float skewValue = (norDistValue[0] * skewness + norDistValue[1]) / sqrt(1+ skewness * skewness); 
    float skewNormalValue = mean + stdDev * skewValue;
    return skewNormalValue;
}

double randomGen::RandGen(double min, double max) {
    std::uniform_real_distribution<double> result(min,max);
    return result(this->seed);
}

bool randomGen::eventRandomGen(float chance) { 
    std::bernoulli_distribution dist(chance); 
    return dist(this->seed);
}

randomGen::~randomGen() {};