#include <cmath>
#include <iostream>
#include "Property.h"
using namespace std;

// const double M_PI = 3.14159265358979323846;


Property::Property()
    : id(0),
      ownerName(""),
      propertyType(""),
      latitude(0),
      longitude(0),
      price(0),
      area(0),
      address(""),
      isAvailable(true),
      facing(""),
      landmark(""),
      ownershipType("") {}

Property::Property(string id, const string &ownerName, const string &propertyType,
                   double latitude, double longitude, double price, double area,
                   const string &address, bool isAvailable,
                   const string &facing, const string &landmark,
                   const string &ownershipType)
    : id(id),
      ownerName(ownerName),
      propertyType(propertyType),
      latitude(latitude),
      longitude(longitude),
      price(price),
      area(area),
      address(address),
      isAvailable(isAvailable),
      facing(facing),
      landmark(landmark),
      ownershipType(ownershipType) {}

string Property::getId() const 
{ 
    return id; 
}
string Property::getOwnerName() const 
{ 
    return ownerName; 
}
string Property::getPropertyType() const
{
    return propertyType; 
}
double Property::getLatitude() const 
{ 
    return latitude; 
}
double Property::getLongitude() const 
{ 
    return longitude; 
}
double Property::getPrice() const 
{
    return price; 
}
double Property::getArea() const {
    return area; 
}
string Property::getAddress() const 
{ 
    return address; 
}
bool Property::getAvailability() const 
{ 
    return isAvailable; 
}
string Property::getFacing() const 
{ 
    return facing; 
}
string Property::getLandmark() const 
{ 
    return landmark; 
}
string Property::getOwnershipType() const 
{ 
    return ownershipType; 
}

void Property::setOwnerName(const string &name) 
{ 
    ownerName = name; 
}
void Property::setPropertyType(const string &type) 
{
    propertyType = type; 
}
void Property::setLatitude(double lat) 
{ 
    latitude = lat; 
}
void Property::setLongitude(double lon) 
{ 
    longitude = lon;
}
void Property::setPrice(double p) 
{ 
    price = p; 
}
void Property::setArea(double a) 
{ 
    area = a; 
}
void Property::setAddress(const string &addr) 
{ 
    address = addr; 
}
void Property::setAvailability(bool status) 
{ 
    isAvailable = status; 
}
void Property::setFacing(const string &face) 
{ 
    facing = face; 
}
void Property::setLandmark(const string &mark) 
{ 
    landmark = mark; 
}
void Property::setOwnershipType(const string &type) 
{ 
    ownershipType = type; 
}

void Property::display() const {
  cout << "Property ID: " << id << "\nOwner: " << ownerName
       << "\nType: " << propertyType << "\nLocation: " << latitude << ", "
       << longitude << "\nPrice: " << price << "\nArea: " << area
       << "\nAddress: " << address
       << "\nAvailability: " << (isAvailable ? "Yes" : "No")
       << "\nFacing: " << facing << "\nLandmark: " << landmark
       << "\nOwnership Type: " << ownershipType << endl;
}

double Property::distanceTo(double lat, double lon) const {
  const double R = 6371.0;  // Earth radius in km
  double lat1 = latitude * M_PI / 180.0;
  double lon1 = longitude * M_PI / 180.0;
  double lat2 = lat * M_PI / 180.0;
  double lon2 = lon * M_PI / 180.0;
  double dlat = lat2 - lat1;
  double dlon = lon2 - lon1;

  double a = sin(dlat / 2) * sin(dlat / 2) +
             cos(lat1) * cos(lat2) * sin(dlon / 2) * sin(dlon / 2);
  double c = 2 * atan2(sqrt(a), sqrt(1 - a));
  return R * c;
}
