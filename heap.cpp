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
