#include "Graphe.h"
#include "Route.h"


//laf = liste à faire, dans le projet des gars c'est pathIndices. 
//il n'est pas censé être créer ici

int TableauDistance(){
	distance = 0;
	laf = [];
	
	//le but de la fonction va être de connaitre la distance entre chaque ville
	for(i=0; i < laf.size()-1; i++){
		wp1 = laf[i];
		wp2 = laf[i+1];
		
		for(const auto& route: this->routes){
			if(route.getIDeb() == wp1 && route.getIFin() == wp2){
				distance += route.getDistance();
				}
		}
		return distance
	}
}

int PlusCourtChemin(){
	liste = []
}

