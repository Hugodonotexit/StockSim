#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include "../asset/asset.h"
#include <vector>


class Portfolio
{
private:
    int id = 0;
    int locateID = 0;
    struct AssetRecord {
    Asset *asset;
    int amount;
    float price;
    };
    std::vector<AssetRecord> portfolio;
    bool isInPortfolio(Asset*);
    float balance, assetValue, margin;
public:
    Portfolio();
    void buy(Asset*, int, float);
    void sell(Asset*, int, float);
    Portfolio::AssetRecord const getPortfolio(int);
    void setBalance(float);
    void setAssetValue(float);
    float getBalance() const;
    float getAssetValue() const;
    float getMargin() const;
    void updateMargin();
    ~Portfolio();
};


#endif