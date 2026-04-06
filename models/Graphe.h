#ifndef GRAPHE_H
#define GRAPHE_H

#include "Carte.h"
#include <vector>
#include <map>

class Graphe {
	public:
		Graphe() {}
		Graphe(const Carte& carte);

		std::vector<int> voisins(int indice);

		int distance(int i1, int i2);

		std::vector<int> cheminLePlusCourt(int i_depart, int i_arrivee);

		int distanceChemin(const std::vector<int>& chemin);

		void afficheChemin(const std::vector<int>& chemin);

		std::vector<int> dernierChemin;

	private:
		std::vector<Waypoint> waypoints;
		std::vector<Route>    routes;

		std::map<int, std::vector<std::pair<int, int>>> adjacence;
};
#endif
