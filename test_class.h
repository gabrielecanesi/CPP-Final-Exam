// Gabriele Canesi
// Matricola 851637

/**
 * @file test_class.h
 * @author Gabriele Canesi
 * @brief File che contiene la dichiarazione della classe di test utilizzata nel main
 */


#ifndef TEST_CLASS_H
#define TEST_CLASS_H

#include <iostream>

/**
 * @brief classe di test
 *
 * Classe di test utilizzata per verificare la correttezza di SparseMatrix.
 */
class test_class {
    int *ptr;
public:
    test_class();
    test_class(const test_class &other);
    ~test_class();
    test_class& operator=(const test_class &other);
    explicit test_class(int value);
    int value() const;
};

//Operatore utile per debug
std::ostream& operator<<(std::ostream& stream, const test_class &test_instance);

#endif
