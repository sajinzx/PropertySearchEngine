#ifndef PROPERTY_H
#define PROPERTY_H

#include <string>
using namespace std;

class Property {
protected:
    string id;
    string ownerName;
    string propertyType;
    double latitude;
    double longitude;
    double price;
    double area;
    string address;
    bool isAvailable;
    string facing;
    string landmark;
    string ownershipType;

public:
    Property();
    Property(string id, const string &ownerName, const string &propertyType,
             double latitude, double longitude, double price, double area,
             const string &address, bool isAvailable, const string &facing,
             const string &landmark, const string &ownershipType);

    virtual ~Property() {}

    string getId() const;
    string getOwnerName() const;
    string getPropertyType() const;
    double getLatitude() const;
    double getLongitude() const;
    double getPrice() const;
    double getArea() const;
    string getAddress() const;
    bool getAvailability() const;
    string getFacing() const;
    string getLandmark() const;
    string getOwnershipType() const;

    void setOwnerName(const string &name);
    void setPropertyType(const string &type);
    void setLatitude(double lat);
    void setLongitude(double lon);
    void setPrice(double price);
    void setArea(double area);
    void setAddress(const string &addr);
    void setAvailability(bool status);
    void setFacing(const string &face);
    void setLandmark(const string &mark);
    void setOwnershipType(const string &type);

    virtual void display() const;
    double distanceTo(double lat, double lon) const;
};

#endif
