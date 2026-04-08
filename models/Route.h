#ifndef ROUTE_H
#define ROUTE_H

#include <iostream>
#include <string>
#include <sstream>

/**
 * @class Route
 * @brief Représente une route reliant deux waypoints, identifiés par leurs indices
 *        dans le vecteur de waypoints de la carte, avec une distance en kilomètres.
 */
class Route {
	private:
		int i_deb;    ///< Indice du waypoint de départ dans le vecteur de waypoints
		int i_fin;    ///< Indice du waypoint d'arrivée dans le vecteur de waypoints
		int distance; ///< Distance de la route en kilomètres

	public:
		/**
		 * @brief Constructeur d'une route.
		 * @param debut    Indice du waypoint de départ
		 * @param fin      Indice du waypoint d'arrivée
		 * @param distance Distance en kilomètres
		 */
		Route(int debut=0, int fin=0, int distance=0): i_deb(debut), i_fin(fin), distance(distance){}

		/// @brief Retourne l'indice du waypoint de départ.
		int getIDeb() const { return i_deb; }

		/// @brief Retourne l'indice du waypoint d'arrivée.
		int getIFin() const { return i_fin; }

		/// @brief Retourne la distance de la route en kilomètres.
		int getDistance() const { return distance; }

		/**
		 * @brief Retourne une chaîne formatée décrivant la route.
		 * @return Texte avec indices de départ/arrivée et distance
		 */
		std::string getInfos() const {
		    std::ostringstream texte;
		    texte << "Route de " << i_deb << " à " << i_fin << " (distance : " << distance << " km)\n";
		    return texte.str();
		}

		/// @brief Affiche les informations de la route dans la console.
		void affiche() const {
		    std::cout << "Route de " << i_deb << " à " << i_fin << " (distance : " << distance << " km)\n";
		}
};

#endif
