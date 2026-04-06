#include "BDD.h"

BDD::BDD(std::string host, std::string nomBDD, std::string login, std::string pwd) {
	sql::Driver* driver = get_driver_instance();
	con = driver->connect(host, login, pwd);
	con->setSchema(nomBDD);
	setlocale(LC_ALL, "C");

	std::vector<Point> points;
	Contour contour(points);
	std::vector<Waypoint> waypoints;
	std::vector<Ville> villes;
	std::vector<Route> routes;

	readContourFromDb(contour);
	readWaypointsFromDb(waypoints);
	readVilleFromDb(villes);
	readRouteFromDb(routes, waypoints);

	this->carte = Carte(contour, waypoints, villes, routes);
}

BDD::~BDD() {
	std::cout << "Fermeture connexion\n";
	delete con;
}

void BDD::readContourFromDb(Contour& contour) {
	sql::Statement* stmt = con->createStatement();
	sql::ResultSet* res  = stmt->executeQuery("SELECT num_pt, lat, lon FROM contour");

	while (res->next()) {
		int   num_pt = res->getInt("num_pt");
		float lat    = res->getDouble("lat");
		float lon    = res->getDouble("lon");
		contour.ajoutUnPoint(Point(num_pt, lat, lon));
	}

	delete res;
	delete stmt;
}

void BDD::readWaypointsFromDb(std::vector<Waypoint>& waypoints) {
	sql::Statement* stmt = con->createStatement();
	sql::ResultSet* res  = stmt->executeQuery("SELECT nom, lat, lon FROM waypoint");

	while (res->next()) {
		std::string nom = res->getString("nom");
		float lat       = res->getDouble("lat");
		float lon       = res->getDouble("lon");
		waypoints.push_back(Waypoint(nom, lon, lat));
	}

	delete res;
	delete stmt;
}

void BDD::readVilleFromDb(std::vector<Ville>& villes) {
	sql::Statement* stmt = con->createStatement();
	sql::ResultSet* res  = stmt->executeQuery("SELECT nom, code_postal, nb_habitants, site FROM ville");

	while (res->next()) {
		std::string nom = res->getString("nom");
		std::string code_postal = res->getString("code_postal");
		int nb_habitants = res->getInt("nb_habitants");
		std::string site = res->getString("site");

		sql::PreparedStatement* pstmt = con->prepareStatement("SELECT lat, lon FROM waypoint WHERE nom = ?");
		pstmt->setString(1, nom);
		sql::ResultSet* res2 = pstmt->executeQuery();

		float lat = 0, lon = 0;
		if (res2->next()) {
			lat = res2->getDouble("lat");
			lon = res2->getDouble("lon");
		}

		villes.push_back(Ville(nom, code_postal, nb_habitants, site, lon, lat));

		delete res2;
		delete pstmt;
	}

	delete res;
	delete stmt;
}

void BDD::readRouteFromDb(std::vector<Route>& routes, std::vector<Waypoint>& waypoints) {
	sql::Statement* stmt = con->createStatement();
	sql::ResultSet* res  = stmt->executeQuery("SELECT nom_debut, nom_fin, distance FROM route");

	while (res->next()) {
		std::string nom_debut = res->getString("nom_debut");
		std::string nom_fin   = res->getString("nom_fin");
		int distance          = res->getInt("distance");

		int i_deb = findRouteIndex(nom_debut, waypoints);
		int i_fin = findRouteIndex(nom_fin, waypoints);

		routes.push_back(Route(i_deb, i_fin, distance));
	}

	delete res;
	delete stmt;
}

int BDD::findRouteIndex(std::string nom, std::vector<Waypoint>& waypoints) {
	for (int i = 0; i < (int)waypoints.size(); i++) {
		if (waypoints[i].getNom() == nom)
			return i;
	}
		return -1;
}
