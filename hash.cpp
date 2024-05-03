#include "hash.h"
#include "cache.h"


void Hash::add(Node* node) {
    // get hash key
    int hashKey = hash(node->key);

    if (get(node->key) == nullptr) {  // check node duplicate
        // create new hash node
        HashNode* newHashNode = new HashNode;

        // input item value
        newHashNode->item = node;

        HashNode* head = arr[hashKey];

        newHashNode->next = head;
        head->above = newHashNode;
        head = newHashNode;
    }
}

void Hash::remove(std::string key) {
    // get hash key
    int hashKey = hash(key);

    Node* currentNode = get(key);

    if (currentNode != nullptr) {  // check node duplicate

        HashNode* head = arr[hashKey];
        
        while (head != nullptr) {
            if (head->item->key == key) {  // if Node key equal paramiter key
                head->above->next = head->next;
                head->next->above = head->above;
                delete head;
            }

            head = head->next;
        }
    }
}

Node* Hash::get(std::string key) {
    int hashKey = hash(key);
    HashNode* hashNode = arr[hashKey];
    if (hashNode == nullptr) {
        return nullptr;
    } else {
        while (hashNode != nullptr) {  // serch and check equal key
            if (hashNode->item->key == key) {
                return hashNode->item;
            }
            hashNode = hashNode->next;
        }
    }
    return nullptr;
}

int Hash::hash(std::string key) {
    int sum = 0;
    for (int i = 0; i < key.length(); i++) {
        sum += key[i];
    }
    return sum / HASHSIZE;
}