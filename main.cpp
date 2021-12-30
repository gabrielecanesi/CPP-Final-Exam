/**
 * @file main.cpp
 * @author Gabriele Canesi
 * @brief File che contiene il main, i test e un funtore di prova.
 */


/**
 * @mainpage
 * Questo progetto è volto ad implementare una matrice sparsa contenente valori di tipi
 * generici, utilizzando il minimo quantitativo di
 * memoria possibile.
 */
#include <iostream>
#include <cassert>
#include "SparseMatrix.h"
#include "test_class.h"
#include "sparse_matrix_exceptions.h"

/**
 * @brief Funtore di prova che controlla se un oggetto di tipo test_class è pari
 */
struct pari{
    bool operator()(test_class n){
        return n.value % 2 == 0;
    }
};

/**
 * @brief Test che controlla il lancio dell'eccezione in caso di dimensione negativa in input
 */
void test_dimensione_negativa(){
    std::cout << "Test dimensione negativa: ";
    bool passed = false;
    SparseMatrix<test_class>::size_type dim = -1;
    test_class default_value(-1);
    try{
        SparseMatrix<test_class> matrice(dim, -1, default_value);
    }
    catch(invalid_matrix_dimension_exception& e){
        std::cout << std::endl << "Eccezione lanciata: " << e.what() << std::endl;
        passed = true;
    }
    assert(passed);
    std::cout << "passato " << std::endl;
}


/**
 * @brief Test che controlla la correttezza del getter del numero di elementi inseriti
 */
void test_get_elementi_inseriti(){
    std::cout << "Test numero elementi inseriti: ";
    test_class default_value(-1);
    SparseMatrix<test_class> matrice(10, 10, default_value);
    matrice.set(3, 4, test_class(5));
    matrice.set(4, 5, test_class(2));
    matrice.set(3, 4, test_class(3));

    assert(matrice.inserted_items() == 2);
    std::cout << "passato" << std::endl;
}


/**
 * @brief Test che controlla la correttezza della funzione evaluate.
 */
void test_evaluate(){
    std::cout << "Test evaluate: ";
    test_class default_value(-1);
    SparseMatrix<test_class> matrice(10, 10, default_value);
    matrice.set(0, 0, test_class(10));
    matrice.set(3, 4, test_class(11));
    matrice.set(2, 1, test_class(12));

    assert(evaluate(matrice, pari()) == 2);
    std::cout << "passato" << std::endl;
}

/**
 * @brief Test che controlla il corretto lancio dell'eccezione nel caso in cui
 * si dovesse accedere a una cella fuori dalle dimensioni
 */
void test_bounds(){
    std::cout << "Test out of bounds: ";
    bool passed = false;
    test_class default_value(-1);
    SparseMatrix<test_class> matrice(10, 10, default_value);
    try{
        matrice.set(100, 9, test_class(3));
    } catch (matrix_out_of_bounds_exception& e){
        std::cout << std::endl << "Eccezione lanciata: " << e.what() << std::endl;
        passed = true;
    }

    assert(passed);
    std::cout << "passato" << std::endl;
}


/**
 * @brief Test del costruttore di copia
 */
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

/**
 * @brief Test dell'operatore di assegnamento
 */
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

void test_const(const SparseMatrix<test_class>& matrice){
    std::cout << "Test metodi const: ";
    matrice.begin();
    matrice.end();
    matrice.rows();
    matrice.cols();
    matrice(0, 0);
    matrice.inserted_items();
    std::cout << "passato" << std::endl;
}

/**
 * @brief Test che controlla il corretto lancio dell'eccezione nel caso si
 * superasse la dimensione totale massima consentita
 */
void test_dimensione_massima(){
    std::cout <<  "Test dimensione massima:" << std::endl;
    bool passed = false;
    SparseMatrix<test_class>::size_type limit = std::numeric_limits<SparseMatrix<test_class>::size_type>::max();
    SparseMatrix<test_class>::size_type v1 = limit / 100;
    SparseMatrix<test_class> matrice(limit / v1, v1, test_class(-1));
    try{
        SparseMatrix<test_class> matrice_troppo_grossa(limit / v1, v1 + 1, test_class(-1));
    } catch (invalid_matrix_dimension_exception &e) {
        std::cout << "Eccezione lanciata: " << e.what() << std::endl;
        passed = true;
    }

    assert(passed);
    std::cout << "passato" << std::endl;
}


void test_default(){
    std::cout << "Test costruttore di default: ";
    SparseMatrix<test_class> matrice;
    assert(matrice.inserted_items() == 0);
    assert(matrice.rows() == 0);
    assert(matrice.cols() == 0);
    std::cout << "passato" << std::endl;
}


int main(int argc, char* argv[]) {
    test_default();
    test_copia();
    test_assegnamento();
    test_evaluate();
    test_bounds();
    test_dimensione_negativa();
    test_get_elementi_inseriti();
    test_dimensione_massima();
    test_const(SparseMatrix<test_class>(1, 1, test_class(-1)));
    return 0;
}