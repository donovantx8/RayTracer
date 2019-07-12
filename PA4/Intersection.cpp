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
#include <algorithm>
#include <stdlib.h> 
#include <cctype> 
#include <limits>
#include <string>
#include "Vertex.h"
#include "Ray.h"
#include "Matrix.h"
#include "Image.h"
#include "ImagePixel.h"
#include "Model.h"
#include "Face.h"
#include "Intersection.h"
#include <math.h>       /* acos */

#define PI 3.14159265
Intersection::Intersection() {}

void Intersection::intersectPolygons() {
	Matrix blank;count =0;
	image.Image::set_Height(camera.hgt);
	image.Image::set_Width(camera.wdh);
	std::vector<double> T;
	//printf("%i Models and %iFaces\n",models.size(),models.at(0).numFaces);
	for (int i = 0; i <= image.Height()-1; i++ ) {				
		for (int j = 0; j <= image.Width()-1; j++ ) {
			ImagePixel add(camera,j,i);
			add.t = 0;
			add.X = j;
			add.Y = i;
			add.models = models;
			Ray ray(camera,add);			
			double tmin = std::numeric_limits<double>::max();
			std::vector<Model>::iterator model_itr;
			int mate = 0;
			for (model_itr = models.begin(); model_itr != models.end(); model_itr++) {
				std::vector<double> inters;
				if ((*model_itr).isSphere) {					
					std::vector<double> solutions;
					solutions = checkForSphereIntersections(ray,(*model_itr));
					if (solutions.at(0) != -1 && solutions.at(1) != -1 && solutions.at(2) != -1) {
						if (solutions.at(3) < tmin) {
								add.isSphere = true;
								add.rayL = ray.L;
								add.rayD = ray.D;
								add.material = (*model_itr).mat;
								add.center = (*model_itr).center;
								tmin = solutions.at(3);
								inters.push_back(solutions.at(0));
								inters.push_back(solutions.at(1));
								inters.push_back(solutions.at(2));
								add.ections = inters;

						} else {
							cout << "found but behind" << endl;
						}
					}
					
				} else {
                    
					std::vector<Face>::iterator face_itr;	
					for (face_itr = (*model_itr).faces.begin(); face_itr != (*model_itr).faces.end(); face_itr++) {
						std::vector<double> solutions;
						solutions = checkForIntersections(ray, (*face_itr));
						if (solutions.at(0) >= 0 && solutions.at(1) >= 0 && (solutions.at(0) + solutions.at(1) <= 1) && solutions.at(2) > 0) {
							if (solutions.at(2) < tmin) {
								add.isSphere = false;
								add.rayL = ray.L;
								add.rayD = ray.D;
								add.face = (*face_itr);
					//			cout << add.face.vertices.size() << endl;
								add.material = (*model_itr).mtllib.at(mate);
								tmin = solutions.at(2);
								inters = solutions;
								add.ections = inters;
							}
							
						} 			
					}
				}
				mate++;
			}
			
			if (tmin != std::numeric_limits<double>::max()) {
				add.t = tmin;
				
				T.push_back(tmin);
			} 	
			image.pixels.push_back(add);
			
		}		
		
	}
	cout << "done tracing" << endl;
	double tmax = *std::max_element(T.begin(),T.end());
	double tmin = *std::min_element(T.begin(),T.end());
	std::vector<ImagePixel>::iterator p_itr = image.pixels.begin();
	for (int i = 0; i <= image.Height()-1; i++ ) {
		for (int j = 0; j <= image.Width()-1; j++ ) {
			if((*p_itr).t > .00001) {
				count++;
				/*double ratio = 2 * ((*p_itr).t - tmin) / (tmax - tmin);
				double r = std::max(0.0, 255 * (1 - ratio));
				double b = std::max(0.0, 255 * (ratio - 1));
				double g = 255 - b - r;
				(*p_itr).Red = r;
				(*p_itr).Blue = b;
				(*p_itr).Green = g;*/
				Material mat;
				mat = (*p_itr).material;
				std::vector<double> accum;
				accum.push_back(0.0);accum.push_back(0.0);accum.push_back(0.0);
				std::vector<double> refatt;
				refatt.push_back(1.0);refatt.push_back(1.0);refatt.push_back(1.0);
				string outf(image.input);
				int level = 0;
				if (outf == "scene5.txt") {
					level = 6;
				} 				
				std::vector<double> color = (*p_itr).colorPixel(camera.lights, camera, mat, (*p_itr).rayL, (*p_itr).rayD, accum, refatt,level);
				(*p_itr).Red = (int)min(255.0, (color.at(0) * 254.999));
				(*p_itr).Green  = (int)min(255.0, (color.at(1) * 254.999));
				(*p_itr).Blue = (int)min(255.0, (color.at(2) * 254.999));
			    

			} else {
				(*p_itr).Red = 0;
				(*p_itr).Blue = 0;
				(*p_itr).Green = 0;
			}
			p_itr++;
		}
	}printf("Counts %i\n",count);
	image.Image::set_Coordinates();
	image.Image::write_Image("test.ppm");
	
}

std::vector<double> Intersection::checkForSphereIntersections(Ray ray, Model sphere) {
	
	std::vector<double> Tv = sphere.center - ray.L;
	double v = Tv & ray.D;
	double c2 = Tv & Tv;
	double disc = (sphere.R*sphere.R) - (c2 - (v*v));
		

	if (disc < 0) {
		std::vector<double> intersections;
		intersections.push_back(-1);
		intersections.push_back(-1);
		intersections.push_back(-1);
		intersections.push_back(-1);
		return intersections;
	} else {
		double d = sqrt(disc);
		double t = v - d;
		std::vector<double> pts = ray.L + (t * ray.D);		
		pts.push_back(t);
		return pts;
	}
}
std::vector<double> Intersection::checkForIntersections(Ray ray, Face face) {
	std::vector<double> A = face.vertices.at(0).vals;
	double ax = A.at(0);
	double ay = A.at(1);
	double az = A.at(2);
	std::vector<double> B = face.vertices.at(1).vals;	
	double bx = B.at(0);
	double by = B.at(1);
	double bz = B.at(2);
	std::vector<double> C = face.vertices.at(2).vals;
	double cx = C.at(0);
	double cy = C.at(1);
	double cz = C.at(2);
	std::vector<double> D = ray.D;
	double dx = D.at(0);
	double dy = D.at(1);
	double dz = D.at(2);
	std::vector<double> L = ray.L;
	double lx = L.at(0);
	double ly = L.at(1);
	double lz = L.at(2);
	if (face.vertices.at(0).vid == 0 && face.vertices.at(1).vid == 1 && face.vertices.at(2).vid == 2) {

	}
	
	double az_cz = az - cz;	
	double ay_cy = ay - cy;
	double ax_lx = ax - lx;
	double ax_bx = ax - bx;
	double ay_ly = ay - ly;
	double ax_cx = ax - cx;	
	double az_lz = az - lz;	
	double ay_by = ay - by;
	double az_bz = az - bz;
	double M = ((az_cz) * dy - (ay_cy) * dz ) * (ax_bx) - (((az_cz) * dx - (ax_cx) * dz) *  (ay_by)) + ((ay_cy) * dx - (ax_cx) * dy)  *  (az -  bz);  

	
	double b =   (((az_cz) * dy - ((ay_cy)) * dz ) * (ax_lx) - ((az_cz) * dx - (ax_cx) * dz) *  (ay_ly) + (((ay_cy)) * dx - (ax_cx) * dy)  * (az_lz) )/ M;  
	double p;
	if (b >= 0) {
		p = (  ((az_lz) * dy - (ay_ly) * dz ) * (ax_bx) - ((az_lz) * dx - (ax_lx) * dz) *  (ay_by) + ((ay_ly) * dx - (ax_lx) * dy)  * (az_bz) )/ M;  

	} else {
		p = -1;
	}
	double t;
	if (b >= 0 && p >= 0 && (b+p<=1)) {
		t =  ( ((ay_ly) * (az_cz) - ((ay_cy)) * (az_lz)) * (ax_bx) - ((ax_lx) * (az_cz) - (ax_cx) * (az_lz)) * (ay_by) + (((ax_lx) * (ay_cy)) - (ax_cx) * (ay_ly)) * (az_bz) )/ M; 

	} else {
		t = -1;
	}
	
	std::vector<double> intersections;
	intersections.push_back(b);
	intersections.push_back(p);
	intersections.push_back(t);

	if(t != -1) {
	//		Matrix::printVector(intersections);
	}
	return intersections;
}
