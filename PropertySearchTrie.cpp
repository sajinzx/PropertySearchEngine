#include "PropertySearchTrie.h"
#include <algorithm>
#include <cctype>

using namespace std;

PropertySearchTrie::PropertySearchTrie() {
    root = new TrieNode();
}

void PropertySearchTrie::collectPropertyIDs(TrieNode* node, vector<int>& result) {
    if (node->isEndOfWord) {
        result.insert(result.end(), node->propertyIDs.begin(), node->propertyIDs.end());
    }
    for (auto& child : node->children) {
        collectPropertyIDs(child.second, result);
    }
}

void PropertySearchTrie::insert(const string& propertyName, int propertyID) {
    TrieNode* node = root;
    for (char c : propertyName) {
        c = tolower(c);
        if (!node->children.count(c)) {
            node->children[c] = new TrieNode();
        }
        node = node->children[c];
    }
    node->isEndOfWord = true;
    node->propertyIDs.push_back(propertyID);
}

vector<int> PropertySearchTrie::search(const string& prefix) {
    TrieNode* node = root;
    for (char c : prefix) {
        c = tolower(c);
        if (!node->children.count(c)) return {};
        node = node->children[c];
    }
    vector<int> result;
    collectPropertyIDs(node, result);
    return result;
}
