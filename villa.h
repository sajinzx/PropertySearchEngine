#ifndef VILLA_H
#define VILLA_H

#include "Property.h"
#include <string>
using namespace std;

class Villa : public Property {
private:
    int numberOfBedrooms;
    bool hasGarden;
    bool hasPrivatePool;
    double plotArea;
    bool hasGarage;
    string furnishingStatus;

public:
    Villa();
    Villa(string id, const string &ownerName, double latitude, double longitude,
          double price, double area, const string &address, bool isAvailable,
          const string &facing, const string &landmark, const string &ownershipType,
          int numberOfBedrooms, bool hasGarden, bool hasPrivatePool,
          double plotArea, bool hasGarage, const string &furnishingStatus);

    int getNumberOfBedrooms() const;
    bool getHasGarden() const;
    bool getHasPrivatePool() const;
    double getPlotArea() const;
    bool getHasGarage() const;
    string getFurnishingStatus() const;

    void setNumberOfBedrooms(int rooms);
    void setHasGarden(bool garden);
    void setHasPrivatePool(bool pool);
    void setPlotArea(double area);
    void setHasGarage(bool garage);
    void setFurnishingStatus(const string &status);

    void display() const override;
};

#endif
