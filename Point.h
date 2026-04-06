#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

class Point {
	private :
		int num;
		float lon;
		float lat;
	public : 
		Point ();
		float getLon();
		float getLat();
};
#endif
