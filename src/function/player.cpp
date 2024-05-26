#include "player.h"

Player::Player() : name("Hugo"), rank(0) {}
void Player::setName(std::string newName) {this->name = newName;}
void Player::setRank(int newRank) {this->rank = newRank;}
std::string Player::getName() const {return this->name;}
float Player::getRank() const {return this->rank;}

Player::~Player(){};