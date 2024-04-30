#include "randomGen.h"

randomGen::randomGen() {};

float randomGen::priceRandomGen(float mean, float stdDev) {
    std::random_device randSeed;  
    std::mt19937 gen(randSeed()); 
    std::normal_distribution<> dist(mean, stdDev); 
    return dist(gen);
}

float randomGen::eventRandomGen(float chance) {
    std::random_device randSeed;  
    std::mt19937 gen(randSeed()); 
    std::bernoulli_distribution dist(chance); 
    return dist(gen);
}

randomGen::~randomGen() {};