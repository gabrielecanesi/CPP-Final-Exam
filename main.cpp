// Gabriele Canesi
// Matricola 851637

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
 * @brief Funtore per test_class
 *
 * Questo funtore ritorna true se il il metodo value() di un oggetto test_class ritorna un valore pari, false altrimenti.
 */
struct pari{
    bool operator()(const test_class &n) const {
        return n.value() % 2 == 0;
    }
};

/**
 * @brief Funtore per std::string
 *
 * Questo funtore ritorna true se la lunghezza della stringa passata come argomento è pari, false altrimenti.
 */

struct stringhe_pari{
    bool operator()(const std::string &str) const {
        return str.length() % 2 == 0;
    }
};


typedef SparseMatrix<test_class>  mat_test;



/**
 * @brief Test che controlla il lancio dell'eccezione in caso di dimensione negativa in input
 *
 * Controlla la cattura di un'eccezione di tipo invalid_matrix_exception nel caso in cui venga passata al costruttore
 * una dimensione negativa
 */
void test_dimensione_negativa(){
    std::cout << "Test dimensione negativa: ";
    bool passed = false;
    mat_test::size_type dim = -1;
    test_class default_value(-1);
    try{
        mat_test matrice(dim, -1, default_value);
    }
    catch(invalid_matrix_dimension_exception& e){
        std::cout << std::endl << "invalid_matrix_dimension_exception lanciata correttamente: " << e.what() << std::endl;
        passed = true;
    }
    assert(passed);
    std::cout << "passato " << std::endl;
}


/**
 * @brief Test che controlla la correttezza del getter del numero di elementi inseriti
 *
 * Verifica che il numero di elementi inseriti corrisponda con quelli effettivamente presenti nella matrice.
 */
void test_get_elementi_inseriti(){
    std::cout << "Test numero elementi inseriti: ";
    test_class default_value(-1);
    mat_test matrice(10, 10, default_value);
    matrice.set(3, 4, test_class(5));
    matrice.set(4, 5, test_class(2));
    matrice.set(3, 4, test_class(3));
    std::cout << matrice << std::endl;
    assert(matrice.inserted_items() == 2);
    std::cout << "passato" << std::endl;
}


/**
 * @brief Test che controlla la correttezza della funzione evaluate.
 *
 * Controlle se evaluate si comporta correttamente testanto un predicato su test_class e uno su stringhe.
 */
void test_evaluate(){
    std::cout << "Test evaluate: ";
    test_class default_value(0);
    mat_test matrice(10, 10, default_value);
    matrice.set(0, 0, test_class(10));
    matrice.set(3, 4, test_class(11));
    matrice.set(2, 1, test_class(12));

    // Prova con le stringhe
    SparseMatrix<std::string> mat_stringhe(10, 10, "Ciao");
    mat_stringhe.set(1, 0, "Dispari");
    assert(evaluate(mat_stringhe, stringhe_pari()) == 99);

    assert(evaluate(matrice, pari()) == 2 + (matrice.rows() * matrice.columns() - matrice.inserted_items()));
    std::cout << "passato" << std::endl;
}

/**
 * @brief Test che controlla la gestione dei limiti di righe/colonne nell'inserimento
 *
 * Verifica che venga lanciata correttamente un'eccezione di tipo matrix_out_of_bounds_exception
 * quando si specifica una riga o una colonna che non appartiene alla matrice logica.
 */
void test_bounds(){
    std::cout << "Test out of bounds: ";
    bool passed = false;
    test_class default_value(-1);
    mat_test matrice(10, 10, default_value);
    try{
        matrice.set(100, 9, test_class(3));
    } catch (matrix_out_of_bounds_exception& e){
        std::cout << std::endl << "matrix_out_of_bounds_exception lanciata correttamente: " << e.what() << std::endl;
        passed = true;
    }

    assert(passed);
    std::cout << "passato" << std::endl;
}


/**
 * @brief Test del costruttore di copia
 *
 * Controlla che il copy constructor di SparseMatrix non renda condivisi tra istanze i puntatori
 */
void test_copia(){
    std::cout << "Test sul costruttore di copia: ";
    test_class default_value(-1);
    mat_test m1(10, 10, test_class(-1));

    // Controllo che i dati siano separati
    m1.set(0, 0, test_class(10));

    mat_test m2 = m1;
    const test_class& v1 = m1(0, 0);
    const test_class& v2 = m2(0, 0);

    // Controllo che gli indirizzi di memoria dei valori siano diversi
    assert(&m1(0, 0) != &m2(0, 0));

    // Controllo che le dimensioni coincidano
    assert(m1.rows() == m2.rows());
    assert(m1.columns() == m2.columns());
    assert(m1.inserted_items() == m2.inserted_items());

    // Controllo che il valore di default sia stato copiato correttamente
    assert(m1.default_value().value() == m2.default_value().value());
    assert(&m1.default_value() != &m2.default_value());

    std::cout << "passato" << std::endl;
}

/**
 * @brief Test dell'operatore di assegnamento
 *
 * Controlla la correttezza dell'operatore di assegnamento, controllando che non ci siano condivisioni
 * di dati tra le istanze.
 */
void test_assegnamento(){
    std::cout << "Test di assegnamento: ";
    mat_test m1(10, 10, test_class(-1));
    mat_test m2(7, 8, test_class(-1));
    m1.set(0, 0, test_class(10));
    m2.set(0, 0, test_class(20));

    m2 = m1;
    assert(m2(0, 0).value() == m1(0, 0).value());

    // Controllo che i dati siano separati
    assert(&m1(0, 0) != &m2(0, 0));

    std::cout << "passato" << std::endl;
}



/**
 * @brief Test che controlla la gestione delle dimensioni in input alla matrice.
 *
 * Controlla che venga lanciata correttamente una eccezione di tipo invalid_matrix_dimension_exception quando
 * viene passata una dimensione troppo grande, ovvero tale da portare potenzialmente il contatore degli elementi
 * inseriti in overflow.
 */
void test_dimensione_massima(){
    std::cout <<  "Test dimensione massima:" << std::endl;
    bool passed = false;

    // Controllo che la dimensione totale non possa superare il limite superiore di size_type.
    mat_test::size_type limit = std::numeric_limits<SparseMatrix<test_class>::size_type>::max();
    mat_test::size_type v1 = limit / 100;
    mat_test matrice(limit / v1, v1, test_class(-1));
    try{
        mat_test matrice_troppo_grossa(limit / v1, v1 + 1, test_class(-1));
    } catch (invalid_matrix_dimension_exception &e) {
        std::cout << "invalid_matrix_dimension_exception lanciata correttamente: " << e.what() << std::endl;
        passed = true;
    }

    assert(passed);
    std::cout << "passato" << std::endl;
}


/**
 * @brief Test sul costruttore di default di SparseMatrix.
 *
 * Controlla che tutti i dati membro della matrice siano istanziati correttamente tramite il costruttore di default.
 */
void test_default(){
    std::cout << "Test costruttore di default: ";
    mat_test matrice;
    assert(matrice.inserted_items() == 0);
    assert(matrice.rows() == 0);
    assert(matrice.columns() == 0);
    assert(matrice.default_value().value() == test_class().value());
    std::cout << "passato" << std::endl;
}

/**
 * @Brief Test sugli iteratori
 *
 * Stampa tutti gli elementi fisicamente inseriti dall'utente
 */
void test_iteratori(){
    std::cout << "Iteratore:" << std::endl;
    mat_test matrice(10, 10, test_class(-1));
    matrice.set(0, 1, test_class(-1));
    matrice.set(1, 2, test_class(3));
    matrice.set(1, 1, test_class(5));
    matrice.set(9, 8, test_class(7));


    for(mat_test::const_iterator it = matrice.begin(), end = matrice.end(); it != end; ++it){
        std::cout << "(" << it->row() << ", " << (*it).column() << ") -> " << it->value().value() << std::endl;
    }
}

/**
 * @brief Test sui metodi di element
 *
 * Verifica che i metodi fondamentali si comportino nel modo corretto all'interno della classe element.
 */
void test_element(){
    std::cout << "Test dei metodi di element: ";
    mat_test::element el(1, 2, test_class(1));
    mat_test::element el2(3, 4, test_class(34));

    assert(&el.value() != &el2.value());
    el2 = el;
    assert(&el.value() != &el2.value());
    std::cout << " passato" << std::endl;
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
    test_iteratori();
    test_element();

    return 0;
}