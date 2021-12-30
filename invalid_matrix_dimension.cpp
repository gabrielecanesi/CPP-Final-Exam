#include "invalid_matrix_dimension.h"


invalid_matrix_dimension::invalid_matrix_dimension(const std::string &message) : std::out_of_range(message) {}