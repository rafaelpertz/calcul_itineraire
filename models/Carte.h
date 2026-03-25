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
		
		
};
#endif
