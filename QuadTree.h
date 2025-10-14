#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include <string>
#include <iostream>
using namespace std;

struct PropertyPoint {
    double latitude;
    double longitude;
    string propertyID;

    PropertyPoint(double lat = 0, double lon = 0, string id = "")
        : latitude(lat), longitude(lon), propertyID(id) {}
};

struct Boundary {
    double x; // center x (longitude)
    double y; // center y (latitude)
    double halfWidth;
    double halfHeight;

    Boundary(double cx, double cy, double hw, double hh)
        : x(cx), y(cy), halfWidth(hw), halfHeight(hh) {}

    bool contains(const PropertyPoint& p) const {
        return (p.longitude >= x - halfWidth && p.longitude <= x + halfWidth &&
                p.latitude >= y - halfHeight && p.latitude <= y + halfHeight);
    }

    bool intersects(const Boundary& range) const {
        return !(range.x - range.halfWidth > x + halfWidth ||
                 range.x + range.halfWidth < x - halfWidth ||
                 range.y - range.halfHeight > y + halfHeight ||
                 range.y + range.halfHeight < y - halfHeight);
    }
};

class QuadTree {
private:
    static const int CAPACITY = 4;
    Boundary boundary;
    vector<PropertyPoint> points;
    bool divided;

    QuadTree *northWest, *northEast, *southWest, *southEast;

public:
    QuadTree(Boundary boundary);
    ~QuadTree();

    bool insert(PropertyPoint p);
    void subdivide();
    void query(Boundary range, vector<PropertyPoint>& found);
};

#endif
