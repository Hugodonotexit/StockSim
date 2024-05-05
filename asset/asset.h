#ifndef ASSET_H
#define ASSET_H
#include <string>
#include "../function/randomGen.h"
#include "../function/graph.h"

class Asset: public Graph
{
private:
    std::string name, ticker;
    float price;
public:
    Asset(): Graph(-1), name("NULL"), ticker("NULL"), price(-1) {};
    Asset(std::string newName, std::string newTicker, float newPrice): Graph(newPrice), name(newName), ticker(newTicker), price(newPrice) {};
    float getPrice() const {return this->price;};
    std::string getName() const {return this->name;};
    std::string getTicker() const {return this->ticker;};
    void setPrice(float newPrice) {
        this->price = newPrice;
        this->updatGraphPrice(this->price);
    };
    virtual void updatePrice() {};
    virtual void updatePrice(double mean, double stdDev, float skewness) {};
    virtual ~Asset() {};
};

#endif