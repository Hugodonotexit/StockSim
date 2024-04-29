#ifndef GAMETIME_H
#define GAMETIME_H
#include <SFML/System.hpp>
#include <string>

using namespace sf;

class Gametime
{
private:
    Clock clock;
    Time elapsed;
    int timeScale; //0, 120, 720, 1440
    int minute, hour, day, month, year;
    int dayOfMonth[12] = {31,28,31,30,31,30,31,31,30,31,30};

    void checkLeapYear();
public:
    Gametime();
    Gametime(int, int, int, int, int, int);
    void setTimeScale(int);
    void updateTime();
    ~Gametime();
    
    int getMinute() const;
    int getHour() const;
    int getDay() const;
    int getMonth() const;
    int getYear() const;
};


#endif