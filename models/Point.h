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
		Point (int num, float lat, float lon): num(num), lat(lat), lon(lon){}; 
		~Point (){};
		float getLon() const{
			return lon;
		}
		float getLat() const{
			return lat;
		}
};
#endif
