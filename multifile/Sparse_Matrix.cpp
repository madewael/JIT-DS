#include "Sparse_Matrix.hpp"

Sparse_Matrix::~Sparse_Matrix(){ }
int Sparse_Matrix::get_rows() const { return rows; }
int Sparse_Matrix::get_cols() const { return cols; }
int Sparse_Matrix::get(int row, int col) const {
	std::unordered_map<int, int>::const_iterator got = non_zero_elements.find ( row + (col*rows) );
	if ( got == non_zero_elements.end() ) {
		return 0;
	} else {
		return got->second;
	}
}
		
		
void Sparse_Matrix::set(int row, int col, int val) { 
	if ( val == 0 ) {
		non_zero_elements.erase( row + (col*rows) );
	} else {
		non_zero_elements[ row + (col*rows) ] = val;
	}
}