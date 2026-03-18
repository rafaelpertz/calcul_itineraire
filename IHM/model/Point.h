#ifndef POINT_H
#define POINT_H

#include <iostream>
#include <string>
#include <iomanip>
#include <sstream>

class Point {
	private :
		int id_plan;
		std::string nom_mur;
		int num;
		float x, y;
	public :
		Point (int id=0, std::string nom="", int num=0, float x=0, float y=0): id_plan(id),nom_mur(nom), num(num), x(x), y(y){
		}
		/*string getNomMur() const{
			return nom_mur;
		}*/
		int getNum() const{
			return num;
		}
		float getX() const{
			return x;
		}
		float getY() const{
			return y;
		}
		void setX(float x){
			this->x = x;
		}
		void setY(float y){
			this->y = y;
		}
		std::string getInfos() const {
			std::ostringstream texte;
			texte << "Point " << std::setprecision(2) << std::fixed 
					<< num << "\n(" << x << "," << y << ")";
			return texte.str();
		}
		void affiche() const{
				std::cout << "\tpoint " << num << " (" << x << "," << y << ")\n";
		}

};
#endif
