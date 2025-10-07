#ifndef LAND_H
#define LAND_H

#include "Property.h"
#include <string>
using namespace std;

class Land : public Property {
private:
    string landType;
    bool hasCompoundWall;
    bool nearMainRoad;
    bool isDTCPApproved;
    bool hasElectricityAccess;
    bool hasWaterFacility;

public:
    Land();
    Land(string id, const string &ownerName, double latitude, double longitude,
         double price, double area, const string &address, bool isAvailable,
         const string &facing, const string &landmark, const string &ownershipType,
         const string &landType, bool hasCompoundWall, bool nearMainRoad,
         bool isDTCPApproved, bool hasElectricityAccess, bool hasWaterFacility);

    string getLandType() const;
    bool getHasCompoundWall() const;
    bool getNearMainRoad() const;
    bool getIsDTCPApproved() const;
    bool getHasElectricityAccess() const;
    bool getHasWaterFacility() const;

    void setLandType(const string &type);
    void setHasCompoundWall(bool wall);
    void setNearMainRoad(bool nearRoad);
    void setIsDTCPApproved(bool approved);
    void setHasElectricityAccess(bool access);
    void setHasWaterFacility(bool facility);

    void display() const override;
};

#endif
