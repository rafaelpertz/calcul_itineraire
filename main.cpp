#include <iostream>
#include <QApplication>
#include <QMessageBox>

#include <cppconn/exception.h>
#include "models/Carte.h"
#include "models/BDD.h"
#include "IHM/MainWindow.h"
#include "IHM/LoginDialog.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    LoginDialog dlg;
    std::string host, base, user, pwd;

    if (!dlg.exec())
    {
        std::cout << "Application fermee par l'utilisateur." << std::endl;
        return 0;
    }

    dlg.getResult(host, base, user, pwd);

    Carte carte;

    try
    {
        std::cout << "Connexion a la base de donnees..." << std::endl;

        BDD bdd("tcp://" + host + ":3306", base, user, pwd);
        carte = bdd.getCarte();

        std::cout << "Chargement des donnees reussi !" << std::endl;

        if (carte.getWaypoints().empty())
        {
            throw std::runtime_error("Aucun waypoint charge !");
        }
    }
    catch (sql::SQLException &e)
    {
        QMessageBox::critical(nullptr, "Erreur MySQL", e.what());
        return 1;
    }
    catch (std::exception &e)
    {
        QMessageBox::critical(nullptr, "Erreur", e.what());
        return 1;
    }
    
    MainWindow mainWindow(carte);
    mainWindow.setWindowTitle("Calcul d'itineraire");

    mainWindow.show();
    return app.exec();
}
