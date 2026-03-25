#include "FenetrePrincipale.h"


FenetrePrincipale::FenetrePrincipale(Plan &plan_init) : plan{plan_init} {

	widget_general = new QWidget;
	auto qbl_general {new QHBoxLayout};
	widget_general->setLayout(qbl_general);
	this->setCentralWidget(widget_general);

	largeur = 600; // qApp->desktop()->screenGeometry().width() / 2;
	hauteur = 400; // qApp->desktop()->screenGeometry().height() / 2;
	setMinimumSize(largeur,hauteur);

	myscene = new ScenePlan{plan};
	myview1 = new GrandeVue{myscene, this, plan.getOrientation()};

	qbl_general->addWidget(creerGroupBoxInfos());

	qbl_general->addWidget(myview1);
	barre_statut = statusBar();
	
	connect( myview1, &GrandeVue::coord_viewport, myview2, &MiniVue::trace_viewport);
	connect( myview1, &GrandeVue::position, this, &FenetrePrincipale::affiche_pos_scene);
	

}

FenetrePrincipale::~FenetrePrincipale() {
}

QGroupBox * FenetrePrincipale::creerGroupBoxInfos() {
	auto gb {new QGroupBox{tr("Infos plan")}};
	gb->setMaximumWidth(largeur/3);
	QString str_tmp;

	auto vbox {new QVBoxLayout};
	gb->setLayout(vbox);

	str_tmp = QString::fromStdString(std::to_string(plan.getIdPlan()));
	auto id_plan {new QLabel{"Plan N°"+str_tmp}};

	str_tmp = QString::fromStdString(plan.getNomProjet());
	auto nom_projet {new QLabel{str_tmp}};

	str_tmp = QString::fromStdString(std::to_string(plan.getVersion()));
	auto version {new QLabel{"Version "+str_tmp}};

	str_tmp = QString::fromStdString(plan.getDatePlan());
	auto date_plan {new QLabel{str_tmp}};

	myview2 = new MiniVue{myscene, this};

	vbox->addWidget(id_plan);
	vbox->addWidget(nom_projet);
	vbox->addWidget(version);
	vbox->addWidget(date_plan);
	vbox->addWidget(myview2);

	return gb;
}

void FenetrePrincipale::affiche_pos_scene( QPointF p){
	QString msg { "Coordonnées scène ("
			+ QString::number(p.x(),'f',2) + ","
			+ QString::number(p.y(),'f',2) + ")" };
	barre_statut->showMessage(msg);
}


