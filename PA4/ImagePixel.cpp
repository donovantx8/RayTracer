#include "ImagePixel.h"
#include "Intersection.h"
#include "Ray.h"
#include "Matrix.h"
#include <stdlib.h>
#include <math.h>
#include <vector> 
#define F2B(f) ((f) >= 1.0 ? 255 : (int)((f)*256.0))

ImagePixel::ImagePixel() {
	
}


ImagePixel::ImagePixel(Camera cam, int x, int y){

	Matrix blank;
	double px = (double) x / (cam.wdh -1) * (cam.rgt-cam.lft) + cam.lft;
	double py = (double) y / (cam.hgt -1) * (cam.top-cam.bot) + cam.bot;

	pixpt = cam.FP + ((-cam.focalLength) * cam.WV) + (px * cam.UV) + (-py * cam.VV);

	
}

std::vector<double> ImagePixel::colorPixel(std::vector<Light> sources, Camera cam, Material mat, std::vector<double> rayL, std::vector<double> rayD, std::vector<double> accum, std::vector<double> refatt, int level) {
	std::vector<Light>::iterator light_itr;
	std::vector<double> color;
	color.push_back(cam.ambient.at(0) * mat.ka.at(0));
	color.push_back(cam.ambient.at(1) * mat.ka.at(1));
	color.push_back(cam.ambient.at(2) * mat.ka.at(2));
	std::vector<double> snrm;

	if (isSphere) {
		snrm = model.Model::calculateSurfaceNormal(ections, center);

	} else {
		snrm = model.Model::calculateSurfaceNormal(face);
	}
	for (light_itr = sources.begin(); light_itr != sources.end(); light_itr++) {
			
			std::vector<double> ptL = (*light_itr).p;
			std::vector<double> emL = (*light_itr).e;

			std::vector<double> toL = ptL - ections;
			toL = toL % Matrix::vectorLength(toL);

			double sndottol = snrm & toL;
	//		Matrix::printVector(snrm);
			if ((sndottol) > 0) {				
			
				/*if (X==29 && Y ==48) {
					Matrix::printVector(color);
					Matrix::printVector(snrm);
					Matrix::printVector(cam.ambient);
					cout << sndottol << endl;
					Matrix::printVector(rayD);
					Matrix::printVector(rayL);
					
				}	*/	
		//		Matrix::printVector(ections);
			//	printf("['%f', '%f', '%f']\n",ections.at(0),ections.at(1),ections.at(2));
				color.at(0) = color.at(0) + (mat.kd.at(0) * emL.at(0) * sndottol); 
				color.at(1) = color.at(1) + (mat.kd.at(1) * emL.at(1) * sndottol);
				color.at(2) = color.at(2) + (mat.kd.at(2) * emL.at(2) * sndottol);
			//	Matrix::printVector(color);

				std::vector<double> toC = rayL - ections;
				
				if (toC.at(0) != 0 && toC.at(1) != 0 && toC.at(2) != 0) {
					toC = toC % Matrix::vectorLength(toC);

				}

				std::vector<double> spR = (2 * sndottol * snrm) - toL;
				/*if (X==29 && Y ==48) {
					
					Matrix::printVector(mat.ka);
					Matrix::printVector(mat.kd);
					Matrix::printVector(mat.ks);
					Matrix::printVector(toC);
					Matrix::printVector(toL);
					Matrix::printVector(spR);
					Matrix::printVector(ptL);
					Matrix::printVector(emL);
					Matrix::printVector(color);
					cout << (pow((toC & spR),16.0)) << endl;
					
				}	*/	
				spR = spR % Matrix::vectorLength(spR);
				color.at(0) += mat.ks.at(0) * emL.at(0) * pow((toC & spR),16.0); 
				color.at(1) += mat.ks.at(1) * emL.at(1) * pow((toC & spR),16.0); 
				color.at(2) += mat.ks.at(2) * emL.at(2) * pow((toC & spR),16.0); 
				/*if (X==29 && Y ==48) {
					Matrix::printVector(color);
				}	*/
				
				
				
			}
	}
	accum.at(0) += (refatt.at(0) * color.at(0));
	accum.at(1) += (refatt.at(1) * color.at(1));
	accum.at(2) += (refatt.at(2) * color.at(2));
	if (level > 0) {
		std::vector<Model>::iterator model_itr;
		double tmin = std::numeric_limits<double>::max();
		std::vector<double> uinv = -1 * rayD;
		std::vector<double> refR = ((2 * (uinv & snrm) * snrm) - uinv);
		refR = refR % Matrix::vectorLength(refR);			
		Ray rayR;
		rayR.L = ections;
		rayR.D = refR;
		std::vector<double> bestL;
		std::vector<double> bestD = refR;
		std::vector<double> bestP;
		std::vector<double> bestC;
		Model bestS;
		for (model_itr = models.begin(); model_itr != models.end(); model_itr++) {
			std::vector<double> inters;
			std::vector<double> solutions = Intersection::checkForSphereIntersections(rayR,(*model_itr));
			if (solutions.at(0) != -1 && solutions.at(1) != -1 && solutions.at(2) != -1) {
				if (solutions.at(3) < tmin && solutions.at(3) > .00001) {
					isSphere = true;
					tmin = solutions.at(3);
					inters.push_back(solutions.at(0));
					inters.push_back(solutions.at(1));
					inters.push_back(solutions.at(2));
					bestP = inters; 
					bestC = (*model_itr).center;
					bestS = (*model_itr);
				}
					
			}
		}
		
		if (tmin != std::numeric_limits<double>::max()) {
			std::vector<double> pass = ections;
			pass.at(0) = mat.kr.at(0) * refatt.at(0);
			pass.at(1) = mat.kr.at(1) * refatt.at(1);
			pass.at(2) = mat.kr.at(2) * refatt.at(2);
			ImagePixel recur = (*this);
			recur.center = bestC;
			recur.ections = bestP;
			Material pm = bestS.mat;
			accum = recur.colorPixel(sources, cam, pm, bestP, bestD, accum, pass, (level-1));
		}
	}
	return accum;
}

