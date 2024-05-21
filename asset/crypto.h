#ifndef CRYPTO_H
#define CRYPTO_H
#include "asset.h"
#include "events.h"
#include "../function/randomGen.h"
#include <string>

class Crypto: public Asset
{
private:
    unsigned long circulatingAmount;
    randomGen rnd;
public:
    Crypto(std::string newName, std::string newTicker, float newPrice, unsigned long long newCirculatingAmount)
        : Asset(newName, newTicker, newPrice), circulatingAmount(newCirculatingAmount) {};
    void updatePrice() {
        float changePercent = this->rnd.priceRandomGen(-0.8, 3.2, 0.2) / 100;
        Asset::setPrice(Asset::getPrice() * (1 + changePercent));
    };
    void updatePrice(double mean, double stdDev, float skewness) {
        float changePercent = this->rnd.priceRandomGen(mean, stdDev, skewness) / 100;
        Asset::setPrice(Asset::getPrice() * (1 + changePercent));
    };
    unsigned long getCirculatingAmount(){
        return this->circulatingAmount;
    };

};

#endif