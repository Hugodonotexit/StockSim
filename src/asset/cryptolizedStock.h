#ifndef CRYPTOLIZEDSTOCK_H
#define CRYPTOLIZEDSTOCK_H
#include "crypto.h"
#include "stock.h"
#include <sstream>
#include <string>
#include <iostream>
class CryptolizedStock : public Crypto
{
private:
    int shareOwned;
    Stock *peggedStock;
    randomGen rnd;
public:
    CryptolizedStock(Stock &stock) : Crypto(stock.getName(), "NULL", 10, rand() % 1000000 + 10000000){
        peggedStock = &stock;
        std::stringstream ss;
        ss << "X" << peggedStock->getTicker();
        this->setTicker(ss.str());
        this->shareOwned = this->rnd.RandGen(100000,50000000);
        double newPirce = ((float)this->shareOwned / (float)this->getCirculatingAmount()) * peggedStock->getPrice();
        this->setPrice(newPirce);
    }
    void updatePrice() {
        double newPirce = ((float)this->shareOwned / (float)this->getCirculatingAmount()) * peggedStock->getPrice();
        this->setPrice(newPirce);
    }
    ~CryptolizedStock() {};
};



#endif