#include "Col_Major_order_Matrix.hpp"

Col_Major_Order_Matrix::Col_Major_Order_Matrix(Row_Major_Order_Matrix* other) {
	rows = other->get_rows();
	cols = other->get_cols();
	data = other->steal_data();
	transpose();
}

		
Col_Major_Order_Matrix::~Col_Major_Order_Matrix() { if(data) delete data; }
int Col_Major_Order_Matrix::get_rows() const { return rows; }
int Col_Major_Order_Matrix::get_cols() const { return cols; }
int Col_Major_Order_Matrix::get(int row, int col) const { return data[ row + (col*rows) ]; }
void Col_Major_Order_Matrix::set(int row, int col, int val) { data[ row + (col*rows) ] = val; }
		
void Col_Major_Order_Matrix::transpose() {
	assert( get_rows()==get_cols() );
	for (int row=0 ; row<get_rows() ; row++) {
		for (int col=(row+1) ; col<get_cols() ; col++) {
			int temp = get(row,col);
			set(row,col,get(col,row));
			set(col,row, temp);
		}
	}
}
		
int* Col_Major_Order_Matrix::steal_data() {
	int* res = data;
	data = nullptr;
	
	rows = -1;
	cols = -1;
	return res;
}
