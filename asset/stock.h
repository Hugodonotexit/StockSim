#ifndef STOCK_H
#define STOCK_H
#include "asset.h"
#include "../randomGen.h"
#include <string>

class stock: public asset
{
   public:
    stock() {};
    void updatePrice() {
        float changePercent = randomGen(0, 0.9) / 100;
        asset::setPrice(asset::getPrice() * (1 + changePercent));
    };
    ~stock() {};
};

#endif