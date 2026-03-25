#ifndef VILLE_H
#define VILLE_H

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

#include "Waypoint.h"

class Ville : public Waypoint {
	private :
		std::string code_postal;
		int nb_hbts;
		std::string site;
		std::string nom;
	public : 
		Ville (std::string code_postal = "", int nb_hbts=0, std::string site = "", std::string nom_ville = "", float lon=0, float lat=0): Waypoint(nom_ville, lon, lat), nom(nom_ville), code_postal(code_postal), site(site), nb_hbts(nb_hbts){} 
		
		~Ville(){}
		
		std::string getInfos() const{
			std::ostringstream texte;
			texte << nom << " , " << code_postal << " , " << site << " , " << nb_hbts << " habitants" << "\n";
			return texte.str();
		}
		
		void affiche() const{
			std::cout << nom << " , " << code_postal << " , " << site << " , " << nb_hbts << " habitants \n";
		}
};
#endif
