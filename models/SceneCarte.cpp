#include "SceneCarte.h"

/**
 * @brief Constructeur : construit le graphe depuis la carte et dessine tous les éléments.
 */
SceneCarte::SceneCarte(Carte& carte) {
	this->carte  = carte;
	this->graphe = Graphe(this->carte);

	drawContour(carte.getContour());
	drawWaypoint(carte.getWaypoints());
	drawVille(carte.getVilles());
	drawRoute(carte.getRoutes());
}

/**
 * @brief Dessine le contour géographique sous forme de polygone vert avec bordure noire.
 *        Chaque point est converti en coordonnées de scène via latLonToXY.
 */
void SceneCarte::drawContour(Contour contour) {
	QPolygonF polygon;

	for (auto& point : contour.getPoints()) {
		double x, y;
		latLonToXY(point.getLon(), point.getLat(), x, y);
		polygon << QPointF(x, y);
	}

	QGraphicsPolygonItem* item = new QGraphicsPolygonItem(polygon);
	item->setPen(QPen(Qt::black, 1));
	item->setBrush(QBrush(Qt::green));
	this->addItem(item);
}

/**
 * @brief Dessine toutes les routes comme des segments de ligne noirs.
 *        Les positions sont calculées depuis les coordonnées des waypoints de départ et d'arrivée.
 */
void SceneCarte::drawRoute(std::vector<Route> routes) {
	std::vector<Waypoint> waypoints = this->carte.getWaypoints();

	for (auto& route : routes) {
		Waypoint wp1 = waypoints[route.getIDeb()];
		Waypoint wp2 = waypoints[route.getIFin()];

		double x1, y1, x2, y2;
		latLonToXY(wp1.getLon(), wp1.getLat(), x1, y1);
		latLonToXY(wp2.getLon(), wp2.getLat(), x2, y2);

		QGraphicsLineItem* ligne = new QGraphicsLineItem(x1, y1, x2, y2);
		ligne->setPen(QPen(Qt::black, 1));
		this->addItem(ligne);
	}
}

/**
 * @brief Dessine les villes sous forme de petits carrés gris (5x5 px).
 *        Un tooltip avec les informations de la ville est associé à chaque carré.
 *        Le nom de la ville est stocké en data(0) pour une identification future.
 */
void SceneCarte::drawVille(std::vector<Ville> villes) {
	for (auto& ville : villes) {
		double x, y;
		latLonToXY(ville.getLon(), ville.getLat(), x, y);

		QGraphicsRectItem* item = new QGraphicsRectItem(x - 2.5, y - 2.5, 5, 5);
		item->setPen(QPen(Qt::black, 1));
		item->setBrush(QBrush(Qt::gray));
		item->setToolTip(QString::fromStdString(ville.getInfos()));
		item->setData(0, QString::fromStdString(ville.getNom())); // Stockage du nom pour identification
		this->addItem(item);
	}
}

/**
 * @brief Dessine les waypoints sous forme de petits cercles noirs (rayon 2 px).
 *        Un tooltip avec les coordonnées est associé à chaque cercle.
 */
void SceneCarte::drawWaypoint(std::vector<Waypoint> waypoints) {
	for (auto& wp : waypoints) {
		double x, y;
		latLonToXY(wp.getLon(), wp.getLat(), x, y);

		double r = 2;
		QGraphicsEllipseItem* item = new QGraphicsEllipseItem(x - r, y - r, r * 2, r * 2);
		item->setPen(QPen(Qt::black, 1));
		item->setBrush(QBrush(Qt::black));
		item->setToolTip(QString::fromStdString(wp.getInfos()));
		this->addItem(item);
	}
}

/**
 * @brief Dessine le chemin le plus court sous forme de segments rouges épais (2 px).
 *        Parcourt les paires de waypoints consécutifs dans le chemin.
 */
void SceneCarte::drawShortestPath(std::vector<int> chemin) {
	std::vector<Waypoint> waypoints = this->carte.getWaypoints();

	for (int i = 0; i < (int)chemin.size() - 1; i++) {
		Waypoint wp1 = waypoints[chemin[i]];
		Waypoint wp2 = waypoints[chemin[i + 1]];

		double x1, y1, x2, y2;
		latLonToXY(wp1.getLon(), wp1.getLat(), x1, y1);
		latLonToXY(wp2.getLon(), wp2.getLat(), x2, y2);

		QGraphicsLineItem* ligne = new QGraphicsLineItem(x1, y1, x2, y2);
		ligne->setPen(QPen(Qt::red, 2));
		this->addItem(ligne);
	}
}

/**
 * @brief Convertit des coordonnées géographiques en coordonnées de scène
 *        en utilisant la projection de Mercator sphérique.
 *        Le résultat est divisé par 1000 pour obtenir des valeurs exploitables à l'écran.
 */
void SceneCarte::latLonToXY(float lon, float lat, double& x, double& y) {
	const double R = 6378137.0; // Rayon de la Terre en mètres
	double lonRad = lon * M_PI / 180.0;
	double latRad = lat * M_PI / 180.0;

	x = R * lonRad / 1000.0;
	y = R * log(tan(M_PI / 4.0 + latRad / 2.0)) / 1000.0; // Formule de Mercator
}

/**
 * @brief Vérifie si un nom donné correspond à une ville existante dans la carte.
 */
bool SceneCarte::isVille(std::string nom) {
	for (const auto& ville : this->carte.getVilles()) {
		if (ville.getNom() == nom)
			return true;
	}
	return false;
}

/**
 * @brief Recherche et retourne l'indice d'un waypoint par son nom.
 *        Retourne -1 si le waypoint n'est pas trouvé.
 */
int SceneCarte::findWaypointIndex(const std::string& nom) {
	std::vector<Waypoint> waypoints = this->carte.getWaypoints();
	for (int i = 0; i < (int)waypoints.size(); i++) {
		if (waypoints[i].getNom() == nom)
			return i;
	}
	return -1;
}

/// @brief Retourne la distance totale du dernier chemin calculé par le graphe.
int SceneCarte::getDistance() {
	return this->graphe.distanceChemin(this->graphe.dernierChemin);
}

/**
 * @brief Calcule le chemin le plus court entre deux villes et le dessine sur la scène.
 *        Vérifie d'abord la validité des deux noms de villes.
 *        Si une ville est invalide, émet le signal signalInvalidVille.
 *        Redessine entièrement la scène avant d'afficher le nouveau chemin en rouge.
 */
void SceneCarte::computeAndDrawShortestPath(const std::string& depart, const std::string& arrivee) {
	if (!isVille(depart) || !isVille(arrivee)) {
		std::string invalide = !isVille(depart) ? depart : arrivee;
		emit signalInvalidVille(invalide);
		return;
	}

	int i_depart  = findWaypointIndex(depart);
	int i_arrivee = findWaypointIndex(arrivee);

	std::vector<int> chemin = this->graphe.cheminLePlusCourt(i_depart, i_arrivee);
	this->graphe.afficheChemin(chemin);

	// Redessinage complet de la scène avant d'afficher le chemin
	this->clear();
	drawContour(carte.getContour());
	drawWaypoint(carte.getWaypoints());
	drawVille(carte.getVilles());
	drawRoute(carte.getRoutes());
	drawShortestPath(chemin);
}
