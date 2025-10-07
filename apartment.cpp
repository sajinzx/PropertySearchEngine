#include <iostream>

#include "Apartment.h"
using namespace std;

Apartment::Apartment()
    : Property(),
      floorNumber(0),
      totalFloors(0),
      numberOfBedrooms(0),
      hasLift(false),
      hasParking(false),
      maintenanceCharge(0.0),
      furnishingStatus("Unfurnished") {}

Apartment::Apartment(string id, const string &ownerName, double latitude,
                     double longitude, double price, double area,
                     const string &address, bool isAvailable,
                     const string &facing, const string &landmark,
                     const string &ownershipType, int floorNumber,
                     int totalFloors, int numberOfBedrooms, bool hasLift,
                     bool hasParking, double maintenanceCharge,
                     const string &furnishingStatus)
    : Property(id, ownerName, "Apartment", latitude, longitude, price, area,
               address, isAvailable, facing, landmark, ownershipType),
      floorNumber(floorNumber),
      totalFloors(totalFloors),
      numberOfBedrooms(numberOfBedrooms),
      hasLift(hasLift),
      hasParking(hasParking),
      maintenanceCharge(maintenanceCharge),
      furnishingStatus(furnishingStatus) {}

int Apartment::getFloorNumber() const 
{ 
    return floorNumber; 
}
int Apartment::getTotalFloors() const 
{ 
    return totalFloors; 
}
int Apartment::getNumberOfBedrooms() const 
{ 
    return numberOfBedrooms; 
}
bool Apartment::getHasLift() const 
{ 
    return hasLift; 
}
bool Apartment::getHasParking() const 
{ 
    return hasParking; 
}
double Apartment::getMaintenanceCharge() const 
{ 
    return maintenanceCharge; 
}
string Apartment::getFurnishingStatus() const 
{ 
    return furnishingStatus; 
}

void Apartment::setFloorNumber(int floor) 
{ 
    floorNumber = floor; 
}
void Apartment::setTotalFloors(int floors) 
{ 
    totalFloors = floors; 
}
void Apartment::setNumberOfBedrooms(int rooms) 
{ 
    numberOfBedrooms = rooms; 
}
void Apartment::setHasLift(bool lift) 
{
    hasLift = lift; 
}
void Apartment::setHasParking(bool parking)
{ 
    hasParking = parking;
}
void Apartment::setMaintenanceCharge(double charge) 
{
  maintenanceCharge = charge;
}
void Apartment::setFurnishingStatus(const string &status) 
{
  furnishingStatus = status;
}

void Apartment::display() const {
  Property::display();
  cout << "Floor: " << floorNumber << "/" << totalFloors
       << "\nBedrooms: " << numberOfBedrooms
       << "\nLift: " << (hasLift ? "Yes" : "No")
       << "\nParking: " << (hasParking ? "Yes" : "No")
       << "\nMaintenance Charge: " << maintenanceCharge
       << "\nFurnishing: " << furnishingStatus << endl;
}
