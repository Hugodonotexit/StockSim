#ifndef LISTITEM_H
#define LISTITEM_H
#include "../asset/cryptolizedStock.h"
#include "../asset/crypto.h"
#include "../asset/stock.h"
#include "../asset/asset.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <sstream>
#include <string>
#include <iomanip> 
class ListItem
{
private:
    sf::Text text;
    Asset *asset = nullptr;
public:
    ListItem(Asset*, sf::Font*);
    void updateText();
    sf::Text* getText();
    ~ListItem();
};



#endif