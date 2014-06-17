#ifndef _MatrixImplementation_H
#define _MatrixImplementation_H

#include "Matrix_Interface.hpp"

#include "Row_Major_Order_Matrix.hpp"
#include "Col_Major_Order_Matrix.hpp"
#include "Sparse_Matrix.hpp"


enum MatrixImplementation    { Row_Major_Order, Col_Major_Order , Sparse };


class Matrix : public IMatrix {
	private:
		MatrixImplementation implementation;
		IMatrix* instance;
	public:
		Matrix(int rs, int cs) {
			instance = new Row_Major_Order_Matrix(rs, cs);
			implementation = Row_Major_Order;
		}
		virtual ~Matrix();
		virtual int get_rows() const;
		virtual int get_cols() const;
		virtual int get(int row, int col) const;
		virtual void set(int row, int col, int val);
		
		bool is(MatrixImplementation impl);
		void swap( MatrixImplementation new_implementation );
};

#endif