#include <fstream>
using std::ifstream;
#include <iostream>
using std::ios;
#include <sstream>
using std::ios;
using std::stringstream;
using std::noskipws;
#include <ostream>
using std::ostringstream;
using std::ios;
#include <stdlib.h> 
#include <cctype> 
#include <limits>
#include <string>
#include "Vertex.h"
#include "Matrix.h"
#include <math.h>       /* sqrt */
using std::vector;

Matrix::Matrix(){
	  std::vector<double> rows (4,0);                       // four doubles with value 0
	  matrix.push_back(rows);								// add four rows to the matrix
	  matrix.push_back(rows);
	  matrix.push_back(rows);
	  matrix.push_back(rows);

}

//Implementation of Matrix Multiplication M1 * M1 right to left ordering preserved
std::vector< std::vector< double > > Matrix::matrixMultiply (std::vector< std::vector< double > > M1, std::vector< std::vector< double > > M2) {
	std::vector< std::vector< double > > result;
	std::vector<double> rows (4,0);                      // four ints with value 0
	result.push_back(rows);
	result.push_back(rows); 
	result.push_back(rows);
	result.push_back(rows);
	for (int row = 0; row < 4; row++) {
		for (int col = 0; col < 4; col++) {
			       result.at(row).at(col) = (M1.at(row).at(0)*M2.at(0).at(col)) +
											(M1.at(row).at(1)*M2.at(1).at(col)) +
											(M1.at(row).at(2)*M2.at(2).at(col)) +
											(M1.at(row).at(3)*M2.at(3).at(col)) ;

		}

	}
	return result;
}


//Function to combine transformations
Matrix Matrix::combineTransformations(std::vector<Matrix> trans) {
	Matrix newM; 																											// Create New Matrix
	if (trans.size() == 1) {	
		newM.matrix = trans.at(0).matrix;
		return newM;
	} else if (trans.size() == 2) {		
		newM.matrix = Matrix::matrixMultiply(trans.at(1).matrix,trans.at(0).matrix);	
		trans.at(0).printMatrix();
		// cout << "=============================" << endl;
		trans.at(1).printMatrix();																				// If two transformations multiply and return them
		newM.printMatrix();
		return newM;
	} else if (trans.size() > 2) {																							// If more than two transformations multiply the first two, delete the first element set the new first element to the product and recurrr
		std::vector< std::vector< double > > inter = Matrix::matrixMultiply(trans.at(1).matrix,trans.at(0).matrix);
		trans.erase (trans.begin());
		newM.matrix = inter;
		trans.at(0) = newM;
		combineTransformations(trans);
	}

	return newM;
}


double Matrix::vectorLength(std::vector<double> vectorI) {
	std::vector<double>::iterator itrV;
	double sqr = 0;
    for (itrV = vectorI.begin(); itrV != vectorI.end(); itrV++) {
		sqr+= ((*itrV) * (*itrV));
	} 

	return sqrt(sqr); 
}


//Print Vectors in matrix format.
void Matrix::printMatrix() {
	std::vector< std::vector<double> >::iterator row;
	std::vector<double>::iterator col;
	for (row = matrix.begin(); row != matrix.end(); row++) {
	    for (col = row->begin(); col != row->end(); col++) {
			// cout << (*col) << "             ";
		} // cout << endl;		
	}
}

void Matrix::printVector(std::vector<double> axis){
	std::vector<double>::iterator itrV;
    for (itrV = axis.begin(); itrV != axis.end(); itrV++) {
		printf("<%f> ",(*itrV));
	} 	printf("\n");
}

vector<double> operator%(const vector<double>& lhs, const double mag){	//normalize operator

	if(lhs.size() == 0 || mag == 0){	// Vectors must be the same size in order to add them!
		throw std::runtime_error("Can't normalize 0 size/length vector");
	}

	std::vector<double> axis = lhs;     
	std::vector<double>::iterator itrV;
	std::vector<double>::iterator itrA = axis.begin();
    for (itrV = axis.begin(); itrV != axis.end(); itrV++) {
		(*itrA) = (*itrV) / mag;
		itrA++;
	} 	

	return axis;

}

vector<double> operator+(const vector<double>& lhs, const vector<double>& rhs){	// return type is a vector of integers


	if(lhs.size() != rhs.size()){	// Vectors must be the same size in order to add them!
		throw std::runtime_error("Can't add two vectors of different sizes!");
	}

	vector<double> result;	// Declaring the resulting vector, result

	for(int i=0; i < lhs.size(); i++){	// adding each element of the result vector
		result.push_back(lhs.at(i) + rhs.at(i));	// by adding each element of the two together
	}

	return result;	// returning the vector "result"

}

vector<double> operator-(const vector<double>& lhs, const vector<double>& rhs){	// return type is a vector of integers


	if(lhs.size() != rhs.size()){	// Vectors must be the same size in order to add them!
		throw std::runtime_error("Can't add two vectors of different sizes!");
	}

	vector<double> result;	// Declaring the resulting vector, result

	for(int i=0; i < lhs.size(); i++){	// adding each element of the result vector
		result.push_back(lhs.at(i) - rhs.at(i));	// by adding each element of the two together
	}

	return result;	// returning the vector "result"

}

vector<double> operator^(const vector<double>& vectorA, const vector<double>& vectorB){	// cross product override
	if(vectorA.size() != vectorB.size()){	// Vectors must be the same size in order to add them!
		throw std::runtime_error("Can't add two vectors of different sizes!");
	}
	
	std::vector<double> cross;
	double a1 = vectorA.at(0);
	double a2 = vectorA.at(1);
	double a3 = vectorA.at(2);

	double b1 = vectorB.at(0);
	double b2 = vectorB.at(1);
	double b3 = vectorB.at(2);

    cross.push_back((a2 * b3) - (a3 * b2)); 
    cross.push_back((a3 * b1) - (a1 * b3)); 
    cross.push_back((a1 * b2) - (a2 * b1)); 

	return cross;	// returning the vector "result"

}

double operator&(const vector<double>& vectorA, const vector<double>& vectorB){	// dot product override
	if(vectorA.size() != vectorB.size()){	// Vectors must be the same size in order to add them!
		throw std::runtime_error("Can't add two vectors of different sizes!");
	}
	
	double dot = (vectorA.at(0) * vectorB.at(0)) + (vectorA.at(1) * vectorB.at(1)) + (vectorA.at(2) * vectorB.at(2));

	return dot;	// returning the vector "result"

}

vector<double> operator*(const vector<double>& lhs, const double rhs){	//scalar vector



	vector<double> result;	// Declaring the resulting vector, result

	for(int i=0; i < lhs.size(); i++){	// adding each element of the result vector
		result.push_back(lhs.at(i) * rhs);	// by adding each element of the two together
	}

	return result;	// returning the vector "result"

}

vector<double> operator*(const double lhs, const vector<double>& rhs){	// scale vector



	return rhs * lhs;	// returning the vector "result"

}