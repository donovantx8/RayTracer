#include "Camera.h"
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
#include <cmath>
#include <limits>
#include <iomanip>
#include <type_traits>
#include <algorithm>
#include <functional>
#include <numeric>
#include <stdio.h>
#include <string.h>

Camera::Camera(){}

Camera::Camera(string filename) {
	ifstream istr(filename);
	if (istr.fail()) {
		cerr << "Failed to open file " << filename << endl;
		exit(-1);
	}

	stringstream str;
    istr >> noskipws >> str.rdbuf();
	if (str.bad()) {
		exit(-1);
	}
 
	string line;
	double xFP,yFP,zFP;
	double xLAP,yLAP,zLAP;
	double xVUP,yVUP,zVUP;
	double ambR,ambG,ambB;
	
	char skip;
	str >> skip;str >> skip;str >> skip;
	if (!(str >> xFP) || !(str >> yFP) || !(str >> zFP)) {
		cerr << "Failed to parse FP" << endl;
		exit(-1);
	}
	str >> skip;str >> skip;str >> skip;str >> skip;
	if (!(str >> xLAP) || !(str >> yLAP) || !(str >> zLAP)) {
		cerr << "Failed to parse look at point" << endl;
		exit(-1);
	}
	str >> skip;str >> skip;
	if (!(str >> xVUP) || !(str >> yVUP) || !(str >> zVUP)) {
		cerr << "Failed to parse look up point" << endl;
		exit(-1);
	}
	str >> skip;
	if (!(str >> focalLength)) {
		cerr << "Failed to parse focal length(d)" << endl;
		exit(-1);
	}
	str >> skip;str >> skip;str >> skip;str >> skip;str >> skip;str >> skip;	
	if (!(str >> lft) || !(str >> bot) || !(str >> rgt) || !(str >> top)) {
		cerr << "Failed to parse 4 INTS" << endl;
		exit(-1);
	}
	str >> skip;str >> skip;str >> skip;
	if (!(str >> wdh) || !(str >> hgt)) {
		cerr << "Failed to parse res" << endl;
		exit(-1);
	}
	str >> skip;str >> skip;str >> skip;str >> skip;str >> skip;str >> skip;str >> skip;
	if (!(str >> ambR) || !(str >> ambG) || !(str >> ambB)) {
		cerr << "Failed to parse ambient" << endl;
		exit(-1);
	}
	
	char get;
	while (!(str).eof()) {
		str >> get;
		if (get == 'l') { // its a light
			str >> skip;str >> skip;str >> skip;str >> skip;
			double x,y,z,w,r,g,b;
			if (!(str >> x) || !(str >> y) || !(str >> z) || !(str >> w) || !(str >> r) || !(str >> g) || !(str >> b)) {
				cerr << "Failed to parse lgiht" << endl;
				exit(-1);
			}
			Light light(x,y,z,r,g,b);
			lights.push_back(light);
		} else if (get == 's') { // its a sphere
			str >> skip;str >> skip;str >> skip;str >> skip;str >> skip;
			double r,x,y,z,w,ka0,ka1,ka2,ks0,ks1,ks2,kd0,kd1,kd2,kr0,kr1,kr2;
			if (!(str >> x) || !(str >> y) || !(str >> z) || !(str >> r) ||!(str >> ka0) || !(str >> ka1) || !(str >> ka2) || !(str >> kd0) || !(str >> kd1) || !(str >> kd2) || !(str >> ks0) || !(str >> ks1) || !(str >> ks2) || !(str >> kr0) || !(str >> kr1) || !(str >> kr2)) {
				cerr << "Failed to parse sphere" << endl;
				exit(-1);
			}
			Model sphere(r,x,y,z,ka0,ka1,ka2,kd0,kd1,kd2,ks0,ks1,ks2,kr0,kr1,kr2);
			models.push_back(sphere);	
		} else if (get == 'm') { // its a model
			str >> skip;str >> skip;str >> skip;str >> skip;
			string filename;
			if (!(str >> filename)) {
				cerr << "Failed to parse filename" << endl;
				exit(-1);
			}
			cout << filename << endl;
			char tab2[1024];
			strcpy(tab2, filename.c_str());
			checkModels(tab2);

		} else {
			str >> skip; // keep reading
		}
	}
	
	ambient.push_back(ambR);
	ambient.push_back(ambG);
	ambient.push_back(ambB);

	LAP.push_back(xLAP);
	LAP.push_back(yLAP);
	LAP.push_back(zLAP);

	VUP.push_back(xVUP);
	VUP.push_back(yVUP);
	VUP.push_back(zVUP);

	FP.push_back(xFP);
	FP.push_back(yFP);
	FP.push_back(zFP);

	WV = FP - LAP;
	WV = WV % Matrix::vectorLength(WV);
	UV = VUP ^ WV;
	UV = UV % Matrix::vectorLength(UV);
	VV = WV ^ UV;

	
/*	printf("VUP:");
	Matrix::printVector(VUP);
	printf("Look at Point:");
	Matrix::printVector(LAP);
	printf("Focal Point, FP, EYE:");
	Matrix::printVector(FP);
	printf("W:");
	Matrix::printVector(WV);
	printf("U:");
	Matrix::printVector(UV);
	printf("V:");
	Matrix::printVector(VV);
	//cout << "doubleresX,resY: " << wdh << " " <<  hgt << endl;
	//cout << "focal length: " << focalLength << endl;
	//cout << "top,bot,lft,rgt: " << top << " " <<  bot << " " <<  lft << " " << rgt << endl;*/
}

bool Camera::verifyOBJ(stringstream *objstream) {
	int cvid = 1;int numVertices = 0; 
	int mid = 0;Model mood;
	while (!(*objstream).eof()) {
		//cout << "reading" << endl;
		string line;
		while (!(*objstream).eof() && !(startsWith(line,"o Object."))) {
			std::getline(*objstream, line);
			cout << "skipping "  << line << endl;
			if (startsWith(line,"mtllib")) {
				string materialFileName = line.substr(7,line.length()-1); 
				cout << "material" << materialFileName << endl;
				char tab2[1024];
				strcpy(tab2, materialFileName.c_str());
				mtllib = mood.Model::checkMtllib("material.mtl");
				cout << mood.mtllib.size() << endl;
				// parse materials
			}
		}

		
		bool isOBJ = false;
		
		char skip;
		(*objstream).get(skip);
		while ((!(*objstream).eof() && skip == 'o') || (!(*objstream).eof() && skip == 'v')) {
			//cout << "inside2" << endl;
			if (skip == 'o') {
				objstream->ignore(100,'\n');
				(*objstream).get(skip);
			}
			double x = getValue(objstream);
			double y = getValue(objstream);
			double z = getValue(objstream);
			objstream->ignore(100,'\n');
			Vertex newVertex(x,y,z,cvid);
			newVertex.vals.push_back(x);
			newVertex.vals.push_back(y);
			newVertex.vals.push_back(z);
			if (cvid == 2983 || cvid == 2984) {
				cout << "v " << x << " " << y << " " << z << endl;	
			}
			

			mood.vertices.push_back(newVertex);
			cvid++;
			numVertices++;
			(*objstream).get(skip);
		}
		(*objstream).get(skip);(*objstream).get(skip);

		//cout << skip << endl;
		while ((!(*objstream).eof() && skip == 'u') || (!(*objstream).eof() && skip == 'f')) {
			//cout << "inside3" << endl;
			if (skip == 'u') {
				objstream->ignore(100,'\n');
				(*objstream).get(skip);
			}
			Face newFace;
			newFace.numVertices = 3;		
			for (int j = 0; j < 3; j++) {
				int vertex = getValue(objstream);
				newFace.vertices.push_back(mood.vertices.at(vertex-1));
			}		
			mood.faces.push_back(newFace);
			//cout << "f" << " " << newFace.vertices.at(0).vid << " " << newFace.vertices.at(1).vid << " " << newFace.vertices.at(2).vid << endl;
			isOBJ = true;
			objstream->ignore(100,'\n');
			(*objstream).get(skip);
		}	

		
	}
	mood.isSphere = false;
	cout << "New Model" << endl;
    Model moood = mood;
	models.push_back(moood);
	cout << "New Model" << endl;
	return 0;
}

void Camera::checkModels(char* filename)
{
  ifstream istr(filename);
  if (istr.fail()) {
	cerr << "Failed to open obj file " << filename << endl;
	exit(-1);
  }

  stringstream str;
  istr >> noskipws >> str.rdbuf();
  if (!str.bad())
    {
		// verifyPYL(&str); /// Verify and open PYL
		   verifyOBJ(&str); /// Verify and open OBJ
    }
}

bool Camera::startsWith(string line,string token)
{
	if (!line.compare(0, token.length(), token)) {
		return true;
	}	
	return false;
}

double Camera::getValue(stringstream *plystream)
{
	double point;
	if((*plystream) >> point) {
		return point;
	}
	while ((*plystream).fail() && !(*plystream).eof()) {
		(*plystream).clear();
		if ((*plystream).eof()) {
			return -6;
		}
		(*plystream) >> point;
	}	
	if ((*plystream).eof()) {
			return -6;
	}
	return point;
}
