#ifndef _RMO_H
#define _RMO_H

#include <cassert>
#include <iostream>

#include "Matrix_Interface.hpp"

class Row_Major_Order_Matrix;
#include "Col_Major_Order_Matrix.hpp"



class Row_Major_Order_Matrix : public IMatrix {
	private:
		int rows, cols;
		int* data;
		
	public:
		Row_Major_Order_Matrix(int rows, int cols)
		: rows(rows)
		, cols(cols)
		, data(new int[rows*cols]) {
			assert(data);
		}
		
		explicit Row_Major_Order_Matrix(Col_Major_Order_Matrix* other);
		
		virtual ~Row_Major_Order_Matrix();
		virtual int get_rows() const;
		virtual int get_cols() const;
		virtual int get(int row, int col) const;
		virtual void set(int row, int col, int val);
		
		void transpose();
		
		int* steal_data();
};

#endif