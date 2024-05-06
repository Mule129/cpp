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
    double value;
    std::cout << "cacherunner multiply get" << std::endl;
    if (caches->get(filename, value)) {
        std::cout << "cacherunner multiply get - if true" << std::endl;
        hit++;
    } else {
        std::cout << "cacherunner multiply get - else" << std::endl;
        value = TaskRunner::multiply(filename);
        caches->add(filename, value);
        miss++;
    }
    return value;
}

int CachedRunner::palindrome(std::string filename) {
    int value;
    if (caches->get(filename, value)) {
        hit++;
    } else {
        value = TaskRunner::palindrome(filename);
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