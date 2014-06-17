#include <cassert>
#include <iostream>

#include "Matrix.hpp"


#define ERROR_NON_SQUARE -1
int make_unit(Matrix& m) {
	if ( m.get_rows() != m.get_cols() ) return ERROR_NON_SQUARE;
	
	for (int i=0 ; i<m.get_rows() ; i++) {
		m.set(i,i,1);
	}
	return 1;
}

int make_row_major_indexed(Matrix& m) {
	int i = 0;
	for (int r=0 ; r<m.get_rows() ; r++) {
		for (int c=0 ; c<m.get_cols() ; c++) {
			m.set(r,c,i++);
		}
	}
	return 1;
}

bool is_row_major_indexed(Matrix& m) {
	int expected = 0;
	for (int r=0 ; r<m.get_rows() ; r++) {
		for (int c=0 ; c<m.get_cols() ; c++) {
			int i =  m.get(r,c);
			if ( i != expected ) return false;
			expected++;
		}
	}
	return true;
}

void print_matrix(Matrix& m) {
	int rows = m.get_rows();
	int cols = m.get_cols();
	
	//std::cout << rows << "\t" << cols << "\n";
	
	for (int row=0 ; row<rows ; row++) {
		for (int col=0 ; col<cols ; col++) {
			std::cout << m.get(row,col) << " ";
		}
		std::cout << "\n";
	}
	
}