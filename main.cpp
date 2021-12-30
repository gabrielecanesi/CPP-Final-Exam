#include <iostream>
#include <vector>
#include <cassert>
#include "SparseMatrix.h"
#include "test_class.h"


// Funtore di test
struct pari{
    bool operator()(int n){
        return n % 2 == 0;
    }
};

void controllo_dimensioni_negative(){
    test_class default_value(-1);
    SparseMatrix<test_class> matrice(-1, 1, default_value);

}

void test_copia(){
    std::cout << "Test sul costruttore di copia: ";

    test_class default_value(-1);
    SparseMatrix<test_class> m1(10, 10, test_class(-1));

    // Controllo che i dati siano separati
    m1.set(0, 0, test_class(10));


    SparseMatrix<test_class> m2 = m1;

    assert(m1(0, 0).value == 10);
    assert(m2(0, 0).value == 10);

    m2.set(0, 0, test_class(20));

    test_class v1 = m1(0, 0);
    test_class v2 = m2(0, 0);

    assert(v1.value == 10);
    assert(v2.value == 20);

    std::cout << "passato" << std::endl;
}

void test_assegnamento(){
    std::cout << "Test di assegnamento: ";
    SparseMatrix<test_class> m1(10, 10, test_class(-1));
    SparseMatrix<test_class> m2(m1);
    m1.set(0, 0, test_class(10));
    m2.set(0, 0, test_class(20));

    m2 = m1;
    assert(m2(0, 0).value == 10);

    // Controllo che i dati siano separati
    m2.set(0, 0, test_class(20));
    assert(m1(0, 0).value == 10);

    std::cout << "passato" << std::endl;
}


int main(int argc, char* argv[]) {
    test_copia();
    test_assegnamento();
    return 0;
}