#include "Villa.h"
#include <iostream>
using namespace std;

Villa::Villa()
  : Property()
  , numberOfBedrooms(0)
  , hasGarden(false)
  , hasPrivatePool(false)
  , plotArea(0.0)
  , hasGarage(false)
  , furnishingStatus("Unfurnished")
{}

Villa::Villa(string id,
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
             int numberOfBedrooms,
             bool hasGarden,
             bool hasPrivatePool,
             double plotArea,
             bool hasGarage,
             const string& furnishingStatus)
  : Property(id,
             ownerName,
             "Villa",
             latitude,
             longitude,
             price,
             area,
             address,
             isAvailable,
             facing,
             landmark,
             ownershipType)
  , numberOfBedrooms(numberOfBedrooms)
  , hasGarden(hasGarden)
  , hasPrivatePool(hasPrivatePool)
  , plotArea(plotArea)
  , hasGarage(hasGarage)
  , furnishingStatus(furnishingStatus)
{}

int Villa::getNumberOfBedrooms() const
{
  return numberOfBedrooms;
}
bool Villa::getHasGarden() const
{
  return hasGarden;
}
bool Villa::getHasPrivatePool() const
{
  return hasPrivatePool;
}
double Villa::getPlotArea() const
{
  return plotArea;
}
bool Villa::getHasGarage() const
{
  return hasGarage;
}
string Villa::getFurnishingStatus() const
{
  return furnishingStatus;
}

void Villa::setNumberOfBedrooms(int rooms)
{
  numberOfBedrooms = rooms;
}
void Villa::setHasGarden(bool garden)
{
  hasGarden = garden;
}
void Villa::setHasPrivatePool(bool pool)
{
  hasPrivatePool = pool;
}
void Villa::setPlotArea(double area)
{
  plotArea = area;
}
void Villa::setHasGarage(bool garage)
{
  hasGarage = garage;
}
void Villa::setFurnishingStatus(const string& status)
{
  furnishingStatus = status;
}

void Villa::display() const
{
  Property::display();
  cout << "Bedrooms: " << numberOfBedrooms
       << "\nGarden: " << (hasGarden ? "Yes" : "No")
       << "\nPrivate Pool: " << (hasPrivatePool ? "Yes" : "No")
       << "\nPlot Area: " << plotArea
       << "\nGarage: " << (hasGarage ? "Yes" : "No")
       << "\nFurnishing: " << furnishingStatus << endl;
}
