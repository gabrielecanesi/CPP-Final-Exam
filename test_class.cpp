// Gabriele Canesi
// Matricola 851637

/**
 * @file test_class.cpp
 * @author Gabriele Canesi
 * @brief File che contiene l'implementazione della classe di test utilizzata nel main
 */

#include <algorithm>
#include "test_class.h"


test_class::test_class() : ptr(new int(0)) {}

test_class::test_class(const test_class &other) {
    if(other.ptr != nullptr) {
        ptr = new int(other.value());
    }
}

test_class::~test_class() {
    delete ptr;
    ptr = nullptr;
}

test_class &test_class::operator=(const test_class &other) {
    if(this != &other){
        test_class temp = other;
        std::swap(ptr, temp.ptr);
    }
    return *this;
}

test_class::test_class(int value) {
    this->ptr = new int(value);
}

int test_class::value() const {
    if(ptr == nullptr){
        return -1;
    }
    return *ptr;
}


std::ostream& operator<<(std::ostream& stream, const test_class &test_instance){
    stream << test_instance.value();
    return stream;
}
