#ifndef CRYPTO_H
#define CRYPTO_H
#include "asset.h"
#include <string>

class crypto: public asset
{
private:
    
public:
    crypto() {};
    float updatePrice() {
        float changePercent = (rand() % 100 - 50) * 0.1; // Random change between -5% to 5%
        asset::setPrice(asset::getPrice() * (1 + changePercent));
    };
    void setPrice(float newPrice) {
        asset::setPrice(newPrice);
    };
    ~crypto() {};
};

#endif