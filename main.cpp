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
    int value;
public:
    test_class(int v){
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


    std::cout << "Bella" << std::endl;
    return 0;
}