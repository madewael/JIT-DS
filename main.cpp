#include <cassert>
#include <iostream>
#include <unordered_map>

#define N     4
#define DEDICATED_ALLOWED true

class IMatrix {
	public:
		virtual ~IMatrix() {};
		virtual int get_rows() const    = 0;
		virtual int get_cols() const    = 0;
		virtual int get(int, int) const = 0;
		virtual void set(int, int, int) = 0;
};

class Sparse_Matrix : public IMatrix {
	private:
		int rows, cols;
		std::unordered_map<int, int> non_zero_elements;
		
	public:
		Sparse_Matrix(int rows, int cols)
		: rows(rows)
		, cols(cols) {
	}
	
	virtual ~Sparse_Matrix(){ }
	virtual int get_rows() const { return rows; }
	virtual int get_cols() const { return cols; }
	virtual int get(int row, int col) const {
		std::unordered_map<int, int>::const_iterator got = non_zero_elements.find ( row + (col*rows) );
		if ( got == non_zero_elements.end() ) {
			return 0;
		} else {
			return got->second;
		}
	}
		
		
	virtual void set(int row, int col, int val) { 
		if ( val == 0 ) {
			non_zero_elements.erase( row + (col*rows) );
		} else {
			non_zero_elements[ row + (col*rows) ] = val;
		}
	}
	
};

class Col_Major_Order_Matrix;

class Row_Major_Order_Matrix : public IMatrix {
	private:
		int rows, cols;
		int* data;
		
		friend class Col_Major_Order_Matrix;
		
	public:
		Row_Major_Order_Matrix(int rows, int cols)
		: rows(rows)
		, cols(cols)
		, data(new int[rows*cols]) {
			assert(data);
		}
		
		explicit Row_Major_Order_Matrix(Col_Major_Order_Matrix* other);
		
		virtual ~Row_Major_Order_Matrix(){ if(data) delete data; }
		virtual int get_rows() const { return rows; }
		virtual int get_cols() const { return cols; }
		virtual int get(int row, int col) const { return data[ (row*cols) + col ]; }
		virtual void set(int row, int col, int val) { data[ (row*cols) + col ] = val; }
		
		void transpose() {
			assert( get_rows()==get_cols() );
			for (int row=0 ; row<get_rows() ; row++) {
				for (int col=(row+1) ; col<get_cols() ; col++) {
					int temp = get(row,col);
					set(row,col,get(col,row));
					set(col,row, temp);
				}
			}
		}
		
		void invalidate() {
			rows = -1;
			cols = -1;
			data = nullptr;
		}
};

class Col_Major_Order_Matrix : public IMatrix {
	private:
		int rows, cols;
		int* data;
		
		friend class Row_Major_Order_Matrix;
		
	public:
		Col_Major_Order_Matrix(int rows, int cols)
		: rows(rows)
		, cols(cols)
		, data(new int[rows*cols]) {
			assert(data);
		}
		
		explicit Col_Major_Order_Matrix(Row_Major_Order_Matrix* other) {
			rows = other->get_rows();
			cols = other->get_cols();
			data = other->data;
			other->invalidate();
			transpose();
		}
		
		virtual ~Col_Major_Order_Matrix() { if(data) delete data; }
		virtual int get_rows() const { return rows; }
		virtual int get_cols() const { return cols; }
		virtual int get(int row, int col) const { return data[ row + (col*rows) ]; }
		virtual void set(int row, int col, int val) { data[ row + (col*rows) ] = val; }
		
		void transpose() {
			assert( get_rows()==get_cols() );
			for (int row=0 ; row<get_rows() ; row++) {
				for (int col=(row+1) ; col<get_cols() ; col++) {
					int temp = get(row,col);
					set(row,col,get(col,row));
					set(col,row, temp);
				}
			}
		}
		
		void invalidate() {
			rows = -1;
			cols = -1;
			data = nullptr;
		}
		
};

Row_Major_Order_Matrix::Row_Major_Order_Matrix(Col_Major_Order_Matrix* other) {
	rows = other->get_rows();
	cols = other->get_cols();
	data = other->data;
	other->invalidate();
	transpose();
}

enum MatrixImplementation { Row_Major_Order, Col_Major_Order , Sparse };

class Matrix : public IMatrix {
	private:
		MatrixImplementation implementation;
		IMatrix* instance;
	public:
		Matrix(int rs, int cs) {
			instance = new Row_Major_Order_Matrix(rs, cs);
			implementation = Row_Major_Order;
		}
		virtual ~Matrix() { delete instance; }
		virtual int get_rows() const { return instance->get_rows(); }
		virtual int get_cols() const { return instance->get_cols(); }
		virtual int get(int row, int col) const { return instance->get(row, col); }
		virtual void set(int row, int col, int val)  { return instance->set(row, col , val); }
		
		bool is(MatrixImplementation impl) { return (impl == implementation); }
		
		void swap( MatrixImplementation new_implementation ){
			if ( is( new_implementation ) ) /* Do Nothing */ return;
			
			IMatrix* old_instance = instance;
			
			if ( is(Row_Major_Order) && ( new_implementation == Col_Major_Order ) && DEDICATED_ALLOWED  ) {
				instance = new Col_Major_Order_Matrix( (Row_Major_Order_Matrix*)old_instance );
			} else if ( is(Col_Major_Order) && ( new_implementation == Row_Major_Order) && DEDICATED_ALLOWED ) {
				instance = new Col_Major_Order_Matrix( (Row_Major_Order_Matrix*)old_instance );
			} else {
				switch ( new_implementation ) {
					case Row_Major_Order: instance = new Row_Major_Order_Matrix( old_instance->get_rows() , old_instance->get_cols() ); break;
					case Col_Major_Order: instance = new Col_Major_Order_Matrix( old_instance->get_rows() , old_instance->get_cols() ); break;
					case Sparse         : /* TODO */ break;
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
};

#define ERROR_NON_SQUARE -1
int make_unit(Matrix& m) {
	if ( m.get_rows() != m.get_cols() ) return ERROR_NON_SQUARE;
	
	for (int i=0 ; i<m.get_rows() ; i++) {
		m.set(i,i,1);
	}
	return 1;
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
	Matrix a (N,N);
	/*
	Matrix b (N,N);
	Matrix c (N,N);
	
	make_unit(a);
	make_unit(b);
	
	
	mul_matrix(a,b,c);
	print_matrix(c);
	*/
	
	a.swap(Sparse);
	print_matrix(a);

	return 0;
}