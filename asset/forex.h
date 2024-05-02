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
        randomGen rnd;
        float changePercent = rnd.priceRandomGen(0, 0.3) / 100;
        Asset::setPrice(Asset::getPrice() * (1 + changePercent));
    };
    void updatePrice(double mean, double stdDev, float skweness) {
        randomGen rnd;
        float changePercent = rnd.priceRandomGen(mean, stdDev, skweness) / 100;
        Asset::setPrice(Asset::getPrice() * (1 + changePercent));
    };
};

#endif
*/