#ifndef STOCK_H
#define STOCK_H
#include "asset.h"
#include "events.h"
#include "../function/randomGen.h"
#include <string>

class Stock: public Asset
{
    private:
    std::string sector;
    unsigned long long circulatingShares;
   public:
    Stock(std::string newSector, std::string newName, std::string newTicker, float newPrice, unsigned long long newCirculatingShares)
        : Asset(newName, newTicker, newPrice), sector(newSector), circulatingShares(newCirculatingShares) {};
    void updatePrice() {
        randomGen rnd;
        float changePercent = rnd.priceRandomGen(0.25, 0.9) / 100;
        Asset::setPrice(Asset::getPrice() * (1 + changePercent));
    };
    void updatePrice(double mean, double stdDev) {
        randomGen rnd;
        float changePercent = rnd.priceRandomGen(mean, stdDev) / 100;
        Asset::setPrice(Asset::getPrice() * (1 + changePercent));
    };
};

#endif