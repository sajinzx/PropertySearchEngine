#include <fstream>
#include <iostream>
#include <limits>
#include "Apartment.h"
#include "Land.h"
#include "PropertyIDGenerator.h"
#include "Villa.h"
#include "PropertySearchTrie.h"
#include "TrieLoader.h"
#include "QuadTree.h"
#include "loadQuadTree.h"
#include <cmath>
using namespace std;

void saveToFile(const string& type, const string& details) {
    ofstream file("properties.txt", ios::app);
    file << "Type: " << type << endl;
    file << details << endl;
    file << "----------------------------------------" << endl;
    file.close();
}

double distanceInKm(double lat1, double lon1, double lat2, double lon2) {
    const double R = 6371.0; // Earth's radius in km
    double dLat = (lat2 - lat1) * M_PI / 180.0;
    double dLon = (lon2 - lon1) * M_PI / 180.0;
    double a = sin(dLat/2) * sin(dLat/2) +
               cos(lat1 * M_PI / 180.0) * cos(lat2 * M_PI / 180.0) *
               sin(dLon/2) * sin(dLon/2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));
    return R * c;
}

void searchByLocation(QuadTree &qt, const string &prefix)
{
    double lat, lon, range;
    cout << "Enter Latitude: ";
    cin >> lat;
    cout << "Enter Longitude: ";
    cin >> lon;
    cout << "Enter Search Radius (in degrees, e.g. 5): ";
    cin >> range;

    Boundary searchArea(lon, lat, range, range);
    vector<PropertyPoint> found;
    qt.query(searchArea, found);

    bool anyFound = false;
    cout << "\nProperties found near given location:\n";
    for (const auto &p : found)
    {
        if (p.propertyID.rfind(prefix, 0) == 0)
        {
            double dist = distanceInKm(lat, lon, p.latitude, p.longitude);
            cout << "- Property ID: " << p.propertyID
                 << " | (" << p.latitude << ", " << p.longitude << ")"
                 << " | Distance: " << dist << " km\n";
            anyFound = true;
        }
    }
    if (!anyFound)
        cout << "No " << prefix.substr(0, 3) << " properties found in this area.\n";
}

void Listing() {
    int choice;
    cout << "You chose Listing\n";
    cout << "Select the type of property you want to list:\n";
    cout << "1. Apartment\n";
    cout << "2. Villa\n";
    cout << "3. Land\n";
    cout << "4. Exit\n";
    cin >> choice;

    switch (choice) {
        case 1: {
            string ownerName, address, facing, landmark, ownershipType, furnishingStatus;
            int floorNumber = 0, totalFloors = 0, bedrooms = 0;
            double latitude = 0.0, longitude = 0.0, price = 0.0, area = 0.0, maintenanceCharge = 0.0;
            int tmpInt;
            bool isAvailable = false, hasLift = false, hasParking = false;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            while (true) {
                cout << "Enter owner name: ";
                getline(cin, ownerName);
                if (!ownerName.empty()) break;
                cout << "Owner name cannot be empty. Please re-enter.\n";
            }

            while (true) {
                cout << "Enter latitude (-90 to 90): ";
                if (cin >> latitude) {
                    if (latitude >= -90.0 && latitude <= 90.0) {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    } else {
                        cout << "Latitude out of range. Try again.\n";
                    }
                } else {
                    cout << "Invalid input. Enter a numeric latitude.\n";
                    cin.clear();
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            while (true) {
                cout << "Enter longitude (-180 to 180): ";
                if (cin >> longitude) {
                    if (longitude >= -180.0 && longitude <= 180.0) {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    } else {
                        cout << "Longitude out of range. Try again.\n";
                    }
                } else {
                    cout << "Invalid input. Enter a numeric longitude.\n";
                    cin.clear();
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            while (true) {
                cout << "Enter price: ";
                if (cin >> price) {
                    if (price >= 0.0) {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    } else {
                        cout << "Price must be non-negative. Try again.\n";
                    }
                } else {
                    cout << "Invalid input. Enter a numeric price.\n";
                    cin.clear();
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            while (true) {
                cout << "Enter area: ";
                if (cin >> area) {
                    if (area > 0.0) {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    } else {
                        cout << "Area must be positive. Try again.\n";
                    }
                } else {
                    cout << "Invalid input. Enter a numeric area.\n";
                    cin.clear();
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            while (true) {
                cout << "Enter address: ";
                getline(cin, address);
                if (!address.empty()) break;
                cout << "Address cannot be empty. Please re-enter.\n";
            }

            while (true) {
                cout << "Is available (1 for yes / 0 for no): ";
                if (cin >> tmpInt) {
                    if (tmpInt == 0 || tmpInt == 1) {
                        isAvailable = (tmpInt == 1);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    } else {
                        cout << "Enter 1 or 0.\n";
                    }
                } else {
                    cout << "Invalid input. Enter 1 or 0.\n";
                    cin.clear();
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            while (true) {
                cout << "Enter facing: ";
                getline(cin, facing);
                if (!facing.empty()) break;
                cout << "Facing cannot be empty. Please re-enter.\n";
            }

            while (true) {
                cout << "Enter landmark: ";
                getline(cin, landmark);
                if (!landmark.empty()) break;
                cout << "Landmark cannot be empty. Please re-enter.\n";
            }

            while (true) {
                cout << "Enter ownership type: ";
                getline(cin, ownershipType);
                if (!ownershipType.empty()) break;
                cout << "Ownership type cannot be empty. Please re-enter.\n";
            }

            while (true) {
                cout << "Enter floor number (0 or positive integer): ";
                if (cin >> floorNumber) {
                    if (floorNumber >= 0) {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    } else {
                        cout << "Floor number must be >= 0. Try again.\n";
                    }
                } else {
                    cout << "Invalid input. Enter an integer.\n";
                    cin.clear();
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            while (true) {
                cout << "Enter total floors (must be >= floor number): ";
                if (cin >> totalFloors) {
                    if (totalFloors >= floorNumber) {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    } else {
                        cout << "Total floors must be >= floor number. Try again.\n";
                    }
                } else {
                    cout << "Invalid input. Enter an integer.\n";
                    cin.clear();
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            while (true) {
                cout << "Enter number of bedrooms: ";
                if (cin >> bedrooms) {
                    if (bedrooms >= 0) {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    } else {
                        cout << "Bedrooms must be >= 0. Try again.\n";
                    }
                } else {
                    cout << "Invalid input. Enter an integer.\n";
                    cin.clear();
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            while (true) {
                cout << "Has lift (1 for yes / 0 for no): ";
                if (cin >> tmpInt) {
                    if (tmpInt == 0 || tmpInt == 1) {
                        hasLift = (tmpInt == 1);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    } else {
                        cout << "Enter 1 or 0.\n";
                    }
                } else {
                    cout << "Invalid input. Enter 1 or 0.\n";
                    cin.clear();
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            while (true) {
                cout << "Has parking (1 for yes / 0 for no): ";
                if (cin >> tmpInt) {
                    if (tmpInt == 0 || tmpInt == 1) {
                        hasParking = (tmpInt == 1);
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    } else {
                        cout << "Enter 1 or 0.\n";
                    }
                } else {
                    cout << "Invalid input. Enter 1 or 0.\n";
                    cin.clear();
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            while (true) {
                cout << "Enter maintenance charge: ";
                if (cin >> maintenanceCharge) {
                    if (maintenanceCharge >= 0.0) {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        break;
                    } else {
                        cout << "Maintenance charge must be non-negative. Try again.\n";
                    }
                } else {
                    cout << "Invalid input. Enter a numeric value.\n";
                    cin.clear();
                }
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }

            while (true) {
                cout << "Enter furnishing status: ";
                getline(cin, furnishingStatus);
                if (!furnishingStatus.empty()) break;
                cout << "Furnishing status cannot be empty. Please re-enter.\n";
            }

            string propertyID = generatePropertyID("Apartment", ownerName, price, area);
            Apartment apt(propertyID, ownerName, latitude, longitude, price, area, address, isAvailable, facing, landmark, ownershipType, floorNumber, totalFloors, bedrooms, hasLift, hasParking, maintenanceCharge, furnishingStatus);
            cout << "\nApartment Listed Successfully:\n";
            apt.display();

            ofstream file("properties.txt", ios::app);
            file << "Type: Apartment\n";
            file << "Property ID: " << propertyID << endl;
            file << "Owner: " << ownerName << endl;
            file << "Latitude: " << latitude << endl;
            file << "Longitude: " << longitude << endl;
            file << "Price: " << price << endl;
            file << "Area: " << area << endl;
            file << "Address: " << address << endl;
            file << "Availability: " << isAvailable << endl;
            file << "Facing: " << facing << endl;
            file << "Landmark: " << landmark << endl;
            file << "Ownership: " << ownershipType << endl;
            file << "Floors: " << floorNumber << "/" << totalFloors << endl;
            file << "Bedrooms: " << bedrooms << endl;
            file << "Lift: " << hasLift << endl;
            file << "Parking: " << hasParking << endl;
            file << "Maintenance: " << maintenanceCharge << endl;
            file << "Furnishing: " << furnishingStatus << endl;
            file << "----------------------------------------" << endl;
            file.close();
            break;
    }


        case 2: {
            string ownerName, address, facing, landmark, ownershipType, furnishingStatus;
            int bedrooms = 0;
            double latitude = 0.0, longitude = 0.0, price = 0.0, area = 0.0, plotArea = 0.0;
            int tmpInt;
            bool isAvailable = false, hasGarden = false, hasPrivatePool = false, hasGarage = false;

            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            while (true) {
                cout << "Enter owner name: ";
                getline(cin, ownerName);
                if (!ownerName.empty()) break;
                cout << "Owner name cannot be empty. Please re-enter.\n";
            }

            while (true) {
                cout << "Enter latitude (-90 to 90): ";
                if (cin >> latitude && latitude >= -90.0 && latitude <= 90.0) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                } else {
                    cout << "Invalid latitude. Enter a value between -90 and 90.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            while (true) {
                cout << "Enter longitude (-180 to 180): ";
                if (cin >> longitude && longitude >= -180.0 && longitude <= 180.0) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                } else {
                    cout << "Invalid longitude. Enter a value between -180 and 180.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            while (true) {
                cout << "Enter price: ";
                if (cin >> price && price >= 0.0) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                } else {
                    cout << "Invalid price. Enter a non-negative number.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            while (true) {
                cout << "Enter area (sq.ft): ";
                if (cin >> area && area > 0.0) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                } else {
                    cout << "Invalid area. Enter a positive number.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            while (true) {
                cout << "Enter address: ";
                getline(cin, address);
                if (!address.empty()) break;
                cout << "Address cannot be empty. Please re-enter.\n";
            }

            while (true) {
                cout << "Is available (1 for yes / 0 for no): ";
                if (cin >> tmpInt && (tmpInt == 0 || tmpInt == 1)) {
                    isAvailable = (tmpInt == 1);
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                } else {
                    cout << "Invalid input. Enter 1 or 0.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            while (true) {
                cout << "Enter facing: ";
                getline(cin, facing);
                if (!facing.empty()) break;
                cout << "Facing cannot be empty. Please re-enter.\n";
            }

            while (true) {
                cout << "Enter landmark: ";
                getline(cin, landmark);
                if (!landmark.empty()) break;
                cout << "Landmark cannot be empty. Please re-enter.\n";
            }

            while (true) {
                cout << "Enter ownership type: ";
                getline(cin, ownershipType);
                if (!ownershipType.empty()) break;
                cout << "Ownership type cannot be empty. Please re-enter.\n";
            }

            while (true) {
                cout << "Enter number of bedrooms: ";
                if (cin >> bedrooms && bedrooms >= 0) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                } else {
                    cout << "Invalid input. Bedrooms must be a non-negative integer.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            while (true) {
                cout << "Has garden (1 for yes / 0 for no): ";
                if (cin >> tmpInt && (tmpInt == 0 || tmpInt == 1)) {
                    hasGarden = (tmpInt == 1);
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                } else {
                    cout << "Invalid input. Enter 1 or 0.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            while (true) {
                cout << "Has private pool (1 for yes / 0 for no): ";
                if (cin >> tmpInt && (tmpInt == 0 || tmpInt == 1)) {
                    hasPrivatePool = (tmpInt == 1);
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                } else {
                    cout << "Invalid input. Enter 1 or 0.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            while (true) {
                cout << "Enter plot area (sq.ft): ";
                if (cin >> plotArea && plotArea > 0.0) {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                } else {
                    cout << "Invalid input. Enter a positive number for plot area.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            while (true) {
                cout << "Has garage (1 for yes / 0 for no): ";
                if (cin >> tmpInt && (tmpInt == 0 || tmpInt == 1)) {
                    hasGarage = (tmpInt == 1);
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    break;
                } else {
                    cout << "Invalid input. Enter 1 or 0.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }

            while (true) {
                cout << "Enter furnishing status: ";
                getline(cin, furnishingStatus);
                if (!furnishingStatus.empty()) break;
                cout << "Furnishing status cannot be empty. Please re-enter.\n";
            }

            string propertyID = generatePropertyID("Villa", ownerName, price, area);
            Villa villa(propertyID, ownerName, latitude, longitude, price, area, address, isAvailable, facing,
                        landmark, ownershipType, bedrooms, hasGarden, hasPrivatePool, plotArea, hasGarage, furnishingStatus);

            cout << "\nVilla Listed Successfully:\n";
            villa.display();

            ofstream file("properties.txt", ios::app);
            file << "Type: Villa\n";
            file << "Property ID: " << propertyID << endl;
            file << "Owner: " << ownerName << endl;
            file << "Latitude: " << latitude << endl;
            file << "Longitude: " << longitude << endl;
            file << "Price: " << price << endl;
            file << "Area: " << area << endl;
            file << "Address: " << address << endl;
            file << "Availability: " << isAvailable << endl;
            file << "Facing: " << facing << endl;
            file << "Landmark: " << landmark << endl;
            file << "Ownership: " << ownershipType << endl;
            file << "Bedrooms: " << bedrooms << endl;
            file << "Garden: " << hasGarden << endl;
            file << "Private Pool: " << hasPrivatePool << endl;
            file << "Plot Area: " << plotArea << endl;
            file << "Garage: " << hasGarage << endl;
            file << "Furnishing: " << furnishingStatus << endl;
            file << "----------------------------------------" << endl;
            file.close();
            break;
        }


        case 3: {
        string ownerName, address, facing, landmark, ownershipType, landType;
        double latitude = 0.0, longitude = 0.0, price = 0.0, area = 0.0;
        int tmpInt;
        bool isAvailable = false, hasCompoundWall = false, nearMainRoad = false, 
            isDTCPApproved = false, hasElectricity = false, hasWater = false;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        while (true) {
            cout << "Enter owner name: ";
            getline(cin, ownerName);
            if (!ownerName.empty()) break;
            cout << "Owner name cannot be empty. Please re-enter.\n";
        }

        while (true) {
            cout << "Enter latitude (-90 to 90): ";
            if (cin >> latitude && latitude >= -90.0 && latitude <= 90.0) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            cout << "Invalid latitude. Enter a value between -90 and 90.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        while (true) {
            cout << "Enter longitude (-180 to 180): ";
            if (cin >> longitude && longitude >= -180.0 && longitude <= 180.0) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            cout << "Invalid longitude. Enter a value between -180 and 180.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        while (true) {
            cout << "Enter price: ";
            if (cin >> price && price >= 0.0) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            cout << "Invalid price. Enter a non-negative number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        while (true) {
            cout << "Enter area (sq.ft): ";
            if (cin >> area && area > 0.0) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            cout << "Invalid area. Enter a positive number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        while (true) {
            cout << "Enter address: ";
            getline(cin, address);
            if (!address.empty()) break;
            cout << "Address cannot be empty. Please re-enter.\n";
        }

        while (true) {
            cout << "Is available (1 for yes / 0 for no): ";
            if (cin >> tmpInt && (tmpInt == 0 || tmpInt == 1)) {
                isAvailable = (tmpInt == 1);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            cout << "Invalid input. Enter 1 or 0.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        while (true) {
            cout << "Enter facing: ";
            getline(cin, facing);
            if (!facing.empty()) break;
            cout << "Facing cannot be empty. Please re-enter.\n";
        }

        while (true) {
            cout << "Enter landmark: ";
            getline(cin, landmark);
            if (!landmark.empty()) break;
            cout << "Landmark cannot be empty. Please re-enter.\n";
        }

        while (true) {
            cout << "Enter ownership type: ";
            getline(cin, ownershipType);
            if (!ownershipType.empty()) break;
            cout << "Ownership type cannot be empty. Please re-enter.\n";
        }

        while (true) {
            cout << "Enter land type (e.g., Residential, Commercial): ";
            getline(cin, landType);
            if (!landType.empty()) break;
            cout << "Land type cannot be empty. Please re-enter.\n";
        }

        while (true) {
            cout << "Has compound wall (1 for yes / 0 for no): ";
            if (cin >> tmpInt && (tmpInt == 0 || tmpInt == 1)) {
                hasCompoundWall = (tmpInt == 1);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            cout << "Invalid input. Enter 1 or 0.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        while (true) {
            cout << "Near main road (1 for yes / 0 for no): ";
            if (cin >> tmpInt && (tmpInt == 0 || tmpInt == 1)) {
                nearMainRoad = (tmpInt == 1);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            cout << "Invalid input. Enter 1 or 0.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        while (true) {
            cout << "Is DTCP approved (1 for yes / 0 for no): ";
            if (cin >> tmpInt && (tmpInt == 0 || tmpInt == 1)) {
                isDTCPApproved = (tmpInt == 1);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            cout << "Invalid input. Enter 1 or 0.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        while (true) {
            cout << "Has electricity access (1 for yes / 0 for no): ";
            if (cin >> tmpInt && (tmpInt == 0 || tmpInt == 1)) {
                hasElectricity = (tmpInt == 1);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            cout << "Invalid input. Enter 1 or 0.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        while (true) {
            cout << "Has water facility (1 for yes / 0 for no): ";
            if (cin >> tmpInt && (tmpInt == 0 || tmpInt == 1)) {
                hasWater = (tmpInt == 1);
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                break;
            }
            cout << "Invalid input. Enter 1 or 0.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }

        string propertyID = generatePropertyID("Land", ownerName, price, area);
        Land land(propertyID, ownerName, latitude, longitude, price, area, address,
                isAvailable, facing, landmark, ownershipType, landType,
                hasCompoundWall, nearMainRoad, isDTCPApproved, hasElectricity, hasWater);

        cout << "\nLand Listed Successfully:\n";
        land.display();

        ofstream file("properties.txt", ios::app);
        file << "Type: Land\n";
        file << "Property ID: " << propertyID << endl;
        file << "Owner: " << ownerName << endl;
        file << "Latitude: " << latitude << endl;
        file << "Longitude: " << longitude << endl;
        file << "Price: " << price << endl;
        file << "Area: " << area << endl;
        file << "Address: " << address << endl;
        file << "Availability: " << isAvailable << endl;
        file << "Facing: " << facing << endl;
        file << "Landmark: " << landmark << endl;
        file << "Ownership: " << ownershipType << endl;
        file << "Land Type: " << landType << endl;
        file << "Compound Wall: " << hasCompoundWall << endl;
        file << "Near Main Road: " << nearMainRoad << endl;
        file << "DTCP Approved: " << isDTCPApproved << endl;
        file << "Electricity: " << hasElectricity << endl;
        file << "Water: " << hasWater << endl;
        file << "----------------------------------------" << endl;
        file.close();

        break;
}


        case 4:
            cout << "Exiting Listing...\n";
            return;
        default:
            cout << "Invalid choice. Please try again.\n";
    }
}

void Finding()
{
    PropertySearchTrie ownerTrie;
    PropertySearchTrie landmarkTrie;
    unordered_map<int, string> idToPropID;
    int nextIndexId = 1;
    loadTriesFromFile("properties.txt", ownerTrie, landmarkTrie, idToPropID, nextIndexId);

    Boundary indiaBoundary(0, 0, 100, 100); // example boundary
    QuadTree qt(indiaBoundary);

    loadQuadTreeFromFile("properties.txt", qt);
    int choice;
    cout<<"You Chose Finding Property\n";
    cout<<"What are you looking for\n";
    cout<<"1.Apartment\n";
    cout<<"2.Villa\n";
    cout<<"3.Land\n";
    cout<<"4.Exit\n";
    cin>>choice;
    switch(choice)
    {
        case 1:
            int inputapt;
            cout<<"You chose Apartment\n";
            cout<<"1.Choose By Owner\n";
            cout<<"2.Choose By Landmark\n";
            cout<<"3.Choose By Latitude and Longitude\n";
            cout<<"4.Choose By Price\n";
            cout<<"5.Choose By Bedrooms\n";
            cout<<"6.Exit\n";
            cin>>inputapt;
            switch(inputapt)
            {
                case 1:
                {
                    cout << "Search By Owner Name:\n";
                    cin.ignore();
                    string name;
                    getline(cin, name);

                    vector<int> results = ownerTrie.search(name);
                    bool found = false;
                    cout << "\nApartments found:\n";
                    for (int id : results)
                    {
                        string pid = idToPropID[id];
                        if (pid.rfind("APA_", 0) == 0) // check if it starts with "APA_"
                        {
                            cout << "- Property ID: " << pid << endl;
                            found = true;
                        }
                    }
                    if (!found)
                        cout << "No Apartments found for owner \"" << name << "\".\n";
                    break;
                }
                case 2:
                {
                    cout << "Search By Landmark:\n";
                    cin.ignore();
                    string landmark;
                    getline(cin, landmark);

                    vector<int> results = landmarkTrie.search(landmark);
                    bool found = false;
                    cout << "\nApartments found:\n";
                    for (int id : results)
                    {
                        string pid = idToPropID[id];
                        if (pid.rfind("APA_", 0) == 0)
                        {
                            cout << "- Property ID: " << pid << endl;
                            found = true;
                        }
                    }
                    if (!found)
                        cout << "No Apartments found near \"" << landmark << "\".\n";
                    break;
                }
                case 3:
                {
                    cout << "Search By Latitude and Longitude\n";
                    searchByLocation(qt, "APA_");
                    break;
                }
                case 4:
                    cout<<"Search By Price\n";
                    break;
                case 5:
                    cout<<"Search By Bedrooms\n";
                    break;
                case 6:
                    cout<<"Exiting Search\n";
                    return;

            }
            break;
        case 2:
            int inputvil;
            cout<<"You chose Villa\n";
            cout<<"1.Choose By Owner\n";
            cout<<"2.Choose By Landmark\n";
            cout<<"3.Choose By Latitude and Longitude\n";
            cout<<"4.Choose By Price\n";
            cout<<"5.Choose By Bedrooms\n";
            cout<<"6.Exit\n";
            cin>>inputvil;
            switch(inputvil)
            {
                case 1:
                {
                    cout << "Search By Owner Name:\n";
                    cin.ignore();
                    string name;
                    getline(cin, name);

                    vector<int> results = ownerTrie.search(name);
                    bool found = false;
                    cout << "\nVillas found:\n";
                    for (int id : results)
                    {
                        string pid = idToPropID[id];
                        if (pid.rfind("VIL_", 0) == 0)
                        {
                            cout << "- Property ID: " << pid << endl;
                            found = true;
                        }
                    }
                    if (!found)
                        cout << "No Villas found for owner \"" << name << "\".\n";
                    break;
                }
                case 2:
                {
                    cout << "Search By Landmark:\n";
                    cin.ignore();
                    string landmark;
                    getline(cin, landmark);

                    vector<int> results = landmarkTrie.search(landmark);
                    bool found = false;
                    cout << "\nVillas found:\n";
                    for (int id : results)
                    {
                        string pid = idToPropID[id];
                        if (pid.rfind("VIL_", 0) == 0)
                        {
                            cout << "- Property ID: " << pid << endl;
                            found = true;
                        }
                    }
                    if (!found)
                        cout << "No Villas found near \"" << landmark << "\".\n";
                    break;
                }
                case 3:
                {   
                    cout << "Search By Latitude and Longitude\n";
                    searchByLocation(qt, "VIL_");
                    break;
                }
                case 4:
                    cout<<"Search By Price\n";
                    break;
                case 5:
                    cout<<"Search By Bedrooms\n";
                    break;
                case 6:
                    cout<<"Exiting Search\n";
                    return;

            }
            break;
        case 3:
            int inputland;
            cout<<"You chose Land\n";
            cout<<"1.Choose By Owner\n";
            cout<<"2.Choose By Landmark\n";
            cout<<"3.Choose By Latitude and Longitude\n";
            cout<<"4.Choose By Price\n";
            cout<<"5.Choose By DTCP Approval\n";
            cout<<"6.Choose By Electricity access\n";
            cout<<"7.Choose By Water Status\n";
            cout<<"8.Exit\n";
            cin>>inputland;
            switch(inputland)
            {
                case 1:
                {
                    cout << "Search By Owner Name:\n";
                    cin.ignore();
                    string name;
                    getline(cin, name);

                    vector<int> results = ownerTrie.search(name);
                    bool found = false;
                    cout << "\nLands found:\n";
                    for (int id : results)
                    {
                        string pid = idToPropID[id];
                        if (pid.rfind("LAN_", 0) == 0)
                        {
                            cout << "- Property ID: " << pid << endl;
                            found = true;
                        }
                    }
                    if (!found)
                        cout << "No Lands found for owner \"" << name << "\".\n";
                    break;
                }

                case 2:
                {
                    cout << "Search By Landmark:\n";
                    cin.ignore();
                    string landmark;
                    getline(cin, landmark);

                    vector<int> results = landmarkTrie.search(landmark);
                    bool found = false;
                    cout << "\nLands found:\n";
                    for (int id : results)
                    {
                        string pid = idToPropID[id];
                        if (pid.rfind("LAN_", 0) == 0)
                        {
                            cout << "- Property ID: " << pid << endl;
                            found = true;
                        }
                    }
                    if (!found)
                        cout << "No Lands found near \"" << landmark << "\".\n";
                    break;
                }
                case 3:
                {
                    cout << "Search By Latitude and Longitude\n";
                    searchByLocation(qt, "LAN_");
                    break;
                }
                case 4:
                    cout<<"Search By Price\n";
                    break;
                case 5:
                    cout<<"Search By DTCP\n";
                    break;
                case 6:
                    cout<<"Search By Electricity access\n";
                    break;
                case 7:
                    cout<<"Search By Water access\n";
                    break;
                case 8:
                    cout<<"Exiting Search\n";
                    return;

            }
            break;
        case 4:
            cout<<"Exiting Finding\n";
            return;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
    }
    
}


int main()
{

    while(1)
    {
        int input;
        int wc;
        cout<<"Welcome to Property Search Engine!!\n";
        cout<<"Pick The Choice\n";
        cout<<"1.List a Property\n";
        cout<<"2.Find a Property\n";
        cout<<"3.Exit\n";
        cin>>input;
        switch (input)
        {
            case 1:
                Listing();
                break;
            
            case 2:
                Finding();
                break;
            case 3:
                cout<<"You chose exit\n";
                wc=1;
                break;
            default:
                cout<<"Not a valid option\n";
                wc=1;
                break;
        }
        if(wc==1)
        {
            cout<<"ThankYou for Choosing us!!!";
            break;
        }
    }
}