#ifndef LIST_H
#define LIST_H
#include "listItem.h"
#include "asset/cryptolizedStock.h"
#include "asset/crypto.h"
#include "asset/stock.h"
#include "asset/asset.h"
#include <string>
#define TAB_NUM 3

class List
{
private:
    std::string name;
    int num = 0;
    ListItem **listItem = nullptr;
public:
    List(std::string, int, Asset**, sf::Font*);
    std::string getName();
    int getIndex();
    ListItem *getListItem(int);
    ~List();
};


#endif 
