
#include "matrix_bounds_exception.h"

matrix_bounds_exception::matrix_bounds_exception(const std::string &message) : std::out_of_range(message) {}
