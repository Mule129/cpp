#include "stack.h"

// TODO: Stack 클래스 구현 작성
Stack::Stack() {
    // LinkedList::LinkedList();
}

Stack::~Stack() {
    LinkedList::~LinkedList();
}

void Stack::push(int data) {
    LinkedList::insert(0, data);
    len++;
}

int Stack::peek() {
    return LinkedList::get(0);
}

int Stack::pop() {
    int value = Stack::peek();
    LinkedList::remove(0);
    len--;
    return value;
}