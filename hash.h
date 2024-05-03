#ifndef HASH_H
#define HASH_H

#define HASHSIZE 10

#include <string>
#include "cache.h"

class HashNode {
public:
    Node* item;
    HashNode* above;
    HashNode* next;
};

class Hash {
private:
    HashNode* arr[HASHSIZE];
    
public:
    Hash() { }
    ~Hash() { }

    // add Node item for HashNode arr
    void add(Node* node);

    // remove Node item for HashNode arr
    void remove(std::string key);

    // get Node item for HashNode arr
    Node* get(std::string key);

    // get hash for file name
    int hash(std::string filename);
};

#endif