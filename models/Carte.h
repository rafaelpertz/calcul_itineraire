#ifndef CARTE_H
#define CARTE_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

#include "Route.h"
#include "Contour.h"
#include "Ville.h"

class Carte {
	protected:
		Contour contour;
		std::vector<Waypoint> waypoints;
		std::vector<Ville> villes;
		std::vector<Route> routes;
	public:
		Carte() {}
		Carte(Contour contour, std::vector<Waypoint> waypoints, std::vector<Ville> villes, std::vector<Route> routes): contour(contour), waypoints(waypoints), villes(villes), routes(routes){}
		
		~Carte(){} 
		
		Contour getContour() const {
			return this->contour;
		}
		
		std::vector<Waypoint> getWaypoints() const {
			return this->waypoints;
		}
		std::vector<Ville> getVilles() const {
			return this->villes;
		}
		std::vector<Route> getRoutes() const {
			return this->routes;
		}

		std::vector<std::string> getNomsVilles() const {
			std::vector<std::string> noms;
			for (const auto& ville : villes)
				noms.push_back(ville.getNom());
			return noms;
		}
		
		void addWaypoint(Waypoint waypoint) {
			this->waypoints.push_back(waypoint);
		}
		void addVille(Ville ville) {
			this->villes.push_back(ville);
		}
		
};
#endif
