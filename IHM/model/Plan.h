#ifndef PLAN_H
#define PLAN_H
#include <iostream>
#include <string>
#include <vector>

#include "Mur.h"

class Plan {
	private :
		int id_plan;
		std::string nom_projet;
		int version;
		int orientation; // en degrés (angles positifs vers NW). 0 = Nord 
		std::string date_plan;
		std::vector<Mur> murs;
	public :
		Plan (int id=0, std::string nom="", int vers=0, int orient=0, std::string date=""): id_plan(id), nom_projet(nom), version(vers), orientation(orient), date_plan(date){
		}
		int getIdPlan() const {
			return id_plan;
		}
		std::string getNomProjet() const{
			return nom_projet;
		}
		int getVersion() const {
			return version;
		}
		int getOrientation() const {
			return orientation;
		}
		std::string getDatePlan() const{
			return date_plan;
		}
		std::vector<Mur> &getMurs() { //retour par référence permet de modifier les murs
			return murs;
		}
		void ajoutUnMur(const Mur& mur) {
			murs.push_back(mur);
		}
		void affiche() const{
			std::cout << "Plan " << id_plan << " (" << nom_projet << ") version:" << version << " orientation:" << orientation <<" date: " << date_plan << "\n";
			for ( auto &mur : murs ){
					mur.affiche();
			}
		}

};
#endif
