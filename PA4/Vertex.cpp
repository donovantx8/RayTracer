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
#include <math.h>

double Vertex::maxX = -5000;
double Vertex::minX = 5000;
double Vertex::maxY = -5000;
double Vertex::minY = 5000;
double Vertex::maxZ = -5000;
double Vertex::minZ = 5000;

           // this is a definition, 


Vertex::Vertex(double X, double Y, double Z, int VID) {
	x = X;
	y = Y;
	z = Z;
	vid = VID;
}

std::vector<double> Vertex::calculateStandardDeviations(std::vector<Vertex> vertices, double meanX, double meanY, double meanZ)
{
    double px;
	double py;
	double pz;
	int i = 0;
	for(i=0; i<(signed)vertices.size();++i) {
		px+=(pow((vertices.at(i).x-meanX),2.0));
		py+=(pow((vertices.at(i).y-meanY),2.0));
		pz+=(pow((vertices.at(i).z-meanZ),2.0));		
	}
	
    double stdevX = sqrt(px/vertices.size());  
	double stdevY = sqrt(py/vertices.size());  
	double stdevZ = sqrt(pz/vertices.size());  

	std::vector<double> deviations;
	deviations.push_back(stdevX);
	deviations.push_back(stdevY);
	deviations.push_back(stdevZ);
	
	return deviations;
	
}
