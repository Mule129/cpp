#include "cache.h"

// TODO: 필요한 함수 구현
Cache::Cache() {
    head = nullptr;
    tail = nullptr;
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
    Node* curruntNode = tail;
    tail = tail->above;
    delete curruntNode;

    // add node;
    newNode->next = head;
    head = newNode;
}

void Cache::add(std::string key, double value) {
    Node *newNode = new Node();
    newNode->key = key;
    newNode->item.doubleItem = value;

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        return;
    }

    // delete tail node
    Node* curruntNode = tail;
    tail = tail->above;
    delete curruntNode;

    // add node;
    newNode->next = head;
    head->above = newNode;
    head = newNode;
}

bool Cache::get(std::string key, int &value) {
    if (head == nullptr) {
        return false;
    }

    Node* currentNode = head;
    while (currentNode->next == nullptr) {
        if (key == currentNode->key) {
            value = currentNode->item.intItem;

            // update head
            currentNode->next->above = currentNode->above;
            currentNode->above->next = currentNode->next;

            currentNode->next = head;
            head->above = currentNode;


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
    while (currentNode->next == nullptr) {
        if (key == currentNode->key) {
            value = currentNode->item.doubleItem;

            // update head
            currentNode->next->above = currentNode->above;
            currentNode->above->next = currentNode->next;

            currentNode->next = head;
            head->above = currentNode;


            return true;
        }
        currentNode = currentNode->next;
    }

    return false;
}

std::string Cache::toString() {
    if (head == nullptr) {
        return;
    }

    std::string stdValue = "";

    Node* currentNode = head;
    while (currentNode->next == nullptr) {
        if (currentNode->item.doubleItem == NULL) {
            stdValue.append("[" + currentNode->key + ": " + std::to_string(currentNode->item.intItem) + "]");
        } else {
            stdValue.append("[" + currentNode->key + ": " + std::to_string(currentNode->item.doubleItem) + "]");
        }
        
    }

    return stdValue;
}