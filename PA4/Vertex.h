#ifndef Vertex_H
#define Vertex_H
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
//#include "Vertex.h"
//#include "Face.h"

class Vertex {
	public:
		Vertex(double X, double Y, double Z, int VID);
		/* simple accessors */
		//inline int Minimum() const {return min;}

		/* Mutators */
		//inline void set_Minimum(int value) {min = value;}

		/* Member Variables */
		std::vector<double> calculateStandardDeviations(std::vector<Vertex> vertices, double meanX, double meanY, double meanZ);
		const inline double getX() { return x;}
		int vid;
		std::vector<double> vals;
		double x;
		double y;
		double z;

		static double maxX;
		static double minX;
		static double maxY;
		static double minY;
		static double maxZ;
		static double minZ;



};	

#endif // Vertex_H
