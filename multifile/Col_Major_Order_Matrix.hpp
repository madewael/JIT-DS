#ifndef _CMO_H
#define _CMO_H

#include <cassert>
#include <iostream>

#include "Matrix_Interface.hpp"

class Col_Major_Order_Matrix;
#include "Row_Major_order_Matrix.hpp"

class Col_Major_Order_Matrix : public IMatrix {
	private:
		int rows, cols;
		int* data;
		
	public:
		Col_Major_Order_Matrix(int rows, int cols)
		: rows(rows)
		, cols(cols)
		, data(new int[rows*cols]) {
			assert(data);
		}
		
		explicit Col_Major_Order_Matrix(Row_Major_Order_Matrix* other);
		
		virtual ~Col_Major_Order_Matrix();
		virtual int get_rows() const;
		virtual int get_cols() const;
		virtual int get(int row, int col) const;
		virtual void set(int row, int col, int val);
		
		void transpose();
		
		int* steal_data();
		
};

#endif