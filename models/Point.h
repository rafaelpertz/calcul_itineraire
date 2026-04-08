#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

/**
 * @class Point
 * @brief Représente un point géographique identifié par un numéro, une latitude et une longitude.
 *        Utilisé pour définir le contour géographique de la carte.
 */
class Point {
	private :
		int num;    ///< Identifiant numérique du point (numéro d'ordre dans le contour)
		float lon;  ///< Longitude en degrés décimaux
		float lat;  ///< Latitude en degrés décimaux

	public :
		/**
		 * @brief Constructeur d'un point géographique.
		 * @param num Numéro d'ordre du point
		 * @param lat Latitude en degrés décimaux
		 * @param lon Longitude en degrés décimaux
		 */
		Point (int num, float lat, float lon)
			: num(num), lon(lon), lat(lat) {}

		~Point (){}

		/**
		 * @brief Retourne la longitude du point.
		 * @return Longitude en degrés décimaux
		 */
		float getLon() const {
			return lon;
		}

		/**
		 * @brief Retourne la latitude du point.
		 * @return Latitude en degrés décimaux
		 */
		float getLat() const {
			return lat;
		}
};

#endif
