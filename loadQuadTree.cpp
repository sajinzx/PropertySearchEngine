#include "loadQuadTree.h"
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

void loadQuadTreeFromFile(const string& filename, QuadTree& qt)
{
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error opening file " << filename << endl;
        return;
    }

    string line, type, propID, owner, latStr, lonStr;
    double latitude, longitude;

    while (getline(file, line)) {
        if (line.substr(0, 5) == "Type:") {
            type = line.substr(6);
        } else if (line.substr(0, 12) == "Property ID:") {
            propID = line.substr(13);
        } else if (line.substr(0, 9) == "Latitude:") {
            latStr = line.substr(10);
            latitude = stod(latStr);
        } else if (line.substr(0, 10) == "Longitude:") {
            lonStr = line.substr(11);
            longitude = stod(lonStr);

            // insert the property point after reading lat/lon
            PropertyPoint p(latitude, longitude, propID);
            qt.insert(p);
        }
    }
    file.close();
}
