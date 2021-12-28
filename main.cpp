#include <iostream>
#include <vector>
#include "SparseMatrix.h"

int main(int argc, char* argv[]) {

    std::cout << "Ciao" << std::endl;

    SparseMatrix<std::vector<int>> m;
    SparseMatrix<std::vector<int>> mm = m;


    std::cout << "Bella" << std::endl;

    return 0;
}