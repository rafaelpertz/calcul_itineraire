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
		Waypoint (std::string nom="", float lon=0, float lat=0): nom(nom), lon(lon), lat(lat) {}
		~Waypoint(){}
		
		float getLon() const{
			return lon;}
			
		float getLat() const{
			return lat;}
			
		std::string getInfos() const{
			std::ostringstream texte;
			texte << nom << " : lat =" << lat << "; lon =" << lon;
			return texte.str();
		}
		
		void affiche() const{
			std::cout << nom << " Longitude: " << lon << " Latitude: " << lat << "\n";
		}
		
		virtual bool isVille() const {
			return false;}
};
#endif
