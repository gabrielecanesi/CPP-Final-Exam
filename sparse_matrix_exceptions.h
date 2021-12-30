
#ifndef INVALID_MATRIX_DIMENSION_H
#define INVALID_MATRIX_DIMENSION_H

#include <stdexcept>

class invalid_matrix_dimension_exception : public std::out_of_range {
public:
    explicit invalid_matrix_dimension_exception(const std::string& message);
};


class matrix_out_of_bounds_exception : public std::out_of_range{
public:
    explicit matrix_out_of_bounds_exception(const std::string& message);
};

#endif // INVALID_MATRIX_DIMENSION_H
