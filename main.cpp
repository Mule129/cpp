#include "cached_runner.h"
#include "task.h"
#include <iostream>
#include <sstream>
#include <string>

const bool DEBUG = true;

// 디버그 용 출력 함수
void print(const std::string &message) {
  if (DEBUG) {
    std::cout << message << std::endl;
  }
}

// double 값을 문자열로 변환한다
std::string doubleToString(double value) {
  std::ostringstream ss;
  ss << value;
  return ss.str();
}

int main() {
  
  Cache cache;  // cache 선언
  CachedRunner runner(cache);  // cache 값을 넣은 runner 선언
  Task task;  // palindrome, multiply 값을 순차적으로 구하기 위한 task 선언

  TaskSet taskSet("resources/task_set.txt");  // task set read
  int index = 0;

  // 태스크를 계속 읽어 수행한다
  while (taskSet.getNext(task)) {
    print("[TASK #" + std::to_string(index++) + "]");
    switch (task.type) {  // task type 확인
    case MULTIPLY: {
      double result = runner.multiply(task.filename);  // multiply 값을 runner를 통해 읽어들임(cache, hash 상에서 추가, 위치 변경, 삭제가 이루어짐)
      print("multiply(" + task.filename + ") = " + doubleToString(result));
    } break;
    case PALINDROME: {
      int result = runner.palindrome(task.filename); // multiply 값을 runner를 통해 읽어들임(cache, hash 상에서 추가, 위치 변경, 삭제가 이루어짐)
      print("palindrome(" + task.filename + ") = " + std::to_string(result));
    } break;
    }

    print("\n[CACHE]");
    print(cache.toString());  // cache 값을 toString 을 통하여 string으로 변환
  }

  print("Hits: " + std::to_string(runner.hits()));
  print("Misses: " + std::to_string(runner.misses()));
  print("Hit ratio: " + doubleToString((double)runner.hits() /
                                       (runner.hits() + runner.misses())));
}