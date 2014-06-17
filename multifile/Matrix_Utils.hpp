#ifndef _Matrix_Utils_H
#define _Matrix_Utils_H

#include <cassert>
#include <iostream>

#include "Matrix.hpp"

#define ERROR_NON_SQUARE -1

int make_unit(Matrix& m);

int make_row_major_indexed(Matrix& m);
bool is_row_major_indexed(Matrix& m);

void print_matrix(Matrix& m);

#endif