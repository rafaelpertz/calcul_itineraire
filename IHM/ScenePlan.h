#ifndef MYSCENE_H
#define MYSCENE_H
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDebug>
#include <QPainter>

#include "model/Plan.h"

class ScenePlan : public QGraphicsScene {
	Q_OBJECT
	public :
		ScenePlan(Plan &);
		void creer_items(Plan &);
	private:
		static inline std::map<std::string, QColor> tab_couleurs 
				{{"rouge", Qt::red}, {"vert", Qt::green}};
};

#endif
