#include <iostream>
#include <vector>
#include "SparseMatrix.h"


struct pari{
    bool operator()(int n){
        return n % 2 == 0;
    }
};

// Classe di prova come tipo di SparseMatrix
class test_class{
public:
    int value;
    test_class(){}
    explicit test_class(int v){
        value = v;
    }
};

int main(int argc, char* argv[]) {

    SparseMatrix<int> matrice(20, 20, -1);

    matrice.set(1, 1, 33);
    matrice.set(15, 20, 24);

    // Test sostuzione
    matrice.set(1, 1, 10);

    SparseMatrix<int>::const_iterator it = matrice.begin();
    SparseMatrix<int>::const_iterator end = matrice.end();

    while(it != matrice.end()){
        std::cout << "("  << it->m_i << ", " << it->m_j << ") -> " << it->data << std::endl;
        ++it;
    }

    std::cout << "Evaluate: " << evaluate(matrice, pari()) << std::endl;

    SparseMatrix<test_class> test_c(10, 10, test_class(-2));
    test_c.set(1, 1, test_class(150));

    // Istanziazione e test con classe custom
    SparseMatrix<test_class>::const_iterator it2 = test_c.begin();
    SparseMatrix<test_class>::const_iterator end2 = test_c.end();
    std:: cout << "Test con classe:" << std::endl;
    while(it2 != end2){
        std::cout << it2->data.value << std::endl;
        ++it2;
    }
    try {

        std::cout << test_c(3000, 3342).value << std::endl;
    }
    catch(matrix_bounds_exception& e){
        std::cout << "Eccezione: " << e.what() << std::endl;
    }

    std::cout << "Bella" << std::endl;
    return 0;
}