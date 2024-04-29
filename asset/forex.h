/*
#ifndef FOREX_H
#define FOREX_H
#include "asset.h"
#include "events.h"
#include "../function/randomGen.h"
#include <string>

class Forex: public Asset
{
public:
    Forex(std::string newName, std::string newTicker, float newPrice)
        : Asset(newName, newTicker, newPrice) {};
    using Asset::Asset;
    void updatePrice() {
        float changePercent = randomGen(0, 0.3) / 100;
        Asset::setPrice(Asset::getPrice() * (1 + changePercent));
    };
    void updatePrice(double mean, double stdDev) {
        float changePercent = randomGen(mean, stdDev) / 100;
        Asset::setPrice(Asset::getPrice() * (1 + changePercent));
    };
};

#endif
*/