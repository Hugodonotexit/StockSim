#ifndef RANDOMGEN_H
#define RANDOMGEN_H
#include <random>

inline float randomGen(float mean, float stdDev) {
    std::random_device randSeed;  
    std::mt19937 gen(randSeed()); 
    std::normal_distribution<> dist(mean, stdDev); 
    return dist(gen);
}

inline float eventRandomGen(float chance) {
    std::random_device randSeed;  
    std::mt19937 gen(randSeed()); 
    std::bernoulli_distribution dist(chance); 
    return dist(gen);
}
#endif