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
    unsigned long circulatingShares;
    randomGen rnd;
   public:
    Stock(std::string newSector, std::string newName, std::string newTicker, float newPrice, unsigned long long newCirculatingShares)
        : Asset(newName, newTicker, newPrice), sector(newSector), circulatingShares(newCirculatingShares) {};
    void updatePrice() {
        float changePercent = this->rnd.priceRandomGen(0.25, 0.9, 0.1) / 100;
        Asset::setPrice(Asset::getPrice() * (1 + changePercent));
    };
    void updatePrice(float mean, float stdDev, float skewness) {
        float changePercent = this->rnd.priceRandomGen(mean, stdDev, skewness) / 100;
        Asset::setPrice(Asset::getPrice() * (1 + changePercent));
    };
    unsigned long getCirculatingShares(){
        return this->circulatingShares;
    };
};

#endif