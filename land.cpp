#include <iostream>
#include "Land.h"
using namespace std;

Land::Land()
    : Property(),
      landType("Residential"),
      hasCompoundWall(false),
      nearMainRoad(false),
      isDTCPApproved(false),
      hasElectricityAccess(false),
      hasWaterFacility(false) {}

Land::Land(string id,
           const string& ownerName,
           double latitude,
           double longitude,
           double price,
           double area,
           const string& address,
           bool isAvailable,
           const string& facing,
           const string& landmark,
           const string& ownershipType,
           const string& landType,
           bool hasCompoundWall,
           bool nearMainRoad,
           bool isDTCPApproved,
           bool hasElectricityAccess,
           bool hasWaterFacility)
    : Property(id,
               ownerName,
               "Land",
               latitude,
               longitude,
               price,
               area,
               address,
               isAvailable,
               facing,
               landmark,
               ownershipType),
      landType(landType),
      hasCompoundWall(hasCompoundWall),
      nearMainRoad(nearMainRoad),
      isDTCPApproved(isDTCPApproved),
      hasElectricityAccess(hasElectricityAccess),
      hasWaterFacility(hasWaterFacility) {}

string Land::getLandType() const 
{
  return landType;
}
bool Land::getHasCompoundWall() const 
{
  return hasCompoundWall;
}
bool Land::getNearMainRoad() const 
{
  return nearMainRoad;
}
bool Land::getIsDTCPApproved() const 
{
  return isDTCPApproved;
}
bool Land::getHasElectricityAccess() const 
{
  return hasElectricityAccess;
}
bool Land::getHasWaterFacility() const 
{
  return hasWaterFacility;
}

void Land::setLandType(const string& type) 
{
  landType = type;
}
void Land::setHasCompoundWall(bool wall) 
{
  hasCompoundWall = wall;
}
void Land::setNearMainRoad(bool nearRoad) 
{
  nearMainRoad = nearRoad;
}
void Land::setIsDTCPApproved(bool approved) 
{
  isDTCPApproved = approved;
}
void Land::setHasElectricityAccess(bool access) 
{
  hasElectricityAccess = access;
}
void Land::setHasWaterFacility(bool facility) 
{
  hasWaterFacility = facility;
}

void Land::display() const 
{
  Property::display();
  cout << "Land Type: " << landType
       << "\nCompound Wall: " << (hasCompoundWall ? "Yes" : "No")
       << "\nNear Main Road: " << (nearMainRoad ? "Yes" : "No")
       << "\nDTCP Approved: " << (isDTCPApproved ? "Yes" : "No")
       << "\nElectricity Access: " << (hasElectricityAccess ? "Yes" : "No")
       << "\nWater Facility: " << (hasWaterFacility ? "Yes" : "No") << endl;
}
