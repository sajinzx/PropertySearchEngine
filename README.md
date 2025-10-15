# PropertySearchEngine

**Property Search Engine** is a C++ console application that allows users to search for real estate properties — Apartments, Villas, and Lands — based on various criteria such as owner, landmark, location and price. The project uses efficient data structures like **Tries, QuadTrees, and Heaps** to enable fast search and retrieval of property data.

---

## Features

- **Search by Owner Name**  
  Quickly find properties owned by a specific person using a Trie data structure.

- **Search by Landmark**  
  Find properties near a landmark efficiently.

- **Search by Location**  
  Find properties within a specific latitude and longitude using a QuadTree spatial index.

- **Search by Price**  
  Retrieve properties below a given price using a Max-Heap structure.



---

## Data File Format

- **Properties are loaded from a text file (`properties.txt`) in the following format:**

Type: Villa

Property ID: VIL_KAR_593827_1760468725

Owner: karishma

Latitude: 13.02

Longitude: 80.28

Price: 49000000

Area: 4700

Address: 13TriplicaneChennai

Availability: 1

Facing: south

Landmark: ParthasarathyTemple

Ownership: own

Bedrooms: 5

Garden: 0

Private Pool: 1

Plot Area: 6900

Garage: 1

Furnishing: semi-furnished


## Data Structures Used

- **Trie**: For fast search by owner and landmark names.
- **QuadTree**: For efficient spatial search by latitude and longitude.
- **Heap**: For retrieving properties below a specified price efficiently.

---

## How to Run

1. Clone the repository:
    ```bash
    git clone "https://github.com/sajinzx/PropertySearchEngine.git"

2. Compile :
    ```bash
    g++ -std=c++17 *.cpp -o PropertyFinder

3. Run the executable:
    ```bash
    ./PropertyFinder


