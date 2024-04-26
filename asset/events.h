#ifndef EVENTS_H
#define EVENTS_H
#include <string>

using namespace std;

class Events
{
private:
    string nameID, discerption;
    float eventImpactMean, eventImpactStdDev; 
public:
    Events(): nameID("NULL"), discerption("NULL"), eventImpactMean(0), eventImpactStdDev(0) {};
    Events(string newNameID, string newDiscerption, float newEventImpactMean, float newEventImpactStdDev): nameID(newNameID), discerption(newDiscerption), eventImpactMean(newEventImpactMean), eventImpactStdDev(newEventImpactStdDev) {};
    string getNameID() const {return this->nameID;};
    string getDiscerption() const {return this->discerption;};
    float getEventImpactMean() const {return this->eventImpactMean;};
    float getEventImpactStdDev() const {return this->eventImpactStdDev;};
    ~Events() {};
};



#endif