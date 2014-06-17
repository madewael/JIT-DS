#ifndef _Sparse_H
#define _Sparse_H

#include "Matrix_Interface.hpp"
#include <unordered_map>

class Sparse_Matrix : public IMatrix {
	private:
		int rows, cols;
		std::unordered_map<int, int> non_zero_elements;
		
	public:
		Sparse_Matrix(int rows, int cols)
		: rows(rows)
		, cols(cols) {
	}
	
	virtual ~Sparse_Matrix();
	virtual int get_rows() const;
	virtual int get_cols() const;
	virtual int get(int row, int col) const;
	virtual void set(int row, int col, int val);
	
};

#endif