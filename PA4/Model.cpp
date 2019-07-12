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

unsigned const int MAX_INT = std::numeric_limits<unsigned int>::max();
const int MAX = 255;
const  int MIN  = -255;
//Check if the file begins with the characters "pyl", 
//close the stream if it doesn't and exit, no further
//verfication need be done.
Model::Model(){}
Model::Model(double r, double cx, double cy, double cz, double ka0, double ka1, double ka2, double kd0, double kd1, double kd2, double ks0, double ks1, double ks2,  double kr0, double kr1, double kr2){
	R = r;
	isSphere = true;
	center.push_back(cx);
	center.push_back(cy);
	center.push_back(cz);

	mat.ka.push_back(ka0);
	mat.ka.push_back(ka1);
	mat.ka.push_back(ka2);
	
	mat.ks.push_back(ks0);
	mat.ks.push_back(ks1);
	mat.ks.push_back(ks2);
	
	mat.kd.push_back(kd0);
	mat.kd.push_back(kd1);
	mat.kd.push_back(kd2);
	
	mat.kr.push_back(kr0);
	mat.kr.push_back(kr1);
	mat.kr.push_back(kr2);
	
}
bool Model::verifyPYL(stringstream *pylstream) {
	int cvid = 0;

	string line;
	while (!(*pylstream).eof() && !(startsWith(line,"end_header"))) {
		std::getline(*pylstream, line);
		header.push_back(line);
		if (startsWith(line,"element vertex")) {
			string vertexNum = line.substr (15,line.length()); 
			numVertices = atoi(vertexNum.c_str());
		}
		if (startsWith(line,"element face")) {
			string faceNum = line.substr (13,line.length());
			numFaces = atoi(faceNum.c_str());
		} 

	}

	// cout << "Number of Vertices: " << numVertices << endl;
	// cout << "Number of Faces   : " << numFaces << endl;
		maxX = MIN;
		maxY = MIN;
		maxZ = MIN;
		minX = MAX;
		minY = MAX;
		minZ = MAX;

	for (int i = 0; i < numVertices; i++) {
		double x = getValue(pylstream);
		double y = getValue(pylstream);
		double z = getValue(pylstream);
		pylstream->ignore(100,'\n');
		Vertex newVertex(x,y,z,cvid);
		newVertex.vals.push_back(x);
		newVertex.vals.push_back(y);
		newVertex.vals.push_back(z);

	//	cout << "New Vertex x:" << x << " y:" << y << " z:" << z << endl;
		vertices.push_back(newVertex);
		cvid++;

		if (x > maxX) {
			maxX = x;
		}
		if (x < minX) {
			minX = x;
		}	
		if (y > maxY) {
			maxY = y;
		}
		if (y < minY) {
			minY = y;
		}		
		if (z > maxZ) {
			maxZ = z;
		}
		if (z < minZ) {
			minZ = z;
		}
	}
	

		
	
	for (int i = 0; i < numFaces; i++) {
		int F = getValue(pylstream);
		Face newFace;
		newFace.numVertices= F;		
		for (int j = 0; j < F; j++) {
			int vertex = getValue(pylstream);
			newFace.vertices.push_back(vertices.at(vertex));
		}		
		faces.push_back(newFace);
		
	//	 cout << " F =  " << F << endl;
	}	

	return 0;
}

std::vector<Material>  Model::parseMtllib(stringstream *objstream) {
	std::vector<Material> materials;
	while (!(*objstream).eof()) {
		
		string line;
		while (!(*objstream).eof() && !(startsWith(line,"new"))) {
			std::getline(*objstream, line);
		//	cout << line << endl;
		}
//		cout << "here" << endl;
		double ka0,ka1,ka2,ks0,ks1,ks2,kd0,kd1,kd2 = 0.0;
		char skip;
		while (!(*objstream).eof()) {		
			bool kd = false;
			bool ka = false;
			bool ks = false;

			(*objstream).get(skip); (*objstream).get(skip);
			if (skip == 'd') {
				kd0 = getValue(objstream);
				kd1 = getValue(objstream);
				kd2 = getValue(objstream);
				objstream->ignore(100,'\n');
				kd = true;
			} 
			(*objstream).get(skip); (*objstream).get(skip);
			if (skip == 'a') {
				ka0 = getValue(objstream);
				ka1 = getValue(objstream);
				ka2 = getValue(objstream);
				objstream->ignore(100,'\n');
				ka = true;
			}
			(*objstream).get(skip); (*objstream).get(skip);
			if (skip == 's') {
				ks0 = getValue(objstream);
				ks1 = getValue(objstream);
				ks2 = getValue(objstream);
				objstream->ignore(100,'\n');
				ks = true;
			}		
			
			if (kd||ks||ka) {
				Material mat(ka0,ka1,ka2,ks0,ks1,ks2,kd0,kd1,kd2,0,0,0);
				materials.push_back(mat);
				std::getline(*objstream, line);
				kd = false;
				ka = false;
				ks = false;
			} else {
				std::getline(*objstream, line);
			}
		}


}
	cout << materials.size() << endl;
	return materials;
}


bool Model::startsWith(string line,string token)
{
	if (!line.compare(0, token.length(), token)) {
		return true;
	}	
	return false;
}
void Model::checkModel(char* filename, char* outfilename)
{
  output = outfilename;
  ifstream istr(filename);
  if (istr.fail()) {
	cerr << "Failed to open file " << filename << endl;
	exit(-1);
  }

  stringstream str;
  istr >> noskipws >> str.rdbuf();
  if (!str.bad())
    {
		// verifyPYL(&str); /// Verify and open PYL
		//   verifyOBJ(&str); /// Verify and open OBJ
    }
}

std::vector<Material>  Model::checkMtllib(char* filename)
{
   cout << filename << endl;
  ifstream istr(filename);
  if (istr.fail()) {
	cerr << "Failed to open Material Library " << filename << endl;
	exit(-1);
  }

  stringstream str;
  istr >> noskipws >> str.rdbuf();
  if (!str.bad())
    {
		// verifyPYL(&str); /// Verify and open PYL
		   mtllib = parseMtllib(&str); /// Verify and open OBJ
		   
    }
}

void Model::transformModel(Matrix transformation) 
{

	std::vector<Vertex>::iterator itrV;
    for (itrV = vertices.begin(); itrV != vertices.end(); itrV++) {
    		double disx = ((*itrV).x);
    		double disy = ((*itrV).y);
    		double disz = ((*itrV).z);
    		((*itrV).x) = ((transformation.matrix.at(0).at(0) * disx) + 
    					   (transformation.matrix.at(0).at(1) * disy) + 
    					   (transformation.matrix.at(0).at(2) * disz) + 
    					   (transformation.matrix.at(0).at(3) * 1)   ) ; 

    		((*itrV).y) = ((transformation.matrix.at(1).at(0) * disx) + 
						   (transformation.matrix.at(1).at(1) * disy) + 
						   (transformation.matrix.at(1).at(2) * disz) + 
						   (transformation.matrix.at(1).at(3) * 1)   ) ; 

			((*itrV).z) = ((transformation.matrix.at(2).at(0) * disx) + 
						   (transformation.matrix.at(2).at(1) * disy) + 
						   (transformation.matrix.at(2).at(2) * disz) + 
						   (transformation.matrix.at(2).at(3) * 1)   ) ; 

			// double epsilon = std::numeric_limits<double>::epsilon();
			// if (std::abs(((*itrV).z) - 0) < epsilon + 0.0000001) {
			// 	(*itrV).z = 0;
			// }
			// if (std::abs(((*itrV).x) - 0) < epsilon + 0.0000001) {
			// 	(*itrV).x = 0;
			// }
			// if (std::abs(((*itrV).y) - 0) < epsilon + 0.0000001) {
			// 	(*itrV).y = 0;
			// }

	}
}

std::vector<double> Model::calculateSurfaceNormal(std::vector<double> point, std::vector<double> center) {
	std::vector<double> surface;
	surface = point - center;
	surface = surface % Matrix::vectorLength(surface);	
	return surface;
}

std::vector<double> Model::calculateSurfaceNormal(Face face) {
	std::vector<double> edge1;
	std::vector<double> edge2;
	Vertex P1 = face.vertices.at(0);
	Vertex P2 = face.vertices.at(1);
	Vertex P3 = face.vertices.at(2);
		edge1 = P2.vals - P1.vals;
	edge2 = P3.vals - P1.vals;
	std::vector<double> surface = edge1 ^ edge2;
	surface = surface % Matrix::vectorLength(surface);	
	return surface*-1;	
}


double Model::getValue(stringstream *plystream)
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

void Model::WriteModel() {

	string copy = output;
	copy.pop_back();copy.pop_back();copy.pop_back();copy.pop_back();
	if (transformations.size() ==1) {
		std::string cen = "_centered.ply";	
		copy.append(cen);
	}
	if (transformations.size() > 1) {
		std::string cen = "_rounded.ply";
		copy.append(cen);
	}

	const char *cstr = copy.c_str();
	std::ofstream out(cstr);


	
    std::vector<string>::iterator itrH;
    for (itrH = header.begin(); itrH != header.end(); itrH++) {
    	out << (*itrH) << endl;
    }

	if (transformations.size() > 0) {
		finalT = finalT.Matrix::combineTransformations(transformations);
		transformModel(finalT);
	} else if (transformations.size() == 1) {
		transformModel(transformations.at(0));
	}

	std::vector<Vertex>::iterator itrV2;
    for (itrV2 = vertices.begin(); itrV2 != vertices.end(); itrV2++) {
    	out << (*itrV2).x << " " << (*itrV2).y << " " << (*itrV2).z << " " <<'\n' ;
    }

	std::vector<Face>::iterator itrF;
    for (itrF = faces.begin(); itrF != faces.end(); itrF++) {
    	out << (*itrF).vertices.size() << " ";
    	std::vector<Vertex>::iterator itrV3;
    	for (itrV3 = (*itrF).vertices.begin(); itrV3 != (*itrF).vertices.end(); itrV3++) {

    		out << (*itrV3).vid << " ";
   		}	out << endl;

    }
}
