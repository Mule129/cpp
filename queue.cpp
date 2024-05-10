#include "queue.h"

// TODO: Queue 클래스 구현 작성
Queue::Queue() {
    // LinkedList::LinkedList();
}

Queue::Queue() {
    LinkedList::~LinkedList();
}

void Queue::push(int data) {
    LinkedList::insert(0, data);
    len++;
}

int Queue::peek() {
    return LinkedList::get(len);
}

int Queue::pop() {
    int data = Queue::peek();
    LinkedList::remove(len);
    len--;
    return data;
}