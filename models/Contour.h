#ifndef CONTOUR_H
#define CONTOUR_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

#include "Point.h"

class Contour {
	private :
		int num;
		float lon;
		float lat;
		std::vector<Point> points;
	public :
		Mur (){}; 
		std::vector<Point> &getPoints() {
			return points;
		}
		void ajoutUnPoint(const Point& pt){
			points.push_back(pt);
		}
};
#endif
