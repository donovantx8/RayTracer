#include "MatrixTranslate.h"

MatrixTranslate::MatrixTranslate(double x, double y, double z){
	//Set diagnols.
	matrix.at(0).at(0) = 1;
	matrix.at(1).at(1) = 1;
	matrix.at(2).at(2) = 1;
	matrix.at(3).at(3) = 1;

	//set translation points
	matrix.at(0).at(3) = x;
	matrix.at(1).at(3) = y;
	matrix.at(2).at(3) = z;
}
