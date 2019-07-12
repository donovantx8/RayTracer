#include <iostream>
using std::cout;
using std::endl;
using std::cin;
#include <fstream>
using std::ifstream;
#include "Model.h"
#include "Matrix.h"
#include "MatrixTranslate.h"
#include "MatrixRotate.h"
#include "MatrixScale.h"
#include "Camera.h"
#include "Intersection.h"
#include <string>
#include <sstream>

int main(int argc, char* argv[])
{
  // check for the correct number of arguments
  if (argc != 3) {
	cout << "Incorrect number of arguments" << endl;
	exit(-1);
  }
   Camera cam(argv[1]);
   Intersection intersect;
   intersect.camera = cam;
   intersect.models = cam.models;
   Image images;
   images.output = argv[2];
   images.input = argv[1];
   intersect.image = images;
   intersect.Intersection::intersectPolygons();

/* Model mood;
  mood.Model::checkModel(argv[2],argv[2]);
  
  Intersection intersect;
  intersect.camera = cam;
  intersect.models.push_back(mood);
  Image images;
  images.output = argv[3];
  intersect.image = images;
  intersect.Intersection::intersectPolygons();*/

/*   while (true) {
	   cout << "Please enter a command :";
	   getline(cin, input);
	   stringstream ss;
	   ss << input;  
	   string get;
	   ss >> get;
	   if (get == "W") {
	   		mood.Model::WriteModel();
	    	exit(-1);
	   } else if (get == "S") {
	   		double x,y,z;
	   		if (!(ss >> x)) {
	   			cerr << "Bad format <S> <double> <double> <double>" << endl;
	   			exit(-1);
	   		} else if (!(ss >> y)) {
	   			cerr << "Bad format <S> <double> <double> <double>" << endl;
	   			exit(-1);
	   		} else if (!(ss >> z)) {
	   			cerr << "Bad format <S> <double> <double> <double>" << endl;
	   			exit(-1);   
	   		}
	   		mood.transformations.push_back(MatrixScale(x,y,z));

	   			   cout << input << " Good Input" << endl;

	   } else if (get == "T") {
	   		double x,y,z;
	   		if (!(ss >> x)) {
	   			cerr << "Bad format <T> <double> <double> <double>" << endl;
	   			exit(-1);
	   		} else if (!(ss >> y)) {
	   			cerr << "Bad format <T> <double> <double> <double>" << endl;
	   			exit(-1);
	   		} else if (!(ss >> z)) {
	   			cerr << "Bad format <T> <double> <double> <double>" << endl;
	   			exit(-1);   
	   		}
	   		mood.transformations.push_back(MatrixTranslate(-mood.meanX,-mood.meanY,-mood.meanZ));
	   			   cout << input << " Good Input" << endl;


	   } else if (get == "R") {
	   		double x,y,z,theta;
	   		if (!(ss >> x)) {
	   			cerr << "Bad format <R> <double> <double> <double> <theta>" << endl;
	   			exit(-1);
	   		} else if (!(ss >> y)) { 
	   			cerr << "Bad format <R> <double> <double> <double> <theta>" << endl;
	   			exit(-1);
	   		} else if (!(ss >> z)) {
	   			cerr << "Bad format <R> <double> <double> <double> <theta>" << endl;
	   			exit(-1);   
	   		} else if (!(ss >> theta)) {
	   			cerr << "Bad format <R> <double> <double> <double> <theta>" << endl;
	   			exit(-1);   
	   		}

	   		mood.transformations.push_back(MatrixRotate(x,y,z,theta));
	   			   cout << input << " Good Input" << endl;


	   }
 } */

  return 0;
}



