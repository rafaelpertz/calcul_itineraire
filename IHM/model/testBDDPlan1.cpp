#include <iostream>
#include <vector>
#include <cppconn/exception.h>

#include "Plan.h"
#include "Mur.h"
#include "BDD.h"

int main(void) {

	std::cout << "Lecture base plans" << std::endl;
	Plan plan;
	std::vector<Mur> tab_murs;

	try {
		BDD bdd("tcp://localhost:3306", "plans", "isen", "isen29");
		plan = bdd.selectPlan(1);
		bdd.ajouterMurs(plan);
		for ( auto &mur : plan.getMurs() ){
			bdd.ajouterPoints(mur);
		}
		plan.affiche();
		//bdd.inserePlan(plan);
	}
	catch (sql::SQLException &e) {
		std::cout << "# ERR: " << e.what();
		std::cout << " (MySQL error code: " << e.getErrorCode();
		std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
	}
	catch(...){
		std::cout << "Exception non trappée"<<std::endl;
	}

	return EXIT_SUCCESS;
}
