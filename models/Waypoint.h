#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

class Waypoint {
	protected :
		std::string nom;
		float lon;
		float lat;
	public : 
		Waypoint (std::string nom="", float longitude=0, float latitude=0): nom(nom), lon(longitude), lat(latitude) {}
		Waypoint(){}
		
		float getLon() const{
			return lon;
		}
		float getLat() const{
			return lat;
		}
		std::string getInfos(); // il y a surement des trucs à rajouter
		void affiche() const{
			//ecrire la fonction
		}
};
#endif
