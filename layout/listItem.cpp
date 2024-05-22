#include "listItem.h"

ListItem::ListItem(Asset* newAsset, sf::Font* font) : asset(newAsset) {
  this->text.setFont(*font);
  this->text.setFillColor(sf::Color::Black);
  this->text.setCharacterSize(16);
  this->text.setPosition(sf::Vector2f(0.f, 0.f));
  std::stringstream ss;

  ss << std::left;
  ss << std::setw(6) << std::setfill(' ') << this->asset->getTicker();
  ss << "|";
  ss << std::setw(26) << this->asset->getName();
  ss << "|$";
  ss << std::setprecision(2) << std::fixed << this->asset->getPrice();

  this->text.setString(ss.str());
}

Asset& ListItem::getAsset(){return *this->asset;}

void ListItem::updateText() {
  std::stringstream ss;
  ss << std::left;
  ss << std::setw(6) << std::setfill(' ') << this->asset->getTicker();
  ss << "|";
  ss << std::setw(26) << this->asset->getName(); 
  ss << "|$";
  ss << std::setprecision(2) << std::fixed << this->asset->getPrice();
  this->text.setString(ss.str());
}
sf::Text* ListItem::getText() { return &this->text; }

ListItem::~ListItem() {}