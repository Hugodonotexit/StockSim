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
        float changePercent = randomGen(-0.1, 3) / 100;
        Asset::setPrice(Asset::getPrice() * (1 + changePercent));
    };
    void updatePrice(double mean, double stdDev) {
        float changePercent = randomGen(mean, stdDev) / 100;
        Asset::setPrice(Asset::getPrice() * (1 + changePercent));
    };
};

#endif