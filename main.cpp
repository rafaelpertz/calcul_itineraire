#include <iostream>
#include <QApplication>
#include <QMessageBox>

/*===Include of project===*/
#include <cppconn/exception.h>
#include "model/Carte.hpp"
#include "model/BDD.hpp"
#include "model/SceneCarte.hpp"
#include "view/MainWindow.hpp"
#include "view/LoginDialog.hpp"

int main (int argc, char **argv){
    QApplication app(argc,argv);
    LoginDialog dlg;
    std::string host, base, user, pwd;


    if(!dlg.exec()){
        std::cout << "Sortie de l'application\n";
        return 1;
    }

    //Récupération des saisies après fermeture de la Dialog box
    dlg.getResult(host, base, user, pwd);
    std::cout << "Lecture base routeplanner" << std::endl;
    Carte carte;

    /*host = "localhost";
    base = "routeplanner";
    user = "routePlanner";
    pwd = "azerty1234";*/

    try {
        BDD bdd("tcp://"+host+":3306",base,user,pwd);
        carte = bdd.getCarte();
        std::cout << "Successfully get the map !! \n";
    }
    catch (sql::SQLException &e){
        std::cout << "Erreur MYSQL, sortie du programme\n";
        QMessageBox msg(QMessageBox::Critical, "Erreur mySQL", e.what());
        msg.exec();
        return 1;
    }


    MainWindow mw(carte);
    mw.show();

    return app.exec();
}
