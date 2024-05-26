#ifndef ASSET_H
#define ASSET_H
#include <string>
#include "../function/randomGen.h"
#include "../function/graph.h"



class Asset
{
private:
    std::string name, ticker;
    float price;
    Graph *graph = nullptr;
public:
    Asset(): name("NULL"), ticker("NULL"), price(-1) { this->graph = new Graph(-1);};
    Asset(std::string newName, std::string newTicker, float newPrice): name(newName), ticker(newTicker), price(newPrice) { this->graph = new Graph(newPrice);};
    Graph *setGraph() {return this->graph;};
    float getPrice() const {return this->price;};
    std::string getName() const {return this->name;};
    std::string getTicker() const {return this->ticker;};
    void setPrice(float newPrice) {
        if (newPrice < 0) {
            newPrice = 0.01;
        }
        this->price = newPrice;
        this->setGraph()->updatGraphPrice(this->price);
    };
    void setTicker(std::string newTicker) {
        this->ticker = newTicker;
    };
    virtual void updatePrice() {};
    virtual void updatePrice(double mean, double stdDev, float skewness) {};
    virtual ~Asset() {delete this->graph;};
};

#endif