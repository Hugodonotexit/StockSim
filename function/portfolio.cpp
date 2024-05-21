#include "portfolio.h"

bool Portfolio::isInPortfolio(Asset* asset) {
  bool isInPortfolio = false;
  for (int i = 0; i < this->id; i++) {
    if (this->portfolio[i].asset == asset) {
      isInPortfolio = true;
      this->locateID = i;
      break;
    } else {
      isInPortfolio = false;
    }
  }
  return isInPortfolio;
}

Portfolio::Portfolio() : balance(100000), assetValue(0) {}
void Portfolio::buy(Asset* asset, int amount) {
  double cost = asset->getPrice() * amount;
  if (cost > balance) {
    return;
  }
  if (!this->isInPortfolio(asset)) {
    this->portfolio.push_back({asset, amount, asset->getPrice()});
    this->id++;
  } else {
        this->portfolio[this->locateID].price = (double)(this->portfolio[this->locateID].price * this->portfolio[this->locateID].amount + asset->getPrice() * amount) / (double)(this->portfolio[this->locateID].amount + amount);
        this->portfolio[this->locateID].amount += amount;   
    }
  this->balance -= cost;
}
void Portfolio::sell(Asset* asset, int amount) {
  if (this->isInPortfolio(asset)) {
        if (amount > this->portfolio[this->locateID].amount) {
            amount = this->portfolio[this->locateID].amount;
        }
        this->balance += asset->getPrice() * amount;
        if (this->portfolio[this->locateID].amount == 0) {
            // If no more of this asset, remove from portfolio
            this->portfolio.erase(this->portfolio.begin() + this->locateID);
            this->id--;  // Adjust the id count
        }
  } 

  return;
}
Portfolio::AssetRecord const Portfolio::getPortfolio(int id) {
  return this->portfolio[id];
}
void Portfolio::setBalance(float newBalance) { this->balance = newBalance; };
void Portfolio::setAssetValue(float newAssetValue) {
  this->assetValue = newAssetValue;
};
float Portfolio::getBalance() const { return this->balance; };
float Portfolio::getAssetValue() const { return this->assetValue; };

Portfolio::~Portfolio() {
  for (int i = 0; i < id; i++) {
    delete this->portfolio[i].asset;
  }
}