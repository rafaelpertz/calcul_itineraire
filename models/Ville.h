#ifndef VILLE_H
#define VILLE_H

#include <iostream>
#include <string>
#include <sstream>
#include "Waypoint.h"

/**
 * @class Ville
 * @brief Spécialisation de Waypoint représentant une ville.
 *        Ajoute un code postal, un nombre d'habitants et un site web.
 */
class Ville : public Waypoint {
	private:
		std::string code_postal;  ///< Code postal de la ville
		int nb_habitants;         ///< Nombre d'habitants
		std::string site;         ///< URL du site web de la ville

	public:
		/**
		 * @brief Constructeur d'une ville.
		 * @param nom          Nom de la ville
		 * @param code_postal  Code postal
		 * @param nb_habitants Nombre d'habitants
		 * @param site         URL du site web
		 * @param lon          Longitude en degrés décimaux
		 * @param lat          Latitude en degrés décimaux
		 */
		Ville(std::string nom = "", std::string code_postal = "", int nb_habitants = 0,
		      std::string site = "", float lon = 0, float lat = 0)
		    : Waypoint(nom, lon, lat), code_postal(code_postal),
		      nb_habitants(nb_habitants), site(site) {}

		~Ville() {}

		/**
		 * @brief Surcharge de la méthode virtuelle : indique que cet objet est une ville.
		 * @return true
		 */
		bool isVille() const override { return true; }

		/**
		 * @brief Retourne une chaîne formatée avec les informations de la ville.
		 * @return Nom, code postal, site et nombre d'habitants
		 */
		std::string getInfos() const {
			std::ostringstream texte;
			texte << getNom() << " , " << code_postal << " , " << site << " , " << nb_habitants << " habitants\n";
			return texte.str();
		}

		/// @brief Affiche les informations de la ville dans la console.
		void affiche() const {
			std::cout << getNom() << " , " << code_postal << " , "<< site << " , " << nb_habitants << " habitants\n";
		}
};

#endif#ifndef VILLE_H
#define VILLE_H

#include <iostream>
#include <string>
#include <sstream>
#include "Waypoint.h"

class Ville : public Waypoint {
	private:
		std::string code_postal;
		int nb_habitants;
		std::string site;
	public:
		Ville(std::string nom = "", std::string code_postal = "", int nb_habitants = 0,
		      std::string site = "", float lon = 0, float lat = 0)
		    : Waypoint(nom, lon, lat), code_postal(code_postal),
		      nb_habitants(nb_habitants), site(site) {}

		~Ville() {}

		bool isVille() const override {
			return true;
		}

		std::string getInfos() const {
			std::ostringstream texte;
			texte << getNom() << " , " << code_postal << " , " << site << " , " << nb_habitants << " habitants\n";
			return texte.str();
		}

		void affiche() const {
			std::cout << getNom() << " , " << code_postal << " , "<< site << " , " << nb_habitants << " habitants\n";
		}
};

#endif
