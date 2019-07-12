#ifndef Model_H
#define Model_H
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
#include "Vertex.h"
#include "Face.h"
#include "Matrix.h"
#include "Material.h"
#include "MatrixTranslate.h"

class Model {
	public:
		Model();
		Model(double r, double cx, double cy, double cz, double ka0, double ka1, double ka2, double kd0, double kd1, double kd2, double ks0, double ks1, double ks2, double kr0, double kr1, double kr2);
		/* simple accessors */
		//inline int Minimum() const {return min;}

		/* Mutators */
		//inline void set_Minimum(int value) {min = value;}

		/* Member Variables */
		
		void checkModel(char* filename, char* outfilename);
		std::vector<Material>  checkMtllib(char* filename);
		bool verifyPYL(stringstream *pylstream);
		static bool startsWith(string line, string token);
		static double getValue(stringstream *plystream);
		void transformModel(Matrix transformation);
		void WriteModel();
		std::vector<double> calculateSurfaceNormal(Face face);
		std::vector<double> calculateSurfaceNormal(std::vector<double> point, std::vector<double> center);
		std::vector<Material> parseMtllib(stringstream *objstream);
		int numVertices;
		int numFaces;
//		Vertex meanVertex;
		double maxX;
		double minX;
		double maxY;
		double minY;
		double maxZ;
		double minZ;
		double stdevX;
		double stdevY;
		double stdevZ;
		double meanX;
		double meanY;
		double meanZ;
		char* output;
		
		Material mat;
		std::vector<Material> mtllib;
		
		// sphere specific
		bool isSphere;
		double R;
		std::vector<double> center;
		
		string comment;
	    std::vector<Vertex>  vertices; 	// a vector that stores the vertices
		std::vector<Face>  faces;   // a vector that stores the faces
		std::vector<Matrix> transformations; // a vector that stroes transformations
		Matrix finalT;
		std::vector<string> header; // a vector that stroes transformations

};	

#endif // Model_H
