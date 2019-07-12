#ifndef Camera_H
#define Camera_H
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
#include "Model.h"
#include "Material.h"
#include "Light.h"
#include <cmath>
#include <limits>
#include <iomanip>
#include <type_traits>
#include <algorithm>
#include <functional>
#include <numeric>



class Camera {
	public:
		Camera(string filename);
		Camera();
		double top,lft,rgt,bot;
	    double focalLength;
		std::vector<double> FP;
		std::vector<double> LAP;
		std::vector<double> VUP;
		std::vector<double> WV;
		std::vector<double> UV;
		std::vector<double> VV;
		std::vector<double> ambient;
		std::vector<Light> lights;
		std::vector<Material> mtllib;
		std::vector<Model> models;
		void checkModels(char* filename);
		double getValue(stringstream *plystream);
		bool startsWith(string line,string token);
		bool verifyOBJ(stringstream *objstream);		
		double wdh;
		double hgt;
};	

#endif // Camera_H