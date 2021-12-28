#include <iostream>
#include <vector>
#include "SparseMatrix.h"

int main(int argc, char* argv[]) {

    std::cout << "Ciao" << std::endl;

    SparseMatrix<std::vector<int> > m;
    SparseMatrix<std::vector<int> > mm = m;

    SparseMatrix<int> matrice(20, 20, -1);

    matrice.set(1, 1, 34);
    std::cout << matrice(2, 2) << std::endl;
    std::cout << matrice(1, 1) << std::endl;

    SparseMatrix<int>::const_iterator it = matrice.begin();
    SparseMatrix<int>::const_iterator end = matrice.end();

    while(it != matrice.end()){
        std::cout << it->data << std::endl;
        std::cout << (*it).data << std::endl;
        std::cout << it->m_i << ", " <<  it->m_j << std::endl;
        ++it;
    }
    std::cout << "Bella" << std::endl;
    return 0;
}