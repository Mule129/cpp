#ifndef LIST_H
#define LIST_H
#include "linked_list.h"

// TODO: List 클래스 정의 작성
class List : public LinkedList
{
private:
    Node* head_;
    int len;
public:
    List();
    ~List();

  // index 위치에 노드를 삽입한다
  void insert(int index, int value);
  // index 위치의 노드 값을 반환한다
  int get(int index);
  // index 위치의 노드를 제거하고 메모리를 반환한다.
  void remove(int index);
};


#endif