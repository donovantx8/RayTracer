#ifndef Matrix_H
#define Matrix_H
#include <fstream>
using std::ifstream;
#include <iostream>
using std::cout;
using std::endl;
using std::cerr;
#include <string>
using std::string;
#include <sstream>
using std::stringstream;
#include <ctype.h>
#include <vector>
#include <string>
//#include "Matrix.h"
//#include "Matrix.h"
using namespace std;

		vector<double> operator-(const vector<double>& lhs, const vector<double>& rhs);
		vector<double> operator+(const vector<double>& lhs, const vector<double>& rhs);
		vector<double> operator*(const vector<double>& lhs, const double rhs);
		vector<double> operator*(const double lhs, const vector<double>& rhs);
		vector<double> operator^(const vector<double>& vectorA, const vector<double>& vectorB);	
		double operator&(const vector<double>& vectorA, const vector<double>& vectorB);	
		vector<double> operator%(const vector<double>& lhs, const double mag);//normalize operator
		
		// return type is a vector of integers
		// return type is a vector of integers

class Matrix {
	public:
		Matrix();

		std::vector< std::vector< double > > matrixMultiply(std::vector< std::vector< double > > M1, std::vector< std::vector< double > > M2);
		void printMatrix();
		static double vectorLength(std::vector<double> vectorI);
		Matrix combineTransformations(std::vector<Matrix> trans);
		static void printVector(std::vector<double> axis);







		//4x4 Base Matrix	
		std::vector< std::vector< double > > matrix;


};	

#endif // Matrix_H