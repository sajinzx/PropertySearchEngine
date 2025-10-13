#ifndef TRIELOADER_H
#define TRIELOADER_H

#include "PropertySearchTrie.h"
#include <string>
#include <unordered_map>

using namespace std;

void loadTriesFromFile(const string &filename,PropertySearchTrie &ownerTrie,PropertySearchTrie &landmarkTrie,unordered_map<int, string> &idToPropID,int &nextIndexId);

#endif
