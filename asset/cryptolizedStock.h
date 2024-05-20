#ifndef CRYPTOLIZEDSTOCK_H
#define CRYPTOLIZEDSTOCK_H
#include "crypto.h"
#include "stock.h"
#include <sstream>
#include <string>
class CryptolizedStock : public Crypto
{
private:
    int shareOwned;
    Stock *peggedStock;
    randomGen rnd;
public:
    CryptolizedStock(Stock *stock) : Crypto(stock->getName(), "NULL", 0, rand() % 10000000 + 10000){
        peggedStock = stock;
        std::stringstream ss;
        ss << "X" << peggedStock->getTicker();
        this->setTicker(ss.str());
        this->shareOwned = stock->getCirculatingShares() / 100 + this->rnd.priceRandomGen(100000,1000,0.25);
        double newPirce = this->shareOwned / this->getCirculatingAmount() * peggedStock->getPrice();
        this->setPrice(newPirce);
    }
    void updatePrice() {
        double newPirce = this->shareOwned / this->getCirculatingAmount() * peggedStock->getPrice();
        this->setPrice(newPirce);
    }
    ~CryptolizedStock() {};
};



#endif