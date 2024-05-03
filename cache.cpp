#include "cache.h"
#include <iostream>
#include <sstream>


Cache::Cache() {
    head = nullptr;
    tail = nullptr;
    len = 0;
}

Cache::~Cache() {
    
}

void Cache::add(std::string key, int value) {
    Node *newNode = new Node();
    newNode->key = key;
    newNode->item.intItem = value;

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        return;
    }

    // delete tail node
    if (len >= CACHE_SIZE) {
        Node* curruntNode = tail;
        
        // remove hash databases
        hash->remove(curruntNode->key);

        tail = tail->above;
        
        tail->next = nullptr;
        delete curruntNode;
        len--;
    }

    len++;

    // add node;
    head->above = newNode;
    newNode->next = head;
    head = newNode;

    if (tail->above == nullptr) {
        tail->above = newNode;
    }

    // add hash database
    hash->add(newNode);
}

void Cache::add(std::string key, double value) {
    Node *newNode = new Node();
    newNode->key = key;
    newNode->item.doubleItem = value;
    
    len++;

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        return;
    }

    // delete tail node
    if (len >= CACHE_SIZE) {
        Node* curruntNode = tail;
        
        // remove hash databases
        hash->remove(curruntNode->key);
        
        tail = tail->above;
        tail->next = NULL;
        delete curruntNode;
        len--;
    }

    len++;

    // add node;
    head->above = newNode;
    newNode->next = head;
    head = newNode;

    if (tail->above == nullptr) {
        tail->above = newNode;
    }

    // add hash database
    hash->add(newNode);
}

bool Cache::get(std::string key, int &value) {
    if (head == nullptr) {
        return false;
    }

    Node* currentNode; // = head;
    // while (currentNode != nullptr) {
        
    //     if (key == currentNode->key) {
    //         // update head
    //         value = currentNode->item.intItem;
    //         if (currentNode == head) {
    //             ;
    //         } else if (currentNode == tail) {
    //             tail->next = head;
                
    //             head->above = tail;
    //             tail->above = nullptr;

    //             head = tail;
    //         } else {
    //             currentNode->next->above = currentNode->above;
    //             currentNode->above->next = currentNode->next;

    //             currentNode->next = head;
    //             head->above = currentNode;
                
    //             head = currentNode;
    //         }

    //         return true;
    //     }
    //     currentNode = currentNode->next;
    // }

    currentNode = hash->get(key);
    if (currentNode == nullptr) {
        return false;
    }

    value = currentNode->item.intItem;

    return true;
}

bool Cache::get(std::string key, double &value) {
    if (head == nullptr) {
        return false;
    }

    Node* currentNode;  // = head;
    // while (currentNode != nullptr) {
    //     if (key == currentNode->key) {
    //         // update head
    //         value = currentNode->item.doubleItem;
    //         if (currentNode == head) {
    //             ;
    //         } else if (currentNode == tail) {
    //             tail->next = head;
                
    //             head->above = tail;
    //             tail->above = nullptr;

    //             head = tail;
    //         } else {
    //             currentNode->next->above = currentNode->above;
    //             currentNode->above->next = currentNode->next;

    //             currentNode->next = head;
    //             head->above = currentNode;
                
    //             head = currentNode;
    //         }

    //         return true;
    //     }
    //     currentNode = currentNode->next;
    // }

    currentNode = hash->get(key);
    if (currentNode == nullptr) {
        return false;
    }

    value = currentNode->item.intItem;

    return true;
}

std::string Cache::toString() {
    std::ostringstream ss;
    
    if (head == nullptr) {
        return "";
    }

    Node* currentNode = head;
    while (currentNode->next != nullptr) {
        if (currentNode->item.doubleItem == -1) {
            ss << "[" << currentNode->key <<": " << currentNode->item.intItem <<"]";
        } else {
            ss << "[" << currentNode->key <<": " << currentNode->item.doubleItem <<"]";
        }
        ss << " -> ";

        currentNode = currentNode->next;
        
    }

    if (currentNode->item.doubleItem == -1) {
        ss << "["  << currentNode->key <<": " << currentNode->item.intItem <<"]";
    } else {
        ss << "["  << currentNode->key <<": " << currentNode->item.doubleItem <<"]";
    }

    ss << "\n";

    return ss.str();
}

// hash


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
    std::cout << "Test";
    if (hashNode == nullptr) {
        return nullptr;
    } else {
        while (hashNode != nullptr) {  // serch and check equal key
            std::cout << "Test" << hashNode;
            if (hashNode->item->key == key) {
                std::cout << "Test";
                return hashNode->item;
            }
            hashNode = hashNode->next;
        }
        std::cout << "Test";
    }
    return nullptr;
}

int Hash::hash(std::string key) {
    int sum = 0;
    for (int i = 0; i < key.length(); i++) {
        sum += key[i];
    }
    return sum / HASH_SIZE;
}