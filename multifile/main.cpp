#include <cassert>
#include <iostream>

#include "Matrix_Interface.hpp"
#include "Matrix.hpp"
#include "Col_Major_Order_Matrix.hpp"
#include "Row_Major_Order_Matrix.hpp"
#include "Sparse_Matrix.hpp"

#include "Matrix_Utils.hpp"

#define N 4

#define ERROR_MATRIX_MUL_SIZES -1
int mul_matrix(Matrix& a, Matrix& b, Matrix& c) {
	assert( a.get_rows() == c.get_rows() );
	assert( b.get_cols() == c.get_cols() );
	assert( a.get_cols() == b.get_rows() );
	
	a.swap(Row_Major_Order);
	b.swap(Col_Major_Order);
	c.swap(Row_Major_Order);
	
	for (int i=0 ; i<c.get_rows() ; i++) {
		for (int j=0 ; j<c.get_cols() ; j++) {
			c.set(i,j,0);
			for (int k=0 ; k<a.get_cols() ; k++) {
				c.set(i,j, c.get(i,j) + (a.get(i,k) * b.get(k,j)) );
			}
		}
	}
	return 1;
}

bool test_swaps(){
	MatrixImplementation implementations[] = { Row_Major_Order, Col_Major_Order , Sparse };
	for (int f=0 ; f<3 ; f++) {
		MatrixImplementation from = implementations[f];
		for (int t=0 ; t<3 ; t++) {
			MatrixImplementation to = implementations[t];
			Matrix a (N,N);
			a.swap( from );
			make_row_major_indexed(a);
			a.swap( to );
			if( !is_row_major_indexed(a) ) return false;
		}
	}
	return true;
}


double computation(Matrix& a, Matrix& b, Matrix& c) {
	clock_t start, end;
	double t;
	
	start = clock();
	
	make_unit(a);
	make_unit(b);
	mul_matrix(a,b,c);
	
	end = clock();
	
	t = (double) (end-start) / CLOCKS_PER_SEC * 1000.0;
	return t;
}


int main(){
	printf("Test Swaps: %s\n", test_swaps()?"succes":"failiure");
	return 0;
}