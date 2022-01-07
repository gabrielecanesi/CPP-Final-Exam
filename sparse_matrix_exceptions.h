// Gabriele Canesi
// Matricola 851637

/**
 * @file sparse_matrix_exceptions.h
 * @author Gabriele Canesi
 * @brief File che contiene le dichiarazioni delle eccezioni relative a SparseMatrix
 */

#ifndef INVALID_MATRIX_DIMENSION_H
#define INVALID_MATRIX_DIMENSION_H

#include <stdexcept>

/**
 * @brief Eccezione lanciata quando viene specificata una dimensione non valida
 * in fase di costruzione di una SparseMatrix
 */
class invalid_matrix_dimension_exception : public std::length_error {
public:
    explicit invalid_matrix_dimension_exception(const std::string &message);
};

/**
 * @brief Eccezione lanciata quando viene richiesto l'accesso a una cella
 * della matrice logica fuori dai limiti disponibili
 */
class matrix_out_of_bounds_exception : public std::out_of_range{
public:
    explicit matrix_out_of_bounds_exception(const std::string &message);
};

#endif
