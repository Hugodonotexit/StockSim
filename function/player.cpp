#include "player.h"

Player::Player() : name("NULL"), rank(0), balance(100000), assetValue(0) {
  this->margin = this->balance * 2 + this->assetValue * 1.5;
};
Player::Player(std::string newName, float newBalance)
    : name(newName), rank(0), balance(newBalance), assetValue(0) {
  this->margin = this->balance * 2 + this->assetValue * 1.5;
};
void Player::setName(std::string newName) {this->name = newName;};
void Player::setRank(int newRank) {this->rank = newRank;};
void Player::setBalance(float newBalance) {this->balance = newBalance;};
void Player::setAssetValue(float newAssetValue) {this->assetValue = newAssetValue;};
std::string Player::getName() const {return this->name;};
float Player::getRank() const {return this->rank;};
float Player::getBalance() const {return this->balance;};
float Player::getAssetValue() const {return this->assetValue;};
float Player::getMargin() const {return this->margin;};
void Player::updateMargin() {
    this->margin = this->balance * 2 + this->assetValue * 1.5;
};
Player::~Player(){};