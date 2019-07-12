#include "Light.h"

Light::Light(double x, double y, double z, double R, double G, double B) {
	p.push_back(x);
	p.push_back(y);
	p.push_back(z);
	e.push_back(R);
	e.push_back(G);
	e.push_back(B);
}
