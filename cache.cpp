#include "cache.h"
#include <iostream>
#include <sstream>
#include <string>


// cache 생성자. cache의 head, tail, hash를 초기화 한다.
Cache::Cache() {  
    head = nullptr;
    tail = nullptr;
    len = 0;
    hash = new Hash;
}

// cache 소멸자. cache의 head, tail이 가리키는 주소값을 모두 해제하고, hash또한 해제해야 한다.
Cache::~Cache() {
    
}

// cache에 값을 add 하는 함수.
// 새로운 값이 들어올 경우 hash에 값을 추가해야한다
void Cache::add(std::string key, int value) {
    Node *newNode = new Node();
    newNode->key = key;
    newNode->item.intItem = value;  // new Node에 값 대입

    if (head == nullptr) {  // head가 null이라면
        head = newNode;  // head와 tail을 new Node로 초기화
        tail = newNode;

        // add hash database
        hash->add(newNode);
        return;
    }

    // delete tail node
    if (len >= CACHE_SIZE) {
        Node* curruntNode = tail;
        tail->item.doubleItem = 111;
        
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
    

    if (head == nullptr) {
        head = newNode;
        tail = newNode;

        // add hash database
        hash->add(newNode);
        return;
    }

    // delete tail node
    if (len >= CACHE_SIZE) {
        Node** curruntNode = &tail;
        
        // remove hash databases
        hash->remove((*curruntNode)->key);
        
        tail = tail->above;
        tail->item.doubleItem = 111;
        tail->next = nullptr;
        delete *curruntNode;
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

    Node* currentNode;
    Node* headNode = head;

    currentNode = hash->get(key);
    if (currentNode == nullptr) {
        return false;
    }

    while (headNode != nullptr) {
        if (currentNode->key == headNode->key) {
            // update head
            value = headNode->item.intItem;
            if (headNode == head) {
                ;
            } else if (headNode == tail) {
                Node* currentNode2 = tail;
                tail = tail->above;
                tail->next = nullptr;

                // add head
                head->above = currentNode2;
                currentNode2->next = head;
                head = currentNode2;
                currentNode2->above = nullptr;
            } else {
                headNode->next->above = headNode->above;
                headNode->above->next = headNode->next;

                headNode->next = head;
                head->above = headNode;
                head = headNode;
                head->above = nullptr;
            }

            break;
        }
        headNode = headNode->next;
    }

    value = currentNode->item.intItem;

    return true;
}

bool Cache::get(std::string key, double &value) {
    if (head == nullptr) {
        return false;
    }

    Node* currentNode;
    Node* headNode = head;

    currentNode = hash->get(key);
    if (currentNode == nullptr) {
        return false;
    }

    while (headNode != nullptr) {
        if (currentNode->key == headNode->key) {
            // update head
            value = headNode->item.intItem;
            if (headNode == head) {
                ;
            } else if (headNode == tail) {
                Node* currentNode2 = tail;
                tail = tail->above;
                tail->next = nullptr;

                // add head
                head->above = currentNode2;
                currentNode2->next = head;
                head = currentNode2;
                currentNode2->above = nullptr;
            } else {
                headNode->next->above = headNode->above;
                headNode->above->next = headNode->next;

                headNode->next = head;
                head->above = headNode;
                head = headNode;
                head->above = nullptr;
            }

            break;
        }
    }

    value = headNode->item.doubleItem;

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
            ss << "[palindrome(" << currentNode->key <<"): " << currentNode->item.intItem <<"]";
        } else {
            ss << "[multiply(" << currentNode->key <<"): " << currentNode->item.doubleItem <<"]";
        }
        ss << " -> ";

        currentNode = currentNode->next;
        
    }

    if (currentNode->item.doubleItem == -1) {
        ss << "[palindrome(" << currentNode->key <<"): " << currentNode->item.intItem <<"]";
    } else {
        ss << "[multiply(" << currentNode->key <<"): " << currentNode->item.doubleItem <<"]";
    }

    ss << "\n";

    return ss.str();
}

// hash

Hash::Hash() {
    int cnt = 0;
    while (cnt < HASH_SIZE) {
       arr[cnt++] = nullptr; 
    } 
}

void Hash::add(Node* node) {
    // get hash key
    int hashKey = hash(node->key);

    if (get(node->key) == nullptr) {  // check node duplicate
        // create new hash node
        HashNode* newHashNode = new HashNode;
        newHashNode->above = nullptr;
        newHashNode->next = nullptr;

        // input item value
        newHashNode->item = node;
        // node check

        HashNode** head = &arr[hashKey];
        if ((*head) == nullptr) {
            *head = newHashNode;
            return;
        }

        newHashNode->next = *head;
        (*head)->above = newHashNode;
        *head = newHashNode;
    }
}

void Hash::remove(std::string key) {
    // get hash key
    int hashKey = hash(key);

    Node* currentNode = get(key);
    if (currentNode != nullptr) {  // check node duplicate

        HashNode** head = &arr[hashKey];
        while (head != nullptr) {
            if ((*head)->item->key == key) {  // if Node key equal paramiter key
                if ((*head)->next == nullptr && (*head)->above == nullptr) {
                } else if ((*head)->next == nullptr) {
                    (*head)->above->next = nullptr;
                    (*head)->item->item.doubleItem = 111;
                } else if ((*head)->above == nullptr) {
                    (*head)->next->above = nullptr;
                } else {
                    (*head)->above->next = (*head)->next;
                    (*head)->next->above = (*head)->above;
                }
                
                delete *head;
                return;
            }

            *head = (*head)->next;
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
    return sum % HASH_SIZE;
}