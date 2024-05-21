#ifndef PLAYER_H
#define PLAYER_H
#include <string>
#include "portfolio.h"

class Player: public Portfolio
{
private:
    std::string name;
    int rank;
public:
    Player();
    Player(std::string, float);
    void setName(std::string);
    void setRank(int);
    std::string getName() const;
    float getRank() const;
    ~Player();
};

#endif
