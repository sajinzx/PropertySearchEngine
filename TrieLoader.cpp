#include "TrieLoader.h"
#include <fstream>
#include <iostream>

using namespace std;

void loadTriesFromFile(const string &filename,PropertySearchTrie &ownerTrie,PropertySearchTrie &landmarkTrie,unordered_map<int, string> &idToPropID,int &nextIndexId)
{
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Could not open file " << filename << endl;
        return;
    }

    string line;
    string propertyID = "";
    string owner = "";
    string landmark = "";

    while (getline(file, line)) {
        // Trim empty lines
        if (line.empty()) continue;

        // Detect end of one property block
        if (line.find("----------------------------------------") != string::npos) {
            // If property info is found, insert into trie
            if (propertyID != "" && owner != "") {
                int id = nextIndexId++;
                idToPropID[id] = propertyID;

                ownerTrie.insert(owner, id);

                if (landmark != "")
                    landmarkTrie.insert(landmark, id);
            }

            // Reset for next property
            propertyID = "";
            owner = "";
            landmark = "";
            continue;
        }

        // Read Property ID
        if (line.find("Property ID:") == 0) {
            propertyID = line.substr(12);
            while (!propertyID.empty() && propertyID[0] == ' ')
                propertyID.erase(0, 1);
        }

        // Read Owner
        else if (line.find("Owner:") == 0) {
            owner = line.substr(6);
            while (!owner.empty() && owner[0] == ' ')
                owner.erase(0, 1);
        }

        // Read Landmark
        else if (line.find("Landmark:") == 0) {
            landmark = line.substr(9);
            while (!landmark.empty() && landmark[0] == ' ')
                landmark.erase(0, 1);
        }
    }

    // Handle last block if file doesn't end with separator
    if (propertyID != "" && owner != "") {
        int id = nextIndexId++;
        idToPropID[id] = propertyID;

        ownerTrie.insert(owner, id);

        if (landmark != "")
            landmarkTrie.insert(landmark, id);
    }

    file.close();
    cout << "Data loaded successfully into tries.\n";
}
