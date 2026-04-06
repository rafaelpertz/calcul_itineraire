#include "Graphe.h"
#include <limits>
#include <algorithm>
#include <iostream>

Graphe::Graphe(const Carte& carte) {
	waypoints = carte.getWaypoints();
	routes = carte.getRoutes();

	for (int i = 0; i < (int)routes.size(); i++) {
		int i_deb = routes[i].getIDeb();
		int i_fin = routes[i].getIFin();
		int dist  = routes[i].getDistance();

		adjacence[i_deb].push_back({i_fin, dist});
		adjacence[i_fin].push_back({i_deb, dist});
	}
}

std::vector<int> Graphe::voisins(int indice) {
	std::vector<int> resultat;
	for (auto& voisin : adjacence[indice]) {
		resultat.push_back(voisin.first);
	}
	return resultat;
}

int Graphe::distance(int i1, int i2) {
	for (auto& voisin : adjacence[i1]) {
		if (voisin.first == i2)
			return voisin.second;
	}
	return -1;
}

std::vector<int> Graphe::cheminLePlusCourt(int i_depart, int i_arrivee) {
	int n = (int)waypoints.size();

	std::vector<double> dist(n, std::numeric_limits<double>::infinity());
	std::vector<int> precedent(n, -1);
	std::vector<bool> visite(n, false);

	dist[i_depart] = 0;

	for (int etape = 0; etape < n; etape++) {
		int u = -1;
		for (int j = 0; j < n; j++) {
		    if (!visite[j] && (u == -1 || dist[j] < dist[u]))
			u = j;
		}

		if (u == -1 || dist[u] == std::numeric_limits<double>::infinity())
		break;

		visite[u] = true;

		for (auto& voisin : adjacence[u]) {
			int v    = voisin.first;
			int d    = voisin.second;
			if (dist[u] + d < dist[v]) {
				dist[v]     = dist[u] + d;
				precedent[v] = u;
			}
		}
	}

	std::vector<int> chemin;
	int courant = i_arrivee;

	while (courant != -1) {
		chemin.push_back(courant);
		courant = precedent[courant];
	}

	std::reverse(chemin.begin(), chemin.end());

	if (chemin.front() != i_depart) {
		chemin.clear();
	}

	dernierChemin = chemin;
	return chemin;
}

int Graphe::distanceChemin(const std::vector<int>& chemin) {
	int total = 0;
	for (int i = 0; i < (int)chemin.size() - 1; i++) {
		total += distance(chemin[i], chemin[i + 1]);
	}
	return total;
}

void Graphe::afficheChemin(const std::vector<int>& chemin) {
	std::cout << "Itineraire : ";
	for (int i = 0; i < (int)chemin.size(); i++) {
		std::cout << waypoints[chemin[i]].getNom();
		if (i < (int)chemin.size() - 1)
			std::cout << " => ";
	}
	std::cout << std::endl;
	std::cout << "Distance totale : " << distanceChemin(chemin) << " km" << std::endl;
}
