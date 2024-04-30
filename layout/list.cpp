#include "list.h"

List::List(){}

void List::addCrypto(const Crypto& crypto) {
    cryptos.insert(crypto);
}

void List::addStock(const Stock& stock) {
    stocks.insert(stock);
}

void List::switchView(){
    if(currentView == ViewType::Stocks) {
        currentView = ViewType::Cryptos;
    } else {
        currentView = ViewType::Stocks;
    }
}