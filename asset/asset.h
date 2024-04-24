#ifndef ASSET_H
#define ASSET_H
#include <string>

class asset
{
private:
    std::string ticker, name;
    float price;
public:
    asset(): name("NULL"), ticker("NULL"), price(-1) {};
    asset(std::string newName, std::string newTicker, float newPrice): name(newName), ticker(newTicker), price(newPrice) {};
    float getPrice() const {return price;};
    std::string getName() const {return name;};
    std::string getTicker() const {return ticker;};
    virtual float updatePrice() {
        float changePercent = (rand() % 100 - 50) * 0.01; // Random change between -0.5% to 0.5%
        price *= (1 + changePercent);
    };
    ~asset() {};
};

#endif