
#ifndef INVALID_MATRIX_DIMENSION_H
#define INVALID_MATRIX_DIMENSION_H

#include <stdexcept>

class invalid_matrix_dimension : public std::out_of_range {
public:
    explicit invalid_matrix_dimension(const std::string& message);
};


#endif // INVALID_MATRIX_DIMENSION_H
