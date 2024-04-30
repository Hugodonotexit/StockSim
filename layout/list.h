#ifndef LIST_H
#define LIST_H

#include "Crypto.h"
#include "Stock.h"
#include <set>

class List {
public:
    enum class ViewType {Stocks, Cryptos};
private:
    std::set<Crypto> cryptos;
    std::set<Stock> stocks;
    ViewType currentView;
public:
    List() : currentView(ViewType::Stocks) {} // list starts off in stocks
    void addCrypto(const Crypto& crypto);
    void addStock(const Stock& stock);
    void switchView(); // if we have forex, will need to update
    
    const std::set<Crypto>& getCryptos() const { return cryptos; }
    const std::set<Stock>& getStocks() const { return stocks; }
    ViewType getCurrentView() const {return currentView; }
};

#endif 
