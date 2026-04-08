#ifndef GRAPHE_H
#define GRAPHE_H

#include "Carte.h"
#include <vector>
#include <map>

/**
 * @class Graphe
 * @brief Représente le graphe des routes entre waypoints.
 *        Construit une liste d'adjacence à partir d'une Carte et fournit
 *        des algorithmes de recherche de chemin (Dijkstra).
 */
class Graphe {
	public:
		/// @brief Constructeur par défaut.
		Graphe() {}

		/**
		 * @brief Constructeur initialisant le graphe à partir d'une carte.
		 *        Construit la liste d'adjacence bidirectionnelle depuis les routes.
		 * @param carte Carte contenant waypoints et routes
		 */
		Graphe(const Carte& carte);

		/**
		 * @brief Retourne la liste des indices des waypoints voisins d'un nœud.
		 * @param indice Indice du waypoint dans le vecteur de waypoints
		 * @return Vecteur d'indices des voisins
		 */
		std::vector<int> voisins(int indice);

		/**
		 * @brief Retourne la distance entre deux waypoints directement connectés.
		 * @param i1 Indice du premier waypoint
		 * @param i2 Indice du second waypoint
		 * @return Distance en km, ou -1 si les deux waypoints ne sont pas voisins
		 */
		int distance(int i1, int i2);

		/**
		 * @brief Calcule le chemin le plus court entre deux waypoints via l'algorithme de Dijkstra.
		 *        Stocke le résultat dans dernierChemin.
		 * @param i_depart  Indice du waypoint de départ
		 * @param i_arrivee Indice du waypoint d'arrivée
		 * @return Vecteur d'indices représentant le chemin optimal, vide si aucun chemin trouvé
		 */
		std::vector<int> cheminLePlusCourt(int i_depart, int i_arrivee);

		/**
		 * @brief Calcule la distance totale d'un chemin donné.
		 * @param chemin Vecteur d'indices de waypoints formant le chemin
		 * @return Distance totale en kilomètres
		 */
		int distanceChemin(const std::vector<int>& chemin);

		/**
		 * @brief Affiche le chemin et sa distance totale dans la console.
		 * @param chemin Vecteur d'indices de waypoints formant le chemin
		 */
		void afficheChemin(const std::vector<int>& chemin);

		std::vector<int> dernierChemin; ///< Dernier chemin calculé par cheminLePlusCourt

	private:
		std::vector<Waypoint> waypoints; ///< Copie des waypoints de la carte
		std::vector<Route>    routes;    ///< Copie des routes de la carte

		/// @brief Liste d'adjacence : pour chaque indice de waypoint, liste de paires (voisin, distance)
		std::map<int, std::vector<std::pair<int, int>>> adjacence;
};
#endif
