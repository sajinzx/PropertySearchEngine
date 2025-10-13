#ifndef PROPERTY_SEARCH_TRIE_H
#define PROPERTY_SEARCH_TRIE_H

#include <unordered_map>
#include <vector>
#include <string>

struct TrieNode {
    std::unordered_map<char, TrieNode*> children;
    std::vector<int> propertyIDs;
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {}
};

class PropertySearchTrie {
private:
    TrieNode* root;

    void collectPropertyIDs(TrieNode* node, std::vector<int>& result);

public:
    PropertySearchTrie();

    void insert(const std::string& propertyName, int propertyID);
    std::vector<int> search(const std::string& prefix);
};

#endif
