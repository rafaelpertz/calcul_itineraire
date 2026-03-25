#ifndef VILLE_H
#define VILLE_H

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

class Ville : public Waypoint {
	private :
		std::string code_postal;
		int nb_habitants;
		std::string site;
	public : 
		Ville (std::string cp, int nb_hbts, std::string site): Waypoint(nom, lon, lat), {} // verifier si c'est bon 
		Waypoint(){}
		
		std::string getInfos(); // il y a surement des trucs à rajouter
		void affiche() const{
			//ecrire la fonction
		}
};
#endif
