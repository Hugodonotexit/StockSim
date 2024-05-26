#include "list.h"

List::List(std::string newName, int newNum, Asset** asset, sf::Font *font): name(newName), num(newNum) {
    this->listItem = new ListItem *[num];
    for (int i = 0; i < num; i++)
    {
        this->listItem[i] = new ListItem(asset[i], font);
    }
}
List::~List() {
    for (int i = 0; i < num; i++)
    {
        delete this->listItem[i];
    }
    delete[] this->listItem;
}

ListItem *List::getListItem(int i){
    if (i > this->num)
    {
        return nullptr;
    }
    return this->listItem[i];
};

std::string List::getName() {return this->name;}

int List::getIndex() { return this->num;}
