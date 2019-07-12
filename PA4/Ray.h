#ifndef Ray_H
#define Ray_H
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
#include "Model.h"
#include "ImagePixel.h"
#include "Camera.h"

//#include "Ray.h"
//#include "Ray.h"

class Ray {
	public:
		Ray(Camera cam, ImagePixel pixel);
		Ray();
		std::vector<double> org;
		std::vector<double> dir;
		std::vector<double> D;
		std::vector<double> L;
		std::vector<double> V;
		std::vector<double> rUcV;
		std::vector<double> ray;
		std::vector<double> dN;		
		std::vector<double> raypt;	
		double t;
		double i;
		double j;
};	

#endif // Ray_H
