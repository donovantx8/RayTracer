#ifndef Image_H
#define Image_H
#include <fstream>
using std::ifstream;
#include <iostream>
using std::cout;
using std::endl;
using std::cerr;
#include <ostream>
using std::ostringstream;
using std::ios;
#include <string>
using std::string;
#include <sstream>
using std::stringstream;
#include <ctype.h>
#include <vector>
#include "ImagePixel.h"

class Image {
	public:
		Image(int height, int width);
		Image();
		/* simple accessors */
		inline int Minimum() const {return min;}
		inline double Average() const {return avg;}
		inline double Maximum() const {return max;}
		inline int Height() const {return hgt;}
		inline int Width() const {return wdh;}
		inline int Resoltuion() const {return res;}
		inline int DMaximum() const {return dmax;}
		
		/* Mutators */
		inline void set_Minimum(int value) {min = value;}
		inline void set_Average(double value) {avg = value;}
		inline void set_Maximum(int value) {max = value;}
		inline void set_DMaximum(int value) {dmax = value;}
		inline void set_Height(int value) {hgt = value;}
		inline void set_Width(int value) {wdh = value;}
		inline void set_Resolution() {res = hgt * wdh;}

		void print_Pixels();
		void set_Coordinates();
		void write_Image(string filename);

		char *output;
		char *input;		
		int min;			 			// the min pixel value
		double avg;						// the average pixel value
		int max; 					// the max pixel value
		int dmax; 					// the declared max pixel value
		int hgt;						// the hieght of the image
		int wdh;						// the width of the image
		int res;					  	// the resolution of the image
		int pixelcount; 			  	// number of read pixels in the image
		std::vector<ImagePixel>  pixels; 	// a vector that store pixels properly formatted
		std::vector< std::vector< ImagePixel > > pixels2D;
};	

#endif // Image_H
