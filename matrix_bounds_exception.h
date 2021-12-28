#include <stdexcept>

#ifndef OUT_OF_BOUNDS_MATRIX_H
#define OUT_OF_BOUNDS_MATRIX_H


class matrix_bounds_exception : public std::out_of_range {
public:
    explicit matrix_bounds_exception(const std::string& message);
};


#endif // OUT_OF_BOUNDS_MATRIX_H
