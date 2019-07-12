#ifndef Material_H
#define Material_H
#include <vector>
class Material {
	public:

		Material(double ka0, double ka1, double ka2, double kd0, double kd1, double kd2, double ks0, double ks1, double ks2, double kr0, double kr1, double kr2);
		Material();
		std::vector<double> ka;
		std::vector<double> kd;
		std::vector<double> ks;
		std::vector<double> kr;

};	

#endif // Material_H