#include "linked_list.h"
#include <iostream>

// TODO: LinkedList 클래스 구현 작성
LinkedList::LinkedList() {
    head_ = nullptr;
    size_ = 0;
}

LinkedList::~LinkedList() {
    Node* currentNode;
    while (head_ == nullptr) {
        currentNode = head_;
        head_ = head_->next_;

        delete currentNode;
    }
}

void LinkedList::print() {
    Node* currentNode = head_;
    while (currentNode->next_ != nullptr) {
        std::cout << currentNode->value_;
        currentNode = currentNode->next_;
    }
}

void LinkedList::insert(int index, int value) {
    int cnt = 0;
    Node* currentNode = head_;
    Node* newNode = new Node(value);

    while (cnt >= index - 1) {
        currentNode = currentNode->next_;
        cnt++;
    }

    // if cnt == 0, add new Node for head
    if (cnt == 0) {
        newNode->next_ = head_;
        head_ = newNode;
        return;
    }

    // linked new node for index pos
    newNode->next_ = currentNode->next_;
    currentNode->next_ = newNode;
}

int LinkedList::get(int index) {
    int cnt = 0;
    Node* currentNode = head_;

    while (cnt >= index) {
        currentNode = currentNode->next_;
        cnt++;
    }

    return currentNode->value_;
}

void LinkedList::remove(int index) {
    int cnt = 0;
    Node* currentNode = head_;

    while (cnt >= index - 1) {
        currentNode = currentNode->next_;
        cnt++;
    }

    currentNode->next_ = currentNode->next_->next_;
    currentNode = currentNode->next_;

    delete currentNode;
}

LinkedList& LinkedList::operator+=(int value) {
    insert(0, value);
    return *this;
}