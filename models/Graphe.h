#ifndef GRAPHE_H
#define GRAPHE_H

#include "Carte.h"
#include <vector>
#include <map>

class Graphe {
	public:
		Graphe() {}// constructeur par défaut (nécessaire pour SceneCarte)
		Graphe(const Carte& carte);

		// Retourne les indices des waypoints voisins d'un waypoint
		std::vector<int> voisins(int indice);

		// Retourne la distance entre deux waypoints voisins (en km)
		int distance(int i1, int i2);

		// Calcul du plus court chemin par Dijkstra
		// Retourne la liste ordonnée des indices de waypoints à suivre
		std::vector<int> cheminLePlusCourt(int i_depart, int i_arrivee);

		// Calcule la distance totale d'un chemin
		int distanceChemin(const std::vector<int>& chemin);

		// Affiche le chemin dans la console
		void afficheChemin(const std::vector<int>& chemin);

		// Dernier chemin calculé (accessible depuis SceneCarte pour getDistance())
		std::vector<int> dernierChemin;

	private:
		std::vector<Waypoint> waypoints; // <-- par valeur, cohérent avec Carte
		std::vector<Route>    routes;

		// Liste d'adjacence : adjacence[i] = liste de paires (indice_voisin, distance)
		std::map<int, std::vector<std::pair<int, int>>> adjacence;
};
#endif // GRAPHE_H
