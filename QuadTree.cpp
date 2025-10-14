#include "QuadTree.h"

QuadTree::QuadTree(Boundary boundary)
    : boundary(boundary), divided(false),
      northWest(nullptr), northEast(nullptr), southWest(nullptr), southEast(nullptr) {}

QuadTree::~QuadTree() {
    delete northWest;
    delete northEast;
    delete southWest;
    delete southEast;
}

void QuadTree::subdivide() {
    double x = boundary.x;
    double y = boundary.y;
    double hw = boundary.halfWidth / 2;
    double hh = boundary.halfHeight / 2;

    northWest = new QuadTree(Boundary(x - hw, y + hh, hw, hh));
    northEast = new QuadTree(Boundary(x + hw, y + hh, hw, hh));
    southWest = new QuadTree(Boundary(x - hw, y - hh, hw, hh));
    southEast = new QuadTree(Boundary(x + hw, y - hh, hw, hh));
    divided = true;
}

bool QuadTree::insert(PropertyPoint p) {
    if (!boundary.contains(p))
        return false;

    if (points.size() < CAPACITY) {
        points.push_back(p);
        return true;
    } else {
        if (!divided)
            subdivide();

        if (northWest->insert(p)) return true;
        if (northEast->insert(p)) return true;
        if (southWest->insert(p)) return true;
        if (southEast->insert(p)) return true;
    }
    return false;
}

void QuadTree::query(Boundary range, vector<PropertyPoint>& found) {
    if (!boundary.intersects(range))
        return;

    for (auto& p : points) {
        if (range.contains(p))
            found.push_back(p);
    }

    if (divided) {
        northWest->query(range, found);
        northEast->query(range, found);
        southWest->query(range, found);
        southEast->query(range, found);
    }
}
