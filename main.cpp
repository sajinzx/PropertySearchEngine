#include <iostream>
#include "Apartment.h"
#include "Land.h"
#include "PropertyIDGenerator.h"
#include "Villa.h"
using namespace std;

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
      string ownerName, address, facing, landmark, ownershipType,
          furnishingStatus;
      int floorNumber, totalFloors, bedrooms;
      double latitude, longitude, price, area, maintenanceCharge;
      bool isAvailable, hasLift, hasParking;

      cout << "Enter owner name: ";
      cin.ignore();
      getline(cin, ownerName);
      cout << "Enter latitude: ";
      cin >> latitude;
      cout << "Enter longitude: ";
      cin >> longitude;
      cout << "Enter price: ";
      cin >> price;
      cout << "Enter area: ";
      cin >> area;
      cin.ignore();
      cout << "Enter address: ";
      getline(cin, address);
      cout << "Is available (1/0): ";
      cin >> isAvailable;
      cin.ignore();
      cout << "Enter facing: ";
      getline(cin, facing);
      cout << "Enter landmark: ";
      getline(cin, landmark);
      cout << "Enter ownership type: ";
      getline(cin, ownershipType);

      cout << "Enter floor number: ";
      cin >> floorNumber;
      cout << "Enter total floors: ";
      cin >> totalFloors;
      cout << "Enter number of bedrooms: ";
      cin >> bedrooms;
      cout << "Has lift (1/0): ";
      cin >> hasLift;
      cout << "Has parking (1/0): ";
      cin >> hasParking;
      cout << "Enter maintenance charge: ";
      cin >> maintenanceCharge;
      cin.ignore();
      cout << "Enter furnishing status: ";
      getline(cin, furnishingStatus);

      string propertyID = generatePropertyID("Apartment", ownerName, price, area);

      Apartment apt(propertyID, ownerName,  latitude, longitude,
                    price, area, address, isAvailable, facing, landmark,
                    ownershipType, floorNumber, totalFloors, bedrooms, hasLift,
                    hasParking, maintenanceCharge, furnishingStatus);

      cout << "\nApartment Listed Successfully:\n";
      apt.display();
      break;
    }

    case 2: {
      string ownerName, address, facing, landmark, ownershipType,
          furnishingStatus;
      int bedrooms;
      double latitude, longitude, price, area, plotArea;
      bool isAvailable, hasGarden, hasPrivatePool, hasGarage;

      cout << "Enter owner name: ";
      cin.ignore();
      getline(cin, ownerName);
      cout << "Enter latitude: ";
      cin >> latitude;
      cout << "Enter longitude: ";
      cin >> longitude;
      cout << "Enter price: ";
      cin >> price;
      cout << "Enter area: ";
      cin >> area;
      cin.ignore();
      cout << "Enter address: ";
      getline(cin, address);
      cout << "Is available (1/0): ";
      cin >> isAvailable;
      cin.ignore();
      cout << "Enter facing: ";
      getline(cin, facing);
      cout << "Enter landmark: ";
      getline(cin, landmark);
      cout << "Enter ownership type: ";
      getline(cin, ownershipType);

      cout << "Enter number of bedrooms: ";
      cin >> bedrooms;
      cout << "Has garden (1/0): ";
      cin >> hasGarden;
      cout << "Has private pool (1/0): ";
      cin >> hasPrivatePool;
      cout << "Enter plot area: ";
      cin >> plotArea;
      cout << "Has garage (1/0): ";
      cin >> hasGarage;
      cin.ignore();
      cout << "Enter furnishing status: ";
      getline(cin, furnishingStatus);

      string propertyID = generatePropertyID("Villa", ownerName, price, area);

      Villa villa(propertyID, ownerName, latitude, longitude, price,
                  area, address, isAvailable, facing, landmark, ownershipType,
                  bedrooms, hasGarden, hasPrivatePool, plotArea, hasGarage,
                  furnishingStatus);

      cout << "\nVilla Listed Successfully:\n";
      villa.display();
      break;
    }

    case 3: {
      string ownerName, address, facing, landmark, ownershipType, landType;
      double latitude, longitude, price, area;
      bool isAvailable, hasCompoundWall, nearMainRoad, isDTCPApproved,
          hasElectricity, hasWater;

      cout << "Enter owner name: ";
      cin.ignore();
      getline(cin, ownerName);
      cout << "Enter latitude: ";
      cin >> latitude;
      cout << "Enter longitude: ";
      cin >> longitude;
      cout << "Enter price: ";
      cin >> price;
      cout << "Enter area: ";
      cin >> area;
      cin.ignore();
      cout << "Enter address: ";
      getline(cin, address);
      cout << "Is available (1/0): ";
      cin >> isAvailable;
      cin.ignore();
      cout << "Enter facing: ";
      getline(cin, facing);
      cout << "Enter landmark: ";
      getline(cin, landmark);
      cout << "Enter ownership type: ";
      getline(cin, ownershipType);

      cout << "Enter land type: ";
      getline(cin, landType);
      cout << "Has compound wall (1/0): ";
      cin >> hasCompoundWall;
      cout << "Near main road (1/0): ";
      cin >> nearMainRoad;
      cout << "Is DTCP approved (1/0): ";
      cin >> isDTCPApproved;
      cout << "Has electricity access (1/0): ";
      cin >> hasElectricity;
      cout << "Has water facility (1/0): ";
      cin >> hasWater;

      string propertyID = generatePropertyID("Land", ownerName, price, area);

      Land land(propertyID, ownerName, latitude, longitude, price, area,
                address, isAvailable, facing, landmark, ownershipType, landType,
                hasCompoundWall, nearMainRoad, isDTCPApproved, hasElectricity,
                hasWater);

      cout << "\nLand Listed Successfully:\n";
      land.display();
      break;
    }

    case 4:
      cout << "Exiting Listing...\n";
      return;

    default:
      cout << "Invalid choice. Please try again.\n";
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
                cout<<"You chose Finding\n";
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