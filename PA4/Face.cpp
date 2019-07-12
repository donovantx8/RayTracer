#define Face_H
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
//#include "Face.h"

class Face {
	public:
		/* simple accessors */
		//inline int Minimum() const {return min;}

		/* Mutators */
		//inline void set_Minimum(int value) {min = value;}

		/* Member Variables */
		
		std::vector<Vertex>  vertices; 	// a vector that stores the vertices that compose faces
		int numVertices;

};	
