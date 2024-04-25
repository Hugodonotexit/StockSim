#ifndef ASSET_H
#define ASSET_H
#include <string>
#include "../randomGen.h"

class asset
{
private:
    std::string ticker, name;
    float oldPrice;
    float price;
public:
    asset(): name("NULL"), ticker("NULL"), price(-1) {};
    asset(std::string newName, std::string newTicker, float newPrice): name(newName), ticker(newTicker), price(newPrice) {};
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
    ~asset() {};
};

#endif