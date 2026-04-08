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

/**
 * @class SceneCarte
 * @brief Scène Qt affichant graphiquement la carte : contour, waypoints, villes, routes
 *        et le chemin le plus court calculé par le graphe.
 *        Hérite de QGraphicsScene pour s'intégrer dans un QGraphicsView.
 */
class SceneCarte : public QGraphicsScene {
	Q_OBJECT

public:
	/**
	 * @brief Constructeur : initialise la scène à partir d'une carte et dessine tous ses éléments.
	 * @param carte Référence vers la carte à afficher
	 */
	SceneCarte(Carte& carte);
	~SceneCarte() {}

	/// @brief Dessine le contour géographique de la carte sous forme de polygone vert.
	void drawContour(Contour contour);

	/// @brief Dessine toutes les routes sous forme de segments noirs.
	void drawRoute(std::vector<Route> routes);

	/// @brief Dessine tous les waypoints sous forme de petits cercles noirs.
	void drawWaypoint(std::vector<Waypoint> waypoints);

	/// @brief Dessine toutes les villes sous forme de petits carrés gris avec tooltip.
	void drawVille(std::vector<Ville> villes);

	/// @brief Dessine le chemin le plus court sous forme de segments rouges épais.
	void drawShortestPath(std::vector<int> chemin);

	/// @brief Retourne la distance totale du dernier chemin calculé.
	int  getDistance();

	/**
	 * @brief Calcule et affiche le chemin le plus court entre deux villes.
	 *        Émet signalInvalidVille si l'une des villes n'est pas reconnue.
	 * @param depart  Nom de la ville de départ
	 * @param arrivee Nom de la ville d'arrivée
	 */
	void computeAndDrawShortestPath(const std::string& depart, const std::string& arrivee);

signals:
	/**
	 * @brief Signal émis lorsqu'un nom de ville fourni n'existe pas dans la carte.
	 * @param nom_ville Nom de la ville invalide
	 */
	void signalInvalidVille(const std::string& nom_ville);

private:
	Carte  carte;   ///< Copie de la carte affichée
	Graphe graphe;  ///< Graphe construit depuis la carte pour le calcul d'itinéraire

	/**
	 * @brief Convertit des coordonnées géographiques (lon, lat) en coordonnées
	 *        de scène (x, y) via la projection de Mercator.
	 * @param lon Longitude en degrés décimaux
	 * @param lat Latitude en degrés décimaux
	 * @param x   Coordonnée X résultante (en sortie)
	 * @param y   Coordonnée Y résultante (en sortie)
	 */
	void latLonToXY(float lon, float lat, double& x, double& y);

	/// @brief Vérifie si un nom correspond à une ville de la carte.
	bool isVille(std::string nom);

	/**
	 * @brief Recherche l'indice d'un waypoint par son nom.
	 * @return Indice dans le vecteur de waypoints, ou -1 si absent
	 */
	int findWaypointIndex(const std::string& nom);
};

#endif
