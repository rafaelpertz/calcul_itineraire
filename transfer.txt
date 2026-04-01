#ifndef BDD1_H
#define BDD1_H

#include <iostream>
#include <string>
#include <vector>
#include <clocale>

#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/connection.h>

#include "Waypoint.h"
#include "Ville.h"
#include "Route.h"
#include "Contour.h"
#include "Point.h"

class BDD1 {
public:
    BDD1(std::string host, std::string nomBDD, std::string login, std::string pwd);
    BDD1() : con(nullptr) {}
    ~BDD1();

    std::vector<Waypoint> getAllWaypoints();
    std::vector<Ville> getAllVilles();
    std::vector<Route> getAllRoutes();
    Contour getContour();

    // Recherche spécifique
    Ville getVilleByNom(std::string nom);

private:
    sql::Connection *con;
};

#endif
