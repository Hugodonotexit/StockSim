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
void Portfolio::buy(Asset* asset, int amount, float price) {
    if (!this->isInPortfolio(asset)) {
    this->portfolio.push_back({asset, amount, price});
    this->id++;
  }
}
void Portfolio::sell(Asset* asset, int amount, float price) {

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