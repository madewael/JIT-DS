#include "Matrix.hpp"

Matrix::~Matrix() { delete instance; }
int Matrix::get_rows() const { return instance->get_rows(); }
int Matrix::get_cols() const { return instance->get_cols(); }
int Matrix::get(int row, int col) const { return instance->get(row, col); }
void Matrix::set(int row, int col, int val)  { return instance->set(row, col , val); }


bool Matrix::is(MatrixImplementation impl) { return (impl == implementation); }

void Matrix::swap( MatrixImplementation new_implementation ){
	if ( is( new_implementation ) ) /* Do Nothing */ return;
	
	IMatrix* old_instance = instance;
	
	if ( is(Row_Major_Order) && ( new_implementation == Col_Major_Order ) ) {
		instance = new Col_Major_Order_Matrix( (Row_Major_Order_Matrix*)old_instance );
	} else if ( is(Col_Major_Order) && ( new_implementation == Row_Major_Order) ) {
		instance = new Row_Major_Order_Matrix( (Col_Major_Order_Matrix*)old_instance );
	} else {
		switch ( new_implementation ) {
			case Row_Major_Order: instance = new Row_Major_Order_Matrix( old_instance->get_rows() , old_instance->get_cols() ); break;
			case Col_Major_Order: instance = new Col_Major_Order_Matrix( old_instance->get_rows() , old_instance->get_cols() ); break;
			case Sparse         : instance = new Sparse_Matrix( old_instance->get_rows() , old_instance->get_cols() ); break;
		}
		for (int i=0 ; i<old_instance->get_rows() ; i++) {
			for (int j=0 ; j<old_instance->get_cols() ; j++) {
				instance->set(i,j, old_instance->get(i,j) );
			}
		}
	}
	
	implementation = new_implementation;
	delete old_instance;
}
