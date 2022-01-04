/**
 * @file test_class.h
 * @author Gabriele Canesi
 * @brief File che contiene la dichiarazione della classe di test utilizzata nel main
 */


#ifndef TEST_CLASS_H
#define TEST_CLASS_H

/**
 * @brief classe utilizzata come tipo custom nei test di SparseMatrix
 */
class test_class {
    int *ptr;
public:
    test_class();
    test_class(const test_class& other);
    ~test_class();
    test_class& operator=(const test_class& other);
    explicit test_class(int value);
    int value() const;
};


#endif // TEST_CLASS_H
