// Gabriele Canesi
// Matricola 851637

/**
 * @file sparse_matrix_exceptions.cpp
 * @author Gabriele Canesi
 * @brief File che contiene la definizione delle classi eccezione relative a SparseMatrix
 */

#include "sparse_matrix_exceptions.h"



invalid_matrix_dimension_exception::invalid_matrix_dimension_exception(const std::string &message)
: std::length_error(message) {
}

matrix_out_of_bounds_exception::matrix_out_of_bounds_exception(const std::string &message) : std::out_of_range(message) {}
