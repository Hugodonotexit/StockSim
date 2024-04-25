#ifndef CRYPTO_H
#define CRYPTO_H
#include "asset.h"
#include "../randomGen.h"
#include <string>

class Crypto: public Asset
{
private:
    unsigned long long circulatingAmount;
public:
    Crypto(std::string newName, std::string newTicker, float newPrice, unsigned long long newCirculatingAmount)
        : Asset(newName, newTicker, newPrice), circulatingAmount(newCirculatingAmount) {};
    void updatePrice() {
        float changePercent = randomGen(0, 3) / 100;
        Asset::setPrice(Asset::getPrice() * (1 + changePercent));
    };
};

#endif