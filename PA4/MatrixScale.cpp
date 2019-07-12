#include "MatrixScale.h"

MatrixScale::MatrixScale(double x, double y, double z){
	//Set diagnols.
	matrix.at(0).at(0) = x;
	matrix.at(1).at(1) = y;
	matrix.at(2).at(2) = z;
	matrix.at(3).at(3) = 1;
}
