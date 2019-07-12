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
#include "Vertex.h"
#include "Matrix.h"
#include "Ray.h"
#include <math.h>       /* sqrt */

Ray::Ray() {}
Ray::Ray(Camera cam, ImagePixel pixel) {
	D = (pixel.pixpt - cam.FP);
	D = D % Matrix::vectorLength(D) ;
	L = pixel.pixpt;
}
