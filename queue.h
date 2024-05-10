#ifndef QUEUE_H
#define QUEUE_H

#include "linked_list.h"

// TODO: Queue 클래스 정의 작성
class Queue : public LinkedList
{
private:
    int len;
public:
    Queue();
    ~Queue();

    void push(int data);
    int peek();
    int pop();
};


#endif