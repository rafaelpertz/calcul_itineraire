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


};

#endif
