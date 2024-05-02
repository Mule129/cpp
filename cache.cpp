#include "cache.h"
#include <iostream>

// TODO: 필요한 함수 구현
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
    newNode->item.intItem = value;  // TODO: change item struct 

    len++;

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        return;
    }

    // delete tail node
    if (len >= CACHE_SIZE) {
        Node* curruntNode = tail;
        tail = tail->above;
        delete curruntNode;
    }

    // add node;
    head->above = newNode;
    newNode->next = head;
    head = newNode;
}

void Cache::add(std::string key, double value) {
    Node *newNode = new Node();
    newNode->key = key;
    newNode->item.doubleItem = value;  // TODO: change item struct
    
    len++;

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        return;
    }

    // delete tail node
    if (len >= CACHE_SIZE) {
        Node* curruntNode = tail;
        tail = tail->above;
        delete curruntNode;
    }

    // add node;
    head->above = newNode;
    newNode->next = head;
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
    while (currentNode->next != nullptr) {
        if (key == currentNode->key) {
            value = currentNode->item.doubleItem;
            std::cout << value;

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
        return "";
    }

    std::string stdValue = "";

    Node* currentNode = head;
    while (currentNode->next != nullptr) {
        if (currentNode->item.doubleItem == -1) {
            stdValue.append("[" + currentNode->key + ": " + std::to_string(currentNode->item.intItem) + "]");
        } else {
            stdValue.append("[" + currentNode->key + ": " + std::to_string(currentNode->item.doubleItem) + "]");
        }

        currentNode = currentNode->next;
        
    }

    if (currentNode->item.doubleItem == -1) {
        stdValue.append("[" + currentNode->key + ": " + std::to_string(currentNode->item.intItem) + "]");
    } else {
        stdValue.append("[" + currentNode->key + ": " + std::to_string(currentNode->item.doubleItem) + "]");
    }

    return stdValue.append("\n");
}