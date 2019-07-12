#ifndef Intersection_H
#define Intersection_H
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
#include "Ray.h"
#include "Image.h"
#include "Camera.h"

class Intersection {
	public:
		Intersection();
		void intersectPolygons();
		std::vector<double> createRay(Camera cam, int r, int c);
		std::vector<double> calculateSurfaceNormal(std::vector<Vertex> vertices);
		std::vector<double> scaleVector(std::vector<double> vec3, double scalar);
		std::vector<double> checkForIntersections(Ray ray, Face face);
		static std::vector<double> checkForSphereIntersections(Ray ray, Model sphere);
		std::vector<double> N;
		std::vector<double> NP;
		std::vector<double> U;
		std::vector<double> V;
		double d;
		std::vector<Model> models;
		Camera camera;
		int count;
		Image image;

};	

#endif // Intersection_H