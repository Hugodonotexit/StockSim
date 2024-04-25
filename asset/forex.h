#ifndef FOREX_H
#define FOREX_H
#include "asset.h"
#include "../randomGen.h"
#include <string>

class forex: public asset
{
public:
    forex() {};
    void updatePrice() {
        float changePercent = randomGen(0, 0.3) / 100;
        asset::setPrice(asset::getPrice() * (1 + changePercent));
    };
    ~forex() {};
};

#endif