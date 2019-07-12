#include "MatrixRotate.h"
#include "Model.h"
#include <math.h>
#include <algorithm>
#define PI 3.14159265


MatrixRotate::MatrixRotate (double x, double y, double z, double theta) {
    std::vector<double> rows (4,0);                     // four ints with value 0
	matrixRw.push_back(rows);								// add four rows to the matrix
    matrixRw.push_back(rows);
    matrixRw.push_back(rows);
    matrixRw.push_back(rows);
  	matrixRt.push_back(rows);								// add four rows to the matrix
    matrixRt.push_back(rows);
    matrixRt.push_back(rows);
    matrixRt.push_back(rows);
  	matrixRwT.push_back(rows);								// add four rows to the matrix
    matrixRwT.push_back(rows);
    matrixRwT.push_back(rows);
    matrixRwT.push_back(rows);
	std::vector<double> axisW (3,0); 
	axisW.at(0) = x;
	axisW.at(1) = y;
	axisW.at(2) = z;

	axisW = axisW % vectorLength(axisW);

	std::vector<double> axisM = axisW;
	axisM.push_back(1); 
	int minIndex = std::min_element(axisM.begin(), axisM.end()) - axisM.begin();
	axisM.at(minIndex) = 1;
	axisM = axisM % vectorLength(axisM);
	axisM.pop_back();
	std::vector<double> axisU (3,0); 

	axisU = axisW ^ axisM;

	std::vector<double> axisV (3,0); 

	axisV = axisW ^ axisU;

	axisV = axisV % vectorLength(axisV);
	axisU = axisU % vectorLength(axisU);
	axisW = axisW % vectorLength(axisW);


	matrixRw.at(0).at(3) = 0;
	matrixRw.at(1).at(3) = 0;
	matrixRw.at(2).at(3) = 0;
	matrixRw.at(3).at(3) = 1;

	matrixRw.at(3).at(0) = 0;
	matrixRw.at(3).at(1) = 0;
	matrixRw.at(3).at(2) = 0;


	matrixRw.at(0).at(0) = axisU.at(0);
	matrixRw.at(0).at(1) = axisU.at(1);
	matrixRw.at(0).at(2) = axisU.at(2);

	matrixRw.at(1).at(0) = axisV.at(0);
	matrixRw.at(1).at(1) = axisV.at(1);
	matrixRw.at(1).at(2) = axisV.at(2);

	matrixRw.at(2).at(0) = axisW.at(0);
	matrixRw.at(2).at(1) = axisW.at(1);
	matrixRw.at(2).at(2) = axisW.at(2);

	//===================================

	matrixRt.at(0).at(0) =  cos(theta*PI/180);
	matrixRt.at(0).at(1) = -sin(theta*PI/180);
	matrixRt.at(0).at(2) = 0;
	matrixRt.at(0).at(3) = 0;

	matrixRt.at(1).at(0) =  sin(theta*PI/180);
	matrixRt.at(1).at(1) =  cos(theta*PI/180);
	matrixRt.at(1).at(2) = 0;
	matrixRt.at(1).at(3) = 0;


	matrixRt.at(2).at(1) = 0;
	matrixRt.at(2).at(2) = 1;
	matrixRt.at(2).at(3) = 0;

	matrixRt.at(3).at(0) = 0;
	matrixRt.at(3).at(1) = 0;
	matrixRt.at(3).at(2) = 0;
	matrixRt.at(3).at(3) = 1;

	//=======================================

	matrixRwT.at(0).at(0) = matrixRw.at(0).at(0);
	matrixRwT.at(0).at(1) = matrixRw.at(1).at(0);
	matrixRwT.at(0).at(2) = matrixRw.at(2).at(0);
	matrixRwT.at(0).at(3) = matrixRw.at(3).at(0);

	matrixRwT.at(1).at(0) = matrixRw.at(0).at(1);
	matrixRwT.at(1).at(1) = matrixRw.at(1).at(1);
	matrixRwT.at(1).at(2) = matrixRw.at(2).at(1);
	matrixRwT.at(1).at(3) = matrixRw.at(3).at(1);

	matrixRwT.at(2).at(0) = matrixRw.at(0).at(2);
	matrixRwT.at(2).at(1) = matrixRw.at(1).at(2);
	matrixRwT.at(2).at(2) = matrixRw.at(2).at(2);
	matrixRwT.at(2).at(3) = matrixRw.at(3).at(2);

	matrixRwT.at(3).at(0) = matrixRw.at(0).at(3);
	matrixRwT.at(3).at(1) = matrixRw.at(1).at(3);
	matrixRwT.at(3).at(2) = matrixRw.at(2).at(3);
	matrixRwT.at(3).at(3) = matrixRw.at(3).at(3);

	std::vector< std::vector< double > > inter = Matrix::matrixMultiply(matrixRt,matrixRw);

	Matrix newM;
	// newM.matrix = matrixRt;
	// newM.printMatrix();
	// // cout << "========================================" << endl;
	// newM.matrix = matrixRwT;
	// newM.printMatrix();
	// // cout << "========================================" << endl;

	newM.matrix = matrixRw;
	newM.printMatrix();

	matrix = Matrix::matrixMultiply(matrixRwT,inter);

}
