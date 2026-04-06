#ifndef CONTOUR_H
#define CONTOUR_H

#include <iostream>
#include <vector>
#include "Point.h"

class Contour {
	private:
		std::vector<Point> points;
	public:
		Contour() {}
		Contour(std::vector<Point> points) : points(points) {}
		~Contour() {}

		std::vector<Point> getPoints() const {
		    return points;
		}

		void ajoutUnPoint(const Point& pt) {
		    points.push_back(pt);
		}
};

#endif
