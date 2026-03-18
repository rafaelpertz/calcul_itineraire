// includes VIEW
#include <QApplication>
#include <QMessageBox>
#include "LoginDialog.h"
#include "FenetrePrincipale.h"

// includes MODEL
#include <cppconn/exception.h>
#include "model/Plan.h"
#include "model/BDD.h"

int main(int argc, char **argv) {

	QApplication app{argc, argv};

	LoginDialog dlg;
	std::string host, base, user, pwd;

	if ( ! dlg.exec() ){ // Ouverture de la boite de dialogue
		std::cout << "Sortie de l'application\n";
		return 1;
	}
	// Récupération des saisies après fermeture de la Dialog box
	dlg.getResult(host, base, user, pwd);

	std::cout << "Lecture base plans" << std::endl;
	Plan plan;

	try {
		// Connexion BD
		BDD bdd{"tcp://"+host+":3306", base, user, pwd};
		// Récupération du plan
		plan = bdd.getPlan(1);
		plan.affiche();
	}
	catch (sql::SQLException &e) {
		std::cout << "Erreur MySQL. Sortie de l'application\n";
		QMessageBox msg{ QMessageBox::Critical, "Erreur mySQL", e.what()};
		msg.exec();
		return 1;
	}
	
	FenetrePrincipale mw { plan };
	mw.show();

	return app.exec();
}
