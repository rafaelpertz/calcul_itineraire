#include "BDD.h"

/**
 * @brief Constructeur : établit la connexion MySQL, charge toutes les données
 *        géographiques depuis la base et construit l'objet Carte.
 */
BDD::BDD(std::string host, std::string nomBDD, std::string login, std::string pwd) {
	sql::Driver* driver = get_driver_instance();
	con = driver->connect(host, login, pwd);
	con->setSchema(nomBDD);
	setlocale(LC_ALL, "C"); // Assure la cohérence du formatage des nombres décimaux

	std::vector<Point> points;
	Contour contour(points);
	std::vector<Waypoint> waypoints;
	std::vector<Ville> villes;
	std::vector<Route> routes;

	// Chargement séquentiel : le contour et les waypoints doivent être chargés
	// avant les villes et les routes qui en dépendent
	readContourFromDb(contour);
	readWaypointsFromDb(waypoints);
	readVilleFromDb(villes);
	readRouteFromDb(routes, waypoints);

	this->carte = Carte(contour, waypoints, villes, routes);
}

/**
 * @brief Destructeur : libère la connexion à la base de données.
 */
BDD::~BDD() {
	std::cout << "Fermeture connexion\n";
	delete con;
}

/**
 * @brief Lit la table `contour` et ajoute chaque point au contour géographique.
 */
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

/**
 * @brief Lit la table `waypoint` et remplit le vecteur de waypoints.
 */
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

/**
 * @brief Lit la table `ville` et récupère les coordonnées de chaque ville
 *        via une requête préparée sur la table `waypoint`.
 */
void BDD::readVilleFromDb(std::vector<Ville>& villes) {
	sql::Statement* stmt = con->createStatement();
	sql::ResultSet* res  = stmt->executeQuery("SELECT nom, code_postal, nb_habitants, site FROM ville");

	while (res->next()) {
		std::string nom         = res->getString("nom");
		std::string code_postal = res->getString("code_postal");
		int nb_habitants        = res->getInt("nb_habitants");
		std::string site        = res->getString("site");

		// Récupération des coordonnées géographiques depuis la table waypoint
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

/**
 * @brief Lit la table `route` et convertit les noms de waypoints en indices
 *        via findRouteIndex pour construire les objets Route.
 */
void BDD::readRouteFromDb(std::vector<Route>& routes, std::vector<Waypoint>& waypoints) {
	sql::Statement* stmt = con->createStatement();
	sql::ResultSet* res  = stmt->executeQuery("SELECT nom_debut, nom_fin, distance FROM route");

	while (res->next()) {
		std::string nom_debut = res->getString("nom_debut");
		std::string nom_fin   = res->getString("nom_fin");
		int distance          = res->getInt("distance");

		// Résolution des noms en indices dans le vecteur de waypoints
		int i_deb = findRouteIndex(nom_debut, waypoints);
		int i_fin = findRouteIndex(nom_fin, waypoints);

		routes.push_back(Route(i_deb, i_fin, distance));
	}

	delete res;
	delete stmt;
}

/**
 * @brief Parcourt le vecteur de waypoints pour trouver l'indice correspondant à un nom.
 *        Retourne -1 si le nom n'est pas trouvé.
 */
int BDD::findRouteIndex(std::string nom, std::vector<Waypoint>& waypoints) {
	for (int i = 0; i < (int)waypoints.size(); i++) {
		if (waypoints[i].getNom() == nom)
			return i;
	}
	return -1;
}
