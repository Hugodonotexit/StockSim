#include "gametime.h"

Gametime::Gametime()
    : timeScaleIndex(0), minute(0), hour(0), day(1), month(1), year(1939) {
  this->elapsed = clock.restart();
};
Gametime::Gametime(int newtimeScaleIndex, int newMinute, int newHour, int newDay,
                   int newMonth, int newYear)
    : timeScaleIndex(newtimeScaleIndex),
      minute(newMinute),
      hour(newHour),
      day(newDay),
      month(newMonth),
      year(newYear) {
  this->elapsed = clock.restart();
};
void Gametime::setTimeScaleIndex(int newTimeScaleIndex) {
  this->timeScaleIndex = newTimeScaleIndex;
};
void Gametime::updateTime() {

  if (this->timeScale[this->timeScaleIndex] == 0) 
  {
    this->elapsed = clock.restart();
  }
  else
  {
    this->elapsed += clock.restart();
    this->minute += elapsed.asSeconds() * timeScale[this->timeScaleIndex];
    while (this->minute >= 60) {
      this->minute -= 60;
      this->hour++;
      if (this->hour >= 24) {
        this->hour = 0;
        this->day++;
        if (this->day > this->dayOfMonth[month - 1]) {
          this->day = 1;
          this->month++;
          if (this->month > 12) {
            this->month = 1;
            this->year++;
            checkLeapYear();
          }
        }
      }
    }
  }
};

int Gametime::getMinute() const {return this->minute;};
int Gametime::getHour() const {return this->hour;};
int Gametime::getDay() const {return this->day;};
int Gametime::getMonth() const {return this->month;};
int Gametime::getYear() const {return this->year;};

void Gametime::checkLeapYear() {
  if (this->year % 400 == 0 || (this->year % 4 == 0 && this->year % 100 != 0)) {
    dayOfMonth[1] = 29;
    return;
  }
  dayOfMonth[1] = 28;
  return;
};
Gametime::~Gametime(){};