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

    Node* currentNode = head;
    while (currentNode != nullptr) {
        
        if (key == currentNode->key) {
            // update head
            value = currentNode->item.intItem;
            if (currentNode == head) {
                ;
            } else if (currentNode == tail) {
                tail->next = head;
                
                head->above = tail;
                tail->above = nullptr;

                head = tail;
            } else {
                currentNode->next->above = currentNode->above;
                currentNode->above->next = currentNode->next;

                currentNode->next = head;
                head->above = currentNode;
                
                head = currentNode;
            }

            return true;
        }
        currentNode = currentNode->next;
    }

    return false;
}

bool Cache::get(std::string key, double &value) {
    if (head == nullptr) {
        return false;
    }

    Node* currentNode = head;
    while (currentNode != nullptr) {
        if (key == currentNode->key) {
            // update head
            value = currentNode->item.doubleItem;
            if (currentNode == head) {
                ;
            } else if (currentNode == tail) {
                tail->next = head;
                
                head->above = tail;
                tail->above = nullptr;

                head = tail;
            } else {
                currentNode->next->above = currentNode->above;
                currentNode->above->next = currentNode->next;

                currentNode->next = head;
                head->above = currentNode;
                
                head = currentNode;
            }

            return true;
        }
        currentNode = currentNode->next;
    }

    return false;
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