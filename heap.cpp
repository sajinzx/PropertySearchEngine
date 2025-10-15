#include "Heap.h"

Heap::Heap() {
    size = 0;
}

void Heap::heapifyUp(int index) {
    while (index > 1 && arr[index / 2].first < arr[index].first) {
        swap(arr[index], arr[index / 2]);
        index /= 2;
    }
}

void Heap::heapifyDown(int index) {
    int largest = index;
    int left = 2 * index;
    int right = 2 * index + 1;

    if (left <= size && arr[left].first > arr[largest].first)
        largest = left;
    if (right <= size && arr[right].first > arr[largest].first)
        largest = right;

    if (largest != index) {
        swap(arr[index], arr[largest]);
        heapifyDown(largest);
    }
}

void Heap::insert(double price, const string& propertyID) {
    if (size >= 999) {
        cout << "Heap is full!\n";
        return;
    }
    size++;
    arr[size] = make_pair(price, propertyID);
    heapifyUp(size);
}

pair<double, string> Heap::getRoot() {
    if (size == 0)
        return make_pair(-1.0, "Empty");
    return arr[1];
}

pair<double, string> Heap::extractRoot() {
    if (size == 0)
        return make_pair(-1.0, "Empty");

    pair<double, string> root = arr[1];
    arr[1] = arr[size];
    size--;
    heapifyDown(1);
    return root;
}

bool Heap::isEmpty() const {
    return size == 0;
}

void Heap::display() const {
    cout << "\nHeap Elements (Price, ID):\n";
    for (int i = 1; i <= size; i++) {
        cout << arr[i].first << " - " << arr[i].second << endl;
    }
}

// ✅ New Function: Show all properties below a given price
void Heap::showPropertiesBelow(double maxPrice) const {
    cout << "\n--- Properties below price " << maxPrice << " ---\n";
    bool found = false;
    for (int i = 1; i <= size; i++) {
        if (arr[i].first <= maxPrice) {
            cout << "Property ID: " << arr[i].second
                 << " | Price: " << arr[i].first << endl;
            found = true;
        }
    }
    if (!found)
        cout << "No properties found below this price.\n";
}

#include <fstream>
#include <sstream>
#include <algorithm>

void Heap::loadFromFile(const string& filename, const string& type) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    string currentType;
    string propertyID;
    double price = -1;

    cout << "\nLoading " << type << " properties from file...\n";

    while (getline(file, line)) {
        // Trim leading/trailing spaces
        line.erase(0, line.find_first_not_of(" \t"));
        line.erase(line.find_last_not_of(" \t") + 1);

        if (line.rfind("Type:", 0) == 0) {
            currentType = line.substr(5);
            currentType.erase(0, currentType.find_first_not_of(" \t"));
        } 
        else if (line.rfind("Property ID:", 0) == 0) {
            propertyID = line.substr(12);
            propertyID.erase(0, propertyID.find_first_not_of(" \t"));
        } 
        else if (line.rfind("Price:", 0) == 0) {
            string priceStr = line.substr(6);
            priceStr.erase(0, priceStr.find_first_not_of(" \t"));
            try {
                price = stod(priceStr);
            } catch (...) {
                price = -1;
            }
        } 
        else if (line.find("----------------------------------------") != string::npos) {
            // Reached end of one property block
            if (currentType == type && !propertyID.empty() && price >= 0) {
                insert(price, propertyID);
            }

            // Reset for next property
            currentType.clear();
            propertyID.clear();
            price = -1;
        }
    }

    // Handle last block if file doesn’t end with a line of dashes
    if (currentType == type && !propertyID.empty() && price >= 0) {
        insert(price, propertyID);
    }

    file.close();
    cout << "✅ Successfully loaded " << type << " properties into heap.\n";
}
