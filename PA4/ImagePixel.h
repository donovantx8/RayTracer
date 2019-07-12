#ifndef IMAGE_PIX_H
#define IMAGE_PIX_H
#include <math.h> 
#include <vector>
#include "Matrix.h"
#include "Material.h"
#include "Camera.h"
#include "Face.h"
#include "Model.h"
#include "Light.h"


class ImagePixel {

	public:
		ImagePixel(Camera cam, int r, int c);
		ImagePixel();
		int Red;
		int Green;
		int Blue;
		int X;
		int Y;
		int distVX;
		int distVY;
		std::vector<double> pixpt;
		std::vector<double> center;
		std::vector<double>  weights; 
		std::vector<double>  ections;
		std::vector<double>  rayL;
		std::vector<double>  rayD;
		std::vector<Model>  models;
		bool isSphere;
		Face face;
		bool set;
		inline void set_Coords(int x, int y) {X = x;Y=y;}
		std::vector<double> colorPixel(std::vector<Light> sources, Camera cam, Material mat, std::vector<double> rayL, std::vector<double> rayD, std::vector<double> accum, std::vector<double> refatt, int level);
		
		double t;
		double tmin;
		int count;
		double tmax;
		Model model;
		Material material;
		/*bool operator <(ImagePixel const& rhs) const {
       			 return rhs.value > value;
    		}	
		int operator ()() const {
       			 return value;
    		}
		inline bool operator==(ImagePixel const& rhs){ return (rhs.value == value); }
		*/
};

#endif // IMAGE_PIX_H
