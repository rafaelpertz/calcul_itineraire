#include "Graphe.h"
#include <limits>
#include <algorithm>
#include <iostream>

/**
 * @brief Constructeur : construit la liste d'adjacence bidirectionnelle
 *        en parcourant toutes les routes de la carte.
 */
Graphe::Graphe(const Carte& carte) {
	waypoints = carte.getWaypoints();
	routes = carte.getRoutes();

	for (int i = 0; i < (int)routes.size(); i++) {
		int i_deb = routes[i].getIDeb();
		int i_fin = routes[i].getIFin();
		int dist  = routes[i].getDistance();

		// Ajout de l'arc dans les deux sens (graphe non orienté)
		adjacence[i_deb].push_back({i_fin, dist});
		adjacence[i_fin].push_back({i_deb, dist});
	}
}

/**
 * @brief Retourne les indices des waypoints voisins d'un nœud donné.
 */
std::vector<int> Graphe::voisins(int indice) {
	std::vector<int> resultat;
	for (auto& voisin : adjacence[indice]) {
		resultat.push_back(voisin.first);
	}
	return resultat;
}

/**
 * @brief Retourne la distance entre deux waypoints directement connectés.
 *        Retourne -1 s'ils ne sont pas voisins.
 */
int Graphe::distance(int i1, int i2) {
	for (auto& voisin : adjacence[i1]) {
		if (voisin.first == i2)
			return voisin.second;
	}
	return -1;
}

/**
 * @brief Implémentation de l'algorithme de Dijkstra pour trouver le chemin
 *        le plus court entre deux waypoints.
 *        Le chemin résultant est stocké dans dernierChemin.
 */
std::vector<int> Graphe::cheminLePlusCourt(int i_depart, int i_arrivee) {
	int n = (int)waypoints.size();

	std::vector<double> dist(n, std::numeric_limits<double>::infinity()); // Distances initialisées à l'infini
	std::vector<int> precedent(n, -1);   // Tableau des prédécesseurs pour reconstruction du chemin
	std::vector<bool> visite(n, false);  // Marqueurs de nœuds visités

	dist[i_depart] = 0;

	for (int etape = 0; etape < n; etape++) {
		// Sélection du nœud non visité ayant la plus petite distance courante
		int u = -1;
		for (int j = 0; j < n; j++) {
		    if (!visite[j] && (u == -1 || dist[j] < dist[u]))
			u = j;
		}

		// Arrêt si aucun nœud accessible restant
		if (u == -1 || dist[u] == std::numeric_limits<double>::infinity())
		break;

		visite[u] = true;

		// Mise à jour des distances pour chaque voisin du nœud courant
		for (auto& voisin : adjacence[u]) {
			int v    = voisin.first;
			int d    = voisin.second;
			if (dist[u] + d < dist[v]) {
				dist[v]      = dist[u] + d;
				precedent[v] = u;
			}
		}
	}

	// Reconstruction du chemin en remontant les prédécesseurs depuis l'arrivée
	std::vector<int> chemin;
	int courant = i_arrivee;

	while (courant != -1) {
		chemin.push_back(courant);
		courant = precedent[courant];
	}

	std::reverse(chemin.begin(), chemin.end());

	// Si le chemin ne commence pas au départ, aucun chemin n'existe
	if (chemin.front() != i_depart) {
		chemin.clear();
	}

	dernierChemin = chemin;
	return chemin;
}

/**
 * @brief Calcule la distance totale d'un chemin en sommant les distances entre chaque paire de nœuds consécutifs.
 */
int Graphe::distanceChemin(const std::vector<int>& chemin) {
	int total = 0;
	for (int i = 0; i < (int)chemin.size() - 1; i++) {
		total += distance(chemin[i], chemin[i + 1]);
	}
	return total;
}

/**
 * @brief Affiche dans la console la séquence de waypoints du chemin et la distance totale.
 */
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
