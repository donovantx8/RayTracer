#include "Material.h"

Material::Material(double ka0, double ka1, double ka2, double kd0, double kd1, double kd2, double ks0, double ks1, double ks2, double kr0, double kr1, double kr2) {
	ka.push_back(ka0);
	ka.push_back(ka1);
	ka.push_back(ka2);
	
	kd.push_back(kd0);
	kd.push_back(kd1);
	kd.push_back(kd2);
	
	ks.push_back(ks0);
	ks.push_back(ks1);
	ks.push_back(ks2);
	
	kr.push_back(kr0);
	kr.push_back(kr1);
	kr.push_back(kr2);
}

Material::Material(){
	
}