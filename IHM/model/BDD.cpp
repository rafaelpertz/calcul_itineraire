#include "BDD.h"

BDD::BDD ( std::string host, std::string nomBDD, std::string login, std::string pwd){
		/* Create a connection */
		sql::Driver *driver { get_driver_instance() };
		con = driver->connect(host, login, pwd);

		/* Connect to the MySQL database */
		con->setSchema(nomBDD);

		setlocale(LC_ALL,"C");
}
BDD::~BDD(){
	std::cout << "Fermeture connection\n";
	delete con;
}

Plan BDD::selectPlan(int id){

	sql::Statement *stmt { con->createStatement() };
	sql::ResultSet *res { stmt->executeQuery(
					"select * from plan where id_plan="+std::to_string(id) ) };
	res->next();
	Plan plan{ res->getInt(1), res->getString(2),
						res->getInt(3), res->getInt(4), res->getString(5) };

	delete res;
	delete stmt;

	return plan;
}

void BDD::inserePlan(Plan &plan){

	sql::Statement *stmt {con->createStatement()};
	// Ajout nouveau plan
	stmt->execute("insert into plan values (null,'" // null => auto_increment
			+plan.getNomProjet()+"',"
			+std::to_string(plan.getVersion())+","
			+std::to_string(plan.getOrientation())
			+",sysdate())"
			);
	for ( auto &mur : plan.getMurs() ){
		// Ajout mur
		// récup id_plan
		sql::ResultSet *res { stmt->executeQuery("select last_insert_id()") };
		res->next();
		int id { res->getInt(1) };		
		delete res;
		
		stmt->execute("insert into mur values ("
				+std::to_string(id)+",'"
				+mur.getNomMur()+"','"
				+mur.getCouleur()+"',"
				+std::to_string(mur.getEpaisseur())+")"
				);
		// Ajout point
		for ( auto &pt : mur.getPoints() ){
		stmt->execute("insert into point values ("
				+std::to_string(id)+",'"
				+mur.getNomMur()+"',"
				+std::to_string(pt.getNum())+","
				+std::to_string(pt.getX())+","
				+std::to_string(pt.getY())+")"
				);
		} // fin insert point

	} // fin insert mur
	
	delete stmt;
}

void BDD::ajouterMurs(Plan &plan){

	sql::Statement *stmt { con->createStatement() };
	sql::ResultSet *res { stmt->executeQuery(
				"select * from mur where id_plan="
					+ std::to_string(plan.getIdPlan()) ) };
	while (res->next()) {
		plan.ajoutUnMur(Mur(res->getInt(1),res->getString(2),res->getString(3),res->getDouble(4)) );
	}
	delete res;
	delete stmt;
}
void BDD::ajouterPoints(Mur &mur){

	sql::Statement *stmt { con->createStatement() };
	sql::ResultSet *res { stmt->executeQuery(
				"select * from point where id_plan="
						+ std::to_string(mur.getIdPlan())
						+ " and nom_mur='"+mur.getNomMur()+"'"
						+ " order by num" ) };
	while (res->next()) {
		Point pt (res->getInt(1),res->getString(2),res->getInt(3),res->getDouble(4),res->getDouble(5));
		mur.ajoutUnPoint(pt);
	}
	delete res;
	delete stmt;
}

Plan BDD::getPlan(int id){
	Plan plan { this->selectPlan(1) };
	this->ajouterMurs(plan);
	for ( auto &mur : plan.getMurs() ){
		this->ajouterPoints(mur);
	}
	return plan;
}
