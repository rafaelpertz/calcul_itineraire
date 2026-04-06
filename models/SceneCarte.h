#ifndef SCENECARTE_H
#define SCENECARTE_H

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QColor>
#include <iostream>
#include <cmath>

#include "Graphe.h"
#include "Carte.h"

class SceneCarte : public QGraphicsScene {
	Q_OBJECT

public:
	SceneCarte(Carte& carte);
	~SceneCarte() {}

	void drawContour(Contour contour);
	void drawRoute(std::vector<Route> routes);
	void drawWaypoint(std::vector<Waypoint> waypoints);
	void drawVille(std::vector<Ville> villes);
	void drawShortestPath(std::vector<int> chemin);

	int  getDistance();
	void computeAndDrawShortestPath(const std::string& depart, const std::string& arrivee);

signals:
	void signalInvalidVille(const std::string& nom_ville);

private:
	Carte  carte;
	Graphe graphe;

	void latLonToXY(float lon, float lat, double& x, double& y);
	bool isVille(std::string nom);

	int findWaypointIndex(const std::string& nom);
};

#endif
