#ifndef MUR_H
#define MUR_H
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <sstream>

#include "Point.h"

class Mur {
	private :
		int id_plan;
		std::string nom_mur;
		std::string couleur;
		float epaisseur;
		std::vector<Point> points;
	public :
		Mur (int id, std::string nom, std::string couleur, float ep): id_plan(id), nom_mur(nom), couleur(couleur), epaisseur(ep) {
		}
		Mur(){}
		int getIdPlan() const{
			return id_plan;
		}
		std::string getNomMur() const{
			return nom_mur;
		}
		std::string getCouleur() const{
			return couleur;
		}
		float getEpaisseur() const{
			return epaisseur;
		}
		std::vector<Point> &getPoints() {//retour par référence permet de modifier les points
			return points;
		}
		void ajoutUnPoint(const Point& pt) {
			points.push_back(pt);
		}
		std::string getInfos() const{
			std::ostringstream texte;
			texte << "Mur " << std::setprecision(2) << std::fixed 
					<< nom_mur << "\népaisseur : " << epaisseur;
			return texte.str();
		}

		void affiche() const{

			std::cout << "   Mur " << nom_mur << " couleur: " << couleur
				<< " epaisseur: " << epaisseur << "\n";
			for ( auto &pt : points ){
				pt.affiche();
			}
		}

};
#endif
