#include "cached_runner.h"

#include "task_runner.h"

#include <iostream>

// TODO: 필요한 함수 구현
CachedRunner::CachedRunner(Cache &cache) {
    hit = 0;
    miss = 0;
    caches = &cache;
}

double CachedRunner::multiply(std::string filename) {
    double value = TaskRunner::multiply(filename);
    if (caches->get(filename, value)) {
        hit++;
    } else {
        caches->add(filename, value);
        miss++;
    }
    return value;
}

int CachedRunner::palindrome(std::string filename) {
    int value = TaskRunner::palindrome(filename);
    if (caches->get(filename, value)) {
        hit++;
    } else {
        caches->add(filename, value);
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