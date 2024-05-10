# 과제 목표

LinkedList 클래스를 상속하는 List, Stack, Queue 클래스를 적절히 작성한다.

# 세부 목표

## LinkedList

LinkedList는 다음 public 함수를 제공해야 한다.

```cpp
LinkedList() // 멤버 변수를 초기화한다
~LinkedList() // 메모리를 적절히 해제한다
void print() // head 부터 순서대로 노드를 출력한다
```

또한 다음 protected 함수를 적절히 구현해야 한다.

```cpp
void insert(int index, int value) // index 위치에 노드를 삽입한다
int get(int index) // index에 위치한 노드의 값을 반환한다.
void remove(int index) // index에 위치한 노드를 제거하고 메모리 상에서 해제한다.
```

## List

List는 다음 public 함수를 새로 제공해야 한다.

```cpp
  void insert(int index, int value) // index 위치에 노드를 삽입한다
  int get(int index) // index에 위치한 노드의 값을 반환한다
  void remove(int index) // index에 위치한 노드를 제거하고 메모리 상에서 해제한다.
```

## Stack

Stack은 다음 함수를 새로 제공해야 한다.

```cpp
  void push(int data) // Stack의 정의에 맞게 데이터를 삽입한다.
  int pop() // Stack의 정의에 맞게 데이터를 꺼내고 적절한 메모리를 해제한다.
  int peek() // Stack의 정의에 맞게 다음에 pop 될 값을 미리 본다.
```

또한 push와 동일한 역할을 하는 피연산자가 int인 += 연산자를 오버로딩하여 구현해야 한다.

## Queue

Queue는 다음 함수를 새로 제공해야 한다.

```cpp
  void push(int data) // Queue의 정의에 맞게 데이터를 삽입한다.
  int pop() // Queue의 정의에 맞게 데이터를 꺼내고 적절한 메모리를 해제한다.
  int peek() // Queue의 정의에 맞게 다음에 pop 될 값을 미리 본다.
```

또한 push와 동일한 역할을 하는 피연산자가 int인 += 연산자를 오버로딩하여 구현해야 한다.

# 과제 조건

- 함수는 세부 목표에서 설명된 대로 작동해야 한다.
- 메모리가 적절히 해제 되지 않을 경우 감점된다.
- 모든 파일에서는 TODO 주석으로 설명된 곳만 수정할 수 있다. 다른 곳을 수정하는 경우 감점될 수 있다.
- 템플릿에 정의된 함수나 변수를 적절히 이용해야 한다.

## 사용 가능 헤더

- iostream
- exception

# 과제 제출 방법

공지된 것과 동일하게 추가적인 텍스트 없이 GitHub Repository URL과 최종 커밋 해시를 제출한다.
과제 제출 방법이 잘못되었거나 정해진 명령어로 빌드가 되지 않을 경우 0점 처리된다.

## 과제 제출 예시

```
https://github.com/cstria0106/data-structure
d62f003
```

## 채점 방법

제공되는 Makefile을 이용한다. 다음 명령어를 통해 채점한다.
Makefile을 수정하지 말 것.

```sh
git clone [url] data-structure
cd data-structure
make    # mingw32-make
./main  # .\main.exe
```

## 올바른 출력 예시

다음은 제공된 main.cpp에서의 올바른 출력 예시이다.
main.cpp의 시나리오가 아닌 다른 시나리오에서도 올바르게 작동해야 한다.

```
0
0 1 2 3 4 5 6 7 8 9 100 99 98 97 96 95 94 93 92 91
0
1
2
3
4
5 6 7 8 9 100 99 98 97 96 95 94 93 92 91
91
91 92 93 94 95 96 97 98 99 100 9 8 7 6 5 4 3 2 1 0
91
92
93
94
95
96 97 98 99 100 9 8 7 6 5 4 3 2 1 0
0 1 2 3 4 5 6 7 8 9
```
