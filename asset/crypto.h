#ifndef CRYPTO_H
#define CRYPTO_H
#include "asset.h"
#include "../randomGen.h"
#include <string>

class crypto: public asset
{
private:
    
public:
    crypto() {};
    void updatePrice() {
        float changePercent = randomGen(0, 3) / 100;
        asset::setPrice(asset::getPrice() * (1 + changePercent));
    };
    ~crypto() {};
};

#endif