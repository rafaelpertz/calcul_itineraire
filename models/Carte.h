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

/**
 * @class Carte
 * @brief Agrège l'ensemble des données géographiques : contour, waypoints, villes et routes.
 *        Sert de modèle de données central transmis aux autres composants (Graphe, SceneCarte).
 */
class Carte {
	protected:
		Contour contour;                ///< Contour géographique de la carte
		std::vector<Waypoint> waypoints; ///< Liste de tous les points de passage
		std::vector<Ville> villes;       ///< Liste des villes (sous-ensemble des waypoints)
		std::vector<Route> routes;       ///< Liste des routes reliant les waypoints

	public:
		/// @brief Constructeur par défaut.
		Carte() {}

		/**
		 * @brief Constructeur principal initialisant tous les éléments de la carte.
		 * @param contour   Contour géographique
		 * @param waypoints Liste des waypoints
		 * @param villes    Liste des villes
		 * @param routes    Liste des routes
		 */
		Carte(Contour contour, std::vector<Waypoint> waypoints, std::vector<Ville> villes, std::vector<Route> routes)
		    : contour(contour), waypoints(waypoints), villes(villes), routes(routes){}

		~Carte(){}

		/// @brief Retourne le contour géographique de la carte.
		Contour getContour() const { return this->contour; }

		/// @brief Retourne la liste de tous les waypoints.
		std::vector<Waypoint> getWaypoints() const { return this->waypoints; }

		/// @brief Retourne la liste des villes.
		std::vector<Ville> getVilles() const { return this->villes; }

		/// @brief Retourne la liste des routes.
		std::vector<Route> getRoutes() const { return this->routes; }

		/**
		 * @brief Retourne la liste des noms de toutes les villes.
		 * @return Vecteur de chaînes de caractères
		 */
		std::vector<std::string> getNomsVilles() const {
			std::vector<std::string> noms;
			for (const auto& ville : villes)
				noms.push_back(ville.getNom());
			return noms;
		}

		/// @brief Ajoute un waypoint à la carte.
		void addWaypoint(Waypoint waypoint) { this->waypoints.push_back(waypoint); }

		/// @brief Ajoute une ville à la carte.
		void addVille(Ville ville) { this->villes.push_back(ville); }
};
#endif
