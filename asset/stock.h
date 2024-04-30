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
        float changePercent = randomGen(0.25, 0.9) / 100;
        Asset::setPrice(Asset::getPrice() * (1 + changePercent));
    };
    void updatePrice(double mean, double stdDev) {
        float changePercent = randomGen(mean, stdDev) / 100;
        Asset::setPrice(Asset::getPrice() * (1 + changePercent));
    };
    
    // used for sorting the set of stocks such that the lists tickers are in alphabetical order
    bool operator<(const Stock& other) const {
        return this->getTicker() < other.getTicker(); 
    }
};

#endif