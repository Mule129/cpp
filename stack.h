#ifndef STACK_H
#define STACK_H

#include "linked_list.h"

// TODO: Stack 클래스 정의 작성
class Stack : public LinkedList
{
private:
    int len;
    LinkedList stack;
public:
    Stack(/* args */);
    ~Stack();

    void push(int data);
    int peek();
    int pop();
};

#endif