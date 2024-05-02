#include "cached_runner.h"

#include "task_runner.h"

#include <iostream>

// TODO: 필요한 함수 구현
CachedRunner::CachedRunner(Cache &cache) {
    hit = 0;
    miss = 0;
}

std::string hash(std::string filename) {
    char value = filename[0];
    int result = value;
    return std::to_string(result);
}

double CachedRunner::multiply(std::string filename) {
    double value = TaskRunner::multiply(filename);
    if (cache.get(filename, value)) {
        hit++;
    } else {
        cache.add(hash(filename), value);
        miss++;
    }
    return value;
}

int CachedRunner::palindrome(std::string filename) {
    int value = TaskRunner::palindrome(filename);
    if (cache.get(filename, value)) {
        hit++;
    } else {
        cache.add(hash(filename), value);
        miss++;
    }
    return value;
}

int CachedRunner::hits() {
    return hit;
}

int CachedRunner::misses() {
    return miss;
}