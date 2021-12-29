#include <algorithm>
#include "test_class.h"

test_class::test_class() : value(0) {}

test_class::test_class(const test_class &other) : value(other.value) {}

test_class::~test_class() {}

test_class &test_class::operator=(const test_class &other) {
    if(this != &other){
        test_class temp = other;
        std::swap(value, temp.value);
    }
    return *this;
}

test_class::test_class(int value) : value(value) {}
