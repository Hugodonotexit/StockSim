#ifndef FOREX_H
#define FOREX_H
#include "asset.h"
#include <string>

class forex: public asset
{
private:
    
public:
    forex();
    float updatePrice() {
        float changePercent = (rand() % 100 - 50) * 0.005; // Random change between -0.25% to 0.25%
        asset::setPrice(asset::getPrice() * (1 + changePercent));
    };
    void setPrice(float newPrice) {
        asset::setPrice(newPrice);
    };
    ~forex();
};

#endif