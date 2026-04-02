#ifndef ROUTE_H
#define ROUTE_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

class Route {
	private :
		int i_deb;
		int i_fin;
		int distance;
	public :
		Route(char debut='', char fin='', int distance=0): i_deb(debut), i_fin(fin), distance(distance){}
		Route(){}
		int getIDeb() const{
			return i_deb;
		}
		int getIFin() const{
			return i_fin;
		}
		int getDistance() const{
			return distance;
		}
		std::string getInfos()const{
			std::ostringstream texte;
			texte << "Route de "<< i_deb << " à " << i_fin << "(distance : " << distance << "\n";
			return texte.str();
		}
		void affiche() const{
			std::cout << "Route de "<< i_deb << " à " << i_fin << "(distance : " << distance << "\n";
		}
};
#endif
