#ifndef Light_H
#define Light_H
#include <vector>
class Light {
	public:
		Light(double x, double y, double z, double R, double G, double B);

		std::vector<double> p;
		std::vector<double> e;


};	

#endif // Light_H