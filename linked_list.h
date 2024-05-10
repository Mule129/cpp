#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "node.h"

class LinkedList {
public:
  LinkedList();
  ~LinkedList();

  // head부터 순차적으로 노드를 해제한다
  void print();

  // index 위치에 노드를 삽입한다
  void insert(int index, int value);
  // index 위치의 노드 값을 반환한다
  int get(int index);
  // index 위치의 노드를 제거하고 메모리를 반환한다.
  void remove(int index);

  Node *head_;
  int size_;

  LinkedList& operator+=(int value);
};

#endif