#include "SceneCarte.h"

// Constructeur : initialise la scène et dessine tous les éléments de la carte
SceneCarte::SceneCarte(Carte& carte) {
	this->carte  = carte;
	this->graphe = Graphe(this->carte);

	drawContour(carte.getContour());
	drawWaypoint(carte.getWaypoints());
	drawVille(carte.getVilles());
	drawRoute(carte.getRoutes());
}

// Dessine le contour géographique (polygone de la carte)
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

// Dessine toutes les routes (segments entre waypoints)
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

// Dessine les villes (petits carrés gris avec tooltip)
void SceneCarte::drawVille(std::vector<Ville> villes) {
	for (auto& ville : villes) {
		double x, y;
		latLonToXY(ville.getLon(), ville.getLat(), x, y);

		QGraphicsRectItem* item = new QGraphicsRectItem(x - 2.5, y - 2.5, 5, 5);
		item->setPen(QPen(Qt::black, 1));
		item->setBrush(QBrush(Qt::gray));
		item->setToolTip(QString::fromStdString(ville.getInfos()));
		item->setData(0, QString::fromStdString(ville.getNom()));
		this->addItem(item);
	}
}

// Dessine les waypoints (petits cercles noirs avec tooltip)
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

// Dessine le chemin le plus court en rouge
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

// Conversion latitude/longitude → coordonnées x/y (projection Mercator, en km)
void SceneCarte::latLonToXY(float lon, float lat, double& x, double& y) {
    const double R = 6378137.0;
    double lonRad = lon * M_PI / 180.0;
    double latRad = lat * M_PI / 180.0;

    x = R * lonRad / 1000.0;
    y = R * log(tan(M_PI / 4.0 + latRad / 2.0)) / 1000.0;
}

// Retourne true si le nom correspond à une ville de la carte
bool SceneCarte::isVille(std::string nom) {
    for (const auto& ville : this->carte.getVilles()) {
        if (ville.getNom() == nom)
            return true;
    }
    return false;
}

// Retourne l'indice d'un waypoint dans le tableau à partir de son nom
int SceneCarte::findWaypointIndex(const std::string& nom) {
    std::vector<Waypoint> waypoints = this->carte.getWaypoints();
    for (int i = 0; i < (int)waypoints.size(); i++) {
        if (waypoints[i].getNom() == nom)
            return i;
    }
    return -1;
}

// Retourne la distance du dernier chemin calculé
int SceneCarte::getDistance() {
    return this->graphe.distanceChemin(this->graphe.dernierChemin);
}

// Calcule et dessine le plus court chemin entre deux villes
void SceneCarte::computeAndDrawShortestPath(const std::string& depart, const std::string& arrivee) {
    if (!isVille(depart) || !isVille(arrivee)) {
        // On signale la ville invalide à l'interface
        std::string invalide = !isVille(depart) ? depart : arrivee;
        emit signalInvalidVille(invalide);
        return;
    }

    int i_depart  = findWaypointIndex(depart);
    int i_arrivee = findWaypointIndex(arrivee);

    std::vector<int> chemin = this->graphe.cheminLePlusCourt(i_depart, i_arrivee);
    this->graphe.afficheChemin(chemin);

    // Redessiner toute la carte puis le chemin par-dessus
    this->clear();
    drawContour(carte.getContour());
    drawWaypoint(carte.getWaypoints());
    drawVille(carte.getVilles());
    drawRoute(carte.getRoutes());
    drawShortestPath(chemin);
}
