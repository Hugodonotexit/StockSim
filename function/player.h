#ifndef PLAYER_H
#define PLAYER_H
#include <string>

class Player
{
private:
    std::string name;
    int rank;
    float balance, assetValue, margin;
public:
    Player();
    Player(std::string, float);
    void setName(std::string);
    void setRank(int);
    void setBalance(float);
    void setAssetValue(float);
    std::string getName() const;
    float getRank() const;
    float getBalance() const;
    float getAssetValue() const;
    float getMargin() const;
    void updateMargin();
    ~Player();
};

#endif
