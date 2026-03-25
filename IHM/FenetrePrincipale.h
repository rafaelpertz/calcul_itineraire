#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H
#include <QGroupBox>
#include <QLayout>
#include <QGraphicsView>
#include <QLabel>
#include <QMainWindow>
#include <QStatusBar>
#include <QString>

#include "model/Plan.h"
#include "ScenePlan.h"
#include "GrandeVue.h"
#include "MiniVue.h"

class FenetrePrincipale : public QMainWindow {
	Q_OBJECT
	public:
		FenetrePrincipale(Plan &plan);
		~FenetrePrincipale();
	private:
		QGroupBox * creerGroupBoxInfos();
	private slots:
		void affiche_pos_scene( QPointF p);
	private:
		QWidget * widget_general;
		ScenePlan *myscene;
		GrandeVue *myview1;
		MiniVue *myview2;
		QStatusBar *barre_statut;

		Plan &plan;
		int hauteur;
		int largeur;
		
};
#endif
