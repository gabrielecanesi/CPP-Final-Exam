//
// Created by gabri on 12/29/21.
//

#ifndef TEST_CLASS_H
#define TEST_CLASS_H


class test_class {
public:
    int value;
    test_class();
    test_class(const test_class& other);
    ~test_class();
    test_class& operator=(const test_class& other);
    explicit test_class(int value);
};


#endif // TEST_CLASS_H
