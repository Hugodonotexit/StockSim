#ifndef STOCK_H
#define STOCK_H
#include "asset.h"
#include <string>

class stock: public asset
{
private:
    
public:
    stock();
    float updatePrice() {
        float changePercent = (rand() % 100 - 80) * 0.1; // Random change between -2% to 2%
        asset::setPrice(asset::getPrice() * (1 + changePercent));
    };
    void setPrice(float newPrice) {
        asset::setPrice(newPrice);
    };
    ~stock();
};

#endif