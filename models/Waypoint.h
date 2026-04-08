#ifndef WAYPOINT_H
#define WAYPOINT_H

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

/**
 * @class Waypoint
 * @brief Représente un point de passage nommé sur la carte, associé à des coordonnées géographiques.
 *        Classe de base pour Ville (héritage).
 */
class Waypoint {
	protected :
		std::string nom; ///< Nom du waypoint
		float lon;       ///< Longitude en degrés décimaux
		float lat;       ///< Latitude en degrés décimaux

	public :
		/**
		 * @brief Constructeur d'un waypoint.
		 * @param nom Nom du point de passage
		 * @param lon Longitude en degrés décimaux
		 * @param lat Latitude en degrés décimaux
		 */
		Waypoint (std::string nom="", float lon=0, float lat=0): nom(nom), lon(lon), lat(lat) {}
		~Waypoint(){}

		/// @brief Retourne le nom du waypoint.
		std::string getNom() const { return nom; }

		/// @brief Retourne la longitude du waypoint.
		float getLon() const { return lon; }

		/// @brief Retourne la latitude du waypoint.
		float getLat() const { return lat; }

		/**
		 * @brief Retourne une chaîne formatée avec le nom et les coordonnées.
		 * @return Informations du waypoint sous forme de texte
		 */
		std::string getInfos() const {
			std::ostringstream texte;
			texte << nom << " : lat =" << lat << "; lon =" << lon;
			return texte.str();
		}

		/// @brief Affiche le nom et les coordonnées du waypoint dans la console.
		void affiche() const {
			std::cout << nom << " Longitude: " << lon << " Latitude: " << lat << "\n";
		}

		/**
		 * @brief Indique si ce waypoint est une ville (méthode virtuelle polymorphique).
		 *        Retourne false par défaut ; surchargée à true dans la classe Ville.
		 * @return false
		 */
		virtual bool isVille() const { return false; }
};
#endif
