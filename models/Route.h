#ifndef _ROUTE_H_
#define _ROUTE_H_

#include <iostream>
#include <string>
#include <sstream>

/**
 * @class Route
 * @brief Contains a collection of routes
 * 
 * This class contains getters to acces the informations
 * And also display methods
 * 
 * @author Gaspard Vieujean
 * @date March 31, 2025
 */

class Route {
<<<<<<< HEAD
	private :
		int i_deb;
		int i_fin;
		int distance;
	public :
		Route(int debut=0, int fin=0, int distance=0): i_deb(debut), i_fin(fin), distance(distance){}
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
=======
    public:
       // Constructor
       Route(int i_debut, int i_fin, int distance) : i_debut(i_debut), i_fin(i_fin), distance(distance) {}
       
       // Destructor
       ~Route(){};
       
       // Getters
       int getDebut() const {return i_debut;}
       int getFin() const {return i_fin;}
       int getDistance() const {return distance;}
       std::string getInfos() const {
        std::ostringstream texte;
            texte << "Route: " << i_debut << " - " << i_fin
                << " | Distance: " << distance << '\n';
            return texte.str();
        }

        void affiche() const {std::cout << "\t\tRoute\n " << "\n\t Start: " << i_debut << "\n\t End: " << i_fin << "\n\t Distance: " << distance << "\n";}
    
    private:
        int i_debut;
        int i_fin;
        int distance;


>>>>>>> 4355e4b0225edc9f1d42d0e1950ff44f680ccca1
};

#endif
