#include "PropertySearchTrie.h"
#include <algorithm>
#include <cctype>

PropertySearchTrie::PropertySearchTrie() {
    root = new TrieNode();
}

void PropertySearchTrie::collectPropertyIDs(TrieNode* node, std::vector<int>& result) {
    if (node->isEndOfWord) {
        result.insert(result.end(), node->propertyIDs.begin(), node->propertyIDs.end());
    }
    for (auto& child : node->children) {
        collectPropertyIDs(child.second, result);
    }
}

void PropertySearchTrie::insert(const std::string& propertyName, int propertyID) {
    TrieNode* node = root;
    for (char c : propertyName) {
        c = std::tolower(c);
        if (!node->children.count(c)) {
            node->children[c] = new TrieNode();
        }
        node = node->children[c];
    }
    node->isEndOfWord = true;
    node->propertyIDs.push_back(propertyID);
}

std::vector<int> PropertySearchTrie::search(const std::string& prefix) {
    TrieNode* node = root;
    for (char c : prefix) {
        c = std::tolower(c);
        if (!node->children.count(c)) return {};
        node = node->children[c];
    }
    std::vector<int> result;
    collectPropertyIDs(node, result);
    return result;
}
