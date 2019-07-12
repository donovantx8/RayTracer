#ifndef MatrixRotate_H
#define MatrixRotate_H
#include "Matrix.h"

//class MatrixRotate

class MatrixRotate: public Matrix {
	public:
		MatrixRotate(double x, double y, double z, double theta);

		std::vector< std::vector< double > > matrixRw;
		std::vector< std::vector< double > > matrixRt;
		std::vector< std::vector< double > > matrixRwT;


};	

#endif // MatrixRotate_H
