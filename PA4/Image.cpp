#include <fstream>
using std::ifstream;
#include <iostream>
using std::ios;
using std::cout;
using std::endl;
using std::cin;
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
#include <gtest/gtest.h>
#include "Image.h"

unsigned const int MAX_INT = std::numeric_limits<unsigned int>::max();
const int MAX = 255;
const  int MIN  = -256;
Image::Image(){}

Image::Image(int height, int width) {
	hgt = height;
	wdh = width;
	pixelcount = 3 * hgt * wdh;
}

void Image::print_Pixels() {
	std::vector< std::vector<ImagePixel> >::iterator row;
	std::vector<ImagePixel>::iterator col;
	for (row = pixels2D.begin(); row != pixels2D.end(); row++) {
	    for (col = row->begin(); col != row->end(); col++) {
//			cout << (*col).X << " " << (*col).Y << " ";
		} //cout << endl;		
	}
}

void Image::write_Image(string filename) {
	const char *cstr = output;
	std::ofstream out(cstr);
	out << "P3" << endl;
	out << wdh << " " << hgt << " " << "255" << endl;
    std::vector< std::vector<ImagePixel> >::iterator row;
    std::vector<ImagePixel>::iterator col;
   
    for (row = pixels2D.begin(); row != pixels2D.end(); row++) {
        for (col = row->begin(); col != row->end(); col++) {
            out << (*col).Red << " " << (*col).Green << " " << (*col).Blue << " " ;
		} out << endl;		
	}
	exit(-1);
}

void Image::set_Coordinates() {
	pixels2D.resize(hgt);
	for (int i = 0; i < hgt; i++) {
	    pixels2D.at(i).resize(wdh);
	}
	std::vector< std::vector<ImagePixel> >::iterator row;
	std::vector<ImagePixel>::iterator col;
	std::vector<ImagePixel>::iterator pixel = pixels.begin();;

	for (row = pixels2D.begin(); row != pixels2D.end(); row++) {
	    for (col = row->begin(); col != row->end(); col++) {
	  	 	(*col) = (*pixel);
            pixel++;
		} 
	}
}
