#ifndef ASSET_H
#define ASSET_H
#include <string>
#include "../randomGen.h"

class Asset
{
private:
    std::string name, ticker;
    float oldPrice, price;
public:
    Asset(): name("NULL"), ticker("NULL"), price(-1) {};
    Asset(std::string newName, std::string newTicker, float newPrice): name(newName), ticker(newTicker), price(newPrice) {};
    float getPrice() const {return this->price;};
    float getOldPrice() const {return this->oldPrice;};
    std::string getName() const {return this->name;};
    std::string getTicker() const {return this->ticker;};
    void setPrice(float newPrice) {
        this->oldPrice = this->price;
        this->price = newPrice;
    };
    virtual void updatePrice() {
        /* float changePercent = randomGen(0, 3) / 100;
        asset::setPrice(asset::getPrice() * (1 + changePercent)); 
        return changePercent;*/
    };
    virtual void updatePrice(double mean, double stdDev) {
        /* float changePercent = randomGen(mean, stdDev) / 100;
        asset::setPrice(asset::getPrice() * (1 + changePercent)); 
        return changePercent;*/
    };
    virtual ~Asset() {};
};

#endif