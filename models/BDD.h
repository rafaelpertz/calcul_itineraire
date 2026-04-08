#ifndef BDD_H
#define BDD_H

#include <iostream>
#include <string>
#include <vector>
#include <clocale>
#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>

#include "Carte.h"

/**
 * @class BDD
 * @brief Gère la connexion à la base de données MySQL et le chargement
 *        de toutes les données géographiques (contour, waypoints, villes, routes)
 *        pour construire un objet Carte.
 */
class BDD {
	public:
		/**
		 * @brief Constructeur : ouvre la connexion MySQL et charge toutes les données
		 *        pour construire la Carte.
		 * @param host   Adresse du serveur MySQL
		 * @param nomBDD Nom de la base de données
		 * @param login  Identifiant de connexion
		 * @param pwd    Mot de passe
		 */
		BDD(std::string host, std::string nomBDD, std::string login, std::string pwd);

		/// @brief Destructeur : ferme et libère la connexion à la base de données.
		~BDD();

		/// @brief Lit les points du contour depuis la table `contour` et les insère dans l'objet Contour.
		void readContourFromDb(Contour& contour);

		/// @brief Lit les waypoints depuis la table `waypoint` et les insère dans le vecteur.
		void readWaypointsFromDb(std::vector<Waypoint>& waypoints);

		/// @brief Lit les villes depuis la table `ville` (avec jointure sur `waypoint` pour les coordonnées).
		void readVilleFromDb(std::vector<Ville>& villes);

		/**
		 * @brief Lit les routes depuis la table `route` et résout les noms en indices de waypoints.
		 * @param routes    Vecteur de routes à remplir
		 * @param waypoints Vecteur de waypoints déjà chargés (pour résolution des indices)
		 */
		void readRouteFromDb(std::vector<Route>& routes, std::vector<Waypoint>& waypoints);

		/**
		 * @brief Recherche l'indice d'un waypoint par son nom dans le vecteur de waypoints.
		 * @param nom       Nom du waypoint recherché
		 * @param waypoints Vecteur de waypoints dans lequel chercher
		 * @return Indice du waypoint trouvé, ou -1 si absent
		 */
		int findRouteIndex(std::string nom, std::vector<Waypoint>& waypoints);

		/// @brief Retourne la carte construite depuis la base de données.
		Carte getCarte() { return carte; }

	private:
		sql::Connection* con; ///< Pointeur vers la connexion MySQL active
		Carte carte;          ///< Carte construite à partir des données lues en base
};

#endif
