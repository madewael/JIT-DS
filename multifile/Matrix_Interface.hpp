#ifndef _IMatrix_H
#define _IMatrix_H

class IMatrix {
	public:
		virtual ~IMatrix() {};
		virtual int get_rows() const    = 0;
		virtual int get_cols() const    = 0;
		virtual int get(int, int) const = 0;
		virtual void set(int, int, int) = 0;
};

#endif