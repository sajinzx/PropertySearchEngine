#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <utility>  // for pair
#include <string>
using namespace std;

// Max-heap based on price (first element of pair)
class Heap {
private:
    pair<double, string> arr[1000]; // (price, propertyID)
    int size;

    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    Heap();

    // Core heap operations
    void insert(double price, const string& propertyID);
    pair<double, string> getRoot();       // Get highest price property
    pair<double, string> extractRoot();   // Remove and return highest price
    bool isEmpty() const;

    // Display all elements
    void display() const;

    void showPropertiesBelow(double maxPrice) const;
    void loadFromFile(const string& filename, const string& type);

};

#endif
