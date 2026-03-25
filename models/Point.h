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
		Point (); // est ce qu'il faut rajouter des trucs ici ?
		float getLon() const{
			return lon;
		}
		float getLat() const{
			return lat;
		}
};
#endif
