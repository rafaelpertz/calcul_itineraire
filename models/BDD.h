#ifndef BDD_H
#define BDD_H

#include <iostream>
#include <string>
#include <vector>
#include <clocale>
#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include "Carte.h"

class BDD {
	public:
		BDD(std::string host, std::string nomBDD, std::string login, std::string pwd);
		~BDD();

		void readContourFromDb(Contour& contour);
		void readWaypointsFromDb(std::vector<Waypoint>& waypoints);
		void readVilleFromDb(std::vector<Ville>& villes);
		void readRouteFromDb(std::vector<Route>& routes, std::vector<Waypoint>& waypoints);

		int findRouteIndex(std::string nom, std::vector<Waypoint>& waypoints);

		Carte getCarte() { return carte; }

	private:
		sql::Connection* con;
		Carte carte;
};

#endif
