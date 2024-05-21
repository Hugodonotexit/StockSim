#include "listItem.h"

ListItem::ListItem(Asset* newAsset, sf::Font *font): asset(newAsset) { 
    this->text.setFont(*font);
    this->text.setFillColor(sf::Color::Black);
    this->text.setCharacterSize(14);
    this->text.setPosition(sf::Vector2f(-1.f, -1.f));
    std::stringstream ss;
    ss << this->asset->getTicker() << std::setw(6) << std::setfill(' ') << "|" << this->asset->getName() << std::setw(24) << std::setfill(' ')  << " | $" << this->asset->getPrice() << std::setw(6) << std::setfill(' ');
    this->text.setString(ss.str());

    }

void ListItem::updateText(){
    std::stringstream ss;
    ss << this->asset->getTicker() << std::setw(6) << std::setfill(' ') << "|" << this->asset->getName() << std::setw(24) << std::setfill(' ')  << " | $" << this->asset->getPrice() << std::setw(6) << std::setfill(' ');
    this->text.setString(ss.str());
    }
sf::Text ListItem::getText() {return this->text;}

ListItem::~ListItem() {
    delete this->asset;
}