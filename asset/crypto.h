#ifndef CRYPTO_H
#define CRYPTO_H
#include "asset.h"
#include "events.h"
#include "../function/randomGen.h"
#include <string>

class Crypto: public Asset
{
private:
    unsigned long long circulatingAmount;
public:
    Crypto(std::string newName, std::string newTicker, float newPrice, unsigned long long newCirculatingAmount)
        : Asset(newName, newTicker, newPrice), circulatingAmount(newCirculatingAmount) {};
    void updatePrice() {
        randomGen rnd;
        float changePercent = rnd.priceRandomGen(-0.1, 3) / 100;
        Asset::setPrice(Asset::getPrice() * (1 + changePercent));
    };
    void updatePrice(double mean, double stdDev) {
        randomGen rnd;
        float changePercent = rnd.priceRandomGen(mean, stdDev) / 100;
        Asset::setPrice(Asset::getPrice() * (1 + changePercent));
    };

    // used for sorting the set of cryptos such that the lists tickers are in alphabetical order
    bool operator<(const Crypto& other) const {
        return this->getTicker() < other.getTicker(); 
    }
};

#endif