#include "ScenePlan.h"

ScenePlan::ScenePlan(Plan &plan)
{
	// Ajout des items graphiques dans la scène
	creer_items(plan);
}

void ScenePlan::creer_items(Plan &plan){

	qreal epais {0};// épaisseur mur
	std::string text_tooltip;
	
	for (auto &mur : plan.getMurs() ){
		QColor coul { tab_couleurs[mur.getCouleur()] };
		epais = mur.getEpaisseur();
		Point *points { mur.getPoints().data() };
		int nb_points { static_cast<int>(mur.getPoints().size()) }; // size() renvoie un size_t
		if ( !nb_points ) continue;
		
		QGraphicsLineItem *ligne { nullptr };

		for ( int i=0; i < nb_points-1; ++i ){

			ligne = new QGraphicsLineItem { points[i].getX(),points[i].getY(),
						  points[i+1].getX(), points[i+1].getY() };
			ligne->setPen(QPen(coul, epais, Qt::SolidLine));

			std::string  text_tooltip { mur.getInfos() };
			ligne->setToolTip(QString::fromStdString(text_tooltip));
			this->addItem(ligne);

			auto point { new QGraphicsEllipseItem ( -epais/2, -epais/2, epais, epais) };
			point->setPos(points[i].getX(), points[i].getY());
			point->setPen(QPen(Qt::black,0,Qt::SolidLine));
			point->setBrush(QBrush(Qt::gray,Qt::SolidPattern));

			text_tooltip = points[i].getInfos();
			point->setToolTip(QString::fromStdString(text_tooltip));

			point->setParentItem(ligne);
		} // fin création point
		// Dernier point
		auto point { new QGraphicsEllipseItem { -epais/2, -epais/2, epais, epais }};
		point->setPos(points[nb_points-1].getX(), points[nb_points-1].getY());
		point->setPen(QPen{Qt::black,0,Qt::SolidLine});
		point->setBrush(QBrush{Qt::gray,Qt::SolidPattern});

		text_tooltip = points[nb_points-1].getInfos();
		point->setToolTip(QString::fromStdString(text_tooltip));

		point->setParentItem(ligne);

	}// fin création mur

	// Matérialisation du point origine de la scène (taille = épaisseur mur)
	qreal taille_o {epais};
	auto origine { new QGraphicsEllipseItem{-taille_o/2,-taille_o/2,taille_o,taille_o}};
	origine->setPos(0,0);
	origine->setPen(QPen{Qt::black,0,Qt::SolidLine});
	this->addItem(origine);

}