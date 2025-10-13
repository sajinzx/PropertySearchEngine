#ifndef PROPERTY_SEARCH_TRIE_H
#define PROPERTY_SEARCH_TRIE_H

#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    vector<int> propertyIDs;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

class PropertySearchTrie {
private:
    TrieNode* root;

    void collectPropertyIDs(TrieNode* node, vector<int>& result);

public:
    PropertySearchTrie();

    void insert(const string& propertyName, int propertyID);
    vector<int> search(const string& prefix);
};

#endif
