#ifndef APARTMENT_H
#define APARTMENT_H

#include "Property.h"

class Apartment : public Property {
private:
    int floorNumber;
    int totalFloors;
    int numberOfBedrooms;
    bool hasLift;
    bool hasParking;
    double maintenanceCharge;
    string furnishingStatus;

public:
    Apartment();
    Apartment(string id, const string &ownerName, double latitude, double longitude,
              double price, double area, const string &address, bool isAvailable,
              const string &facing, const string &landmark, const string &ownershipType,
              int floorNumber, int totalFloors, int numberOfBedrooms,
              bool hasLift, bool hasParking, double maintenanceCharge,
              const string &furnishingStatus);

    int getFloorNumber() const;
    int getTotalFloors() const;
    int getNumberOfBedrooms() const;
    bool getHasLift() const;
    bool getHasParking() const;
    double getMaintenanceCharge() const;
    string getFurnishingStatus() const;

    void setFloorNumber(int floor);
    void setTotalFloors(int floors);
    void setNumberOfBedrooms(int rooms);
    void setHasLift(bool lift);
    void setHasParking(bool parking);
    void setMaintenanceCharge(double charge);
    void setFurnishingStatus(const string &status);

    void display() const override;
};

#endif
