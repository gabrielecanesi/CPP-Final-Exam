/**
 * @file matrix_bounds_exception.cpp
 * @author Gabriele Canesi
 * @brief Contiene la definizione della classe eccezione matrix_bounds_exception
 */

#include "matrix_bounds_exception.h"


matrix_bounds_exception::matrix_bounds_exception(const std::string &message) : std::out_of_range(message) {}
