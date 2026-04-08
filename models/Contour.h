#ifndef CONTOUR_H
#define CONTOUR_H

#include <iostream>
#include <vector>
#include "Point.h"

/**
 * @class Contour
 * @brief Représente le contour géographique de la carte sous forme d'un polygone
 *        défini par une liste ordonnée de points géographiques.
 */
class Contour {
	private:
		std::vector<Point> points; ///< Liste ordonnée des points formant le contour

	public:
		/// @brief Constructeur par défaut.
		Contour() {}

		/**
		 * @brief Constructeur avec une liste de points existante.
		 * @param points Vecteur de points géographiques
		 */
		Contour(std::vector<Point> points) : points(points) {}
		~Contour() {}

		/**
		 * @brief Retourne la liste des points du contour.
		 * @return Vecteur de points géographiques
		 */
		std::vector<Point> getPoints() const { return points; }

		/**
		 * @brief Ajoute un point à la fin du contour.
		 * @param pt Point géographique à ajouter
		 */
		void ajoutUnPoint(const Point& pt) { points.push_back(pt); }
};

#endif
