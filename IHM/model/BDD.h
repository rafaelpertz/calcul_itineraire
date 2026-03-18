#ifndef BDD_H
#define BDD_H

#include <iostream>
#include <string>
#include <vector>
#include <clocale>

#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

#include "Plan.h"
#include "Mur.h"
#include "Point.h"

class BDD {
	public :
		BDD ( std::string host, std::string nomBDD, std::string login, std::string pwd);
		BDD (){}
		~BDD();

		Plan selectPlan(int id);
		void ajouterMurs(Plan &plan);
		void ajouterPoints(Mur &mur);
		Plan getPlan(int id);
		void inserePlan(Plan &plan);

	private :
		Plan plan;
		sql::Connection *con;
};
#endif
