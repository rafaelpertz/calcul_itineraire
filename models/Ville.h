#ifndef VILLE_H
#define VILLE_H

#include <iostream>
#include <string>
#include <sstream>
#include "Waypoint.h"

class Ville : public Waypoint {
	private:
		std::string code_postal;
		int nb_habitants;
		std::string site;
	public:
		Ville(std::string nom = "", std::string code_postal = "", int nb_habitants = 0,
		      std::string site = "", float lon = 0, float lat = 0)
		    : Waypoint(nom, lon, lat), code_postal(code_postal),
		      nb_habitants(nb_habitants), site(site) {}

		~Ville() {}

		bool isVille() const override {
			return true;
		}

		std::string getInfos() const {
			std::ostringstream texte;
			texte << getNom() << " , " << code_postal << " , " << site << " , " << nb_habitants << " habitants\n";
			return texte.str();
		}

		void affiche() const {
			std::cout << getNom() << " , " << code_postal << " , "<< site << " , " << nb_habitants << " habitants\n";
		}
};

#endif
