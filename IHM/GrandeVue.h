#ifndef GRANDEVUE_H
#define GRANDEVUE_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QMouseEvent>

#include "ScenePlan.h"

class GrandeVue : public QGraphicsView {
	Q_OBJECT
	public :
		GrandeVue(ScenePlan *scene, QWidget *w, int orientation_nord):QGraphicsView{scene, w}, orientation_nord{orientation_nord}{
			Q_UNUSED(scene);
			scale(1, -1); // inversion des y
			setMouseTracking(true);
			setViewportUpdateMode(QGraphicsView::FullViewportUpdate);// important pour la North arrow
		}
		~GrandeVue(){}
	signals:
		void coord_viewport(QRectF);
		void position(QPointF);

	private:
		// Gestionnaires d'évènements

		// Fit de la vue sur les limites de la scène
		void resizeEvent (QResizeEvent * ) override {

			if ( this->transform().m11() == 1 ) {
				this->fitInView(sceneRect(), Qt::KeepAspectRatio);
			}
		}

		void wheelEvent(QWheelEvent *event) override{

			int angle {event->angleDelta().y()};
			qreal facteur_zoom {1};
			if (angle > 0 ){
				facteur_zoom = 1.1;
			} else {
				facteur_zoom = 0.9;
			}
			centerOn(mapToScene(event->position().toPoint()));// centrage approximatif
			scale ( facteur_zoom, facteur_zoom );					
		}

		void paintEvent (QPaintEvent * event) override {

			// déclenché par les wheelEvents ET les scollBars
			QPolygonF poly {mapToScene(viewport()->x(),viewport()->y(),viewport()->width(),viewport()->height())};
			QRectF rect_viewport {poly.boundingRect()};

			emit coord_viewport(rect_viewport);
			// re-propage l'évènement
			QGraphicsView::paintEvent(event);
		}
		void mouseMoveEvent(QMouseEvent *event) override{
			// Pb pour avoir position du curseur en coords Scene
			//QPointF pos_scene { mapToScene(event->pos()) }; // obsolète depuis 6.0
			//QPointF pos_scene { event->scenePosition() };// donne coords vue !!
			QPointF pos_scene {mapToScene(event->position().toPoint())};// depuis 6.0
			
			emit position(pos_scene);
			// re-propage l'évènement
			QGraphicsView::mouseMoveEvent(event);
		}
		void drawBackground( QPainter *painter, const QRectF &) override {

			//painter->save(); // pas utile
			painter->setWorldMatrixEnabled(false);// mettre en coords View (pixels)
			// Chargement image et rotation selon orientation plan
			QPixmap pixmap{"north.png"};
			QTransform matrice;
			matrice.rotate(orientation_nord);
			QPixmap pixmap2 {pixmap.transformed(matrice)};

			painter->drawPixmap(viewport()->x(),viewport()->y(),pixmap2);
			painter->setWorldMatrixEnabled(true);
			//painter->restore();  // pas utile
		}
		void drawForeground( QPainter *painter, const QRectF &) override {
		
			//painter->save();  // pas utile
			painter->setWorldMatrixEnabled(false);// mettre en coords View (pixels)
			painter->setPen(QPen{Qt::black, 0});
			qreal echelle { this->transform().m11() };
			int x2 { viewport()->x()+viewport()->width()-10 };
			int y2 { viewport()->y()+viewport()->height()-10 };
			int x1 { x2 - static_cast<int>(echelle) };
			int y1 { y2 };
			int longueur_tick { qMin(static_cast<int>(echelle/10),5) };
			painter->drawLine(x1,y1,x2,y2);
			painter->drawLine(x1,y1-longueur_tick,x1,y1+longueur_tick);
			painter->drawLine(x2,y2-longueur_tick,x2,y2+longueur_tick);
			QRectF rect_texte{ static_cast<qreal>(x1), static_cast<qreal>(y1-30), static_cast<qreal>(x2-x1), 20.0 };
			painter->drawText(rect_texte, Qt::AlignCenter|Qt::TextDontClip,"1 m");
			painter->setWorldMatrixEnabled(true);
			//painter->restore();  // pas utile
		}
	private:
		int orientation_nord;

};

#endif
