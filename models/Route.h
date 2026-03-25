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
		Route(int debut=0, int fin=0, int distance=0): i_deb(debut), i_fin(fin), distance(distance){}
		Route(){}
		int getIDeb() const{
			return deb;
		}
		int getIFin() const{
			return fin;
		}
		int getDistance() const{
			return distance;
		}
		std::string getInfos()const{
			std::ostringstream texte;
			texte << "Route de "<< i_deb << " à " << i_fin << "(distance : " << distance << \n;
			return texte.str();
		}
		void affiche() const{
			std::cout << "Route de "<< i_deb << " à " << i_fin << "(distance : " << distance << \n;
		}
};
#endif
