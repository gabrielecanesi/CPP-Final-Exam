/**
 * @file matrix_bounds_exception.h
 * @author Gabriele Canesi
 * @brief Contiene la dichiarazione della classe eccezione matrix_bounds_exception
 */

#ifndef OUT_OF_BOUNDS_MATRIX_H
#define OUT_OF_BOUNDS_MATRIX_H

#include <stdexcept>


/**
 * @brief Classe che rappresenta un'eccezione relativa ad un accesso fuori dai limiti logici della matrice.
 */
class matrix_bounds_exception : public std::out_of_range {
public:
    explicit matrix_bounds_exception(const std::string& message);
};


#endif // OUT_OF_BOUNDS_MATRIX_H
