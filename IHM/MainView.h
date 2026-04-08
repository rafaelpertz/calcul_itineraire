#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QMenu>
#include <QAction>
#include <QDesktopServices>
#include <QUrl>
#include <QCursor>
#include "../models/SceneCarte.h"

 class MainView : public QGraphicsView {
    Q_OBJECT
    public :
        MainView(SceneCarte *scene, QWidget *w, int orientation_nord = 0)
            : QGraphicsView(scene, w), orientation_nord(orientation_nord) 
        {
            Q_UNUSED(scene);
            scale(1, -1); // Inverse l'axe Y 
            setMouseTracking(true); // Active le suivi de la souris 
        }

        ~MainView(){}

    signals:
        // Signal émis lors du changement de zone visible
        void coord_viewport(QRectF);
        // Signal émis lors du mouvement de la souris
        void position(QPointF);

    protected:
        // Gère le zoom interactif avec la molette de la souris.
        void wheelEvent(QWheelEvent *event) override{
            int angle = event->angleDelta().y();
            qreal facteur_zoom = (angle > 0) ? 1.1 : 0.9;
            scale(facteur_zoom, facteur_zoom);
        }

        // Intercepte le rendu pour calculer et émettre les limites de la vue actuelle. 
        void paintEvent (QPaintEvent * event) override {
            QPolygonF poly = mapToScene(viewport()->rect());
            emit coord_viewport(poly.boundingRect());
            
            QGraphicsView::paintEvent(event);
        }

        //Suit le mouvement de la souris et émet sa position géographique.
        void mouseMoveEvent(QMouseEvent *event) override{
            emit position(mapToScene(event->pos()));
            QGraphicsView::mouseMoveEvent(event);
        }

        //Dessine l'arrière-plan (Océan) et l'indicateur fixe du Nord. 
        void drawBackground(QPainter *painter, const QRectF &) override {
            // 1. Dessin de l'eau en coordonnées "viewport" (fixe sur l'écran)
            painter->setWorldMatrixEnabled(false);
            painter->setBrush(QBrush(QColor(70, 130, 180))); // Bleu acier
            painter->setPen(Qt::NoPen);
            painter->drawRect(viewport()->rect());
            
            // 2. Dessin de l'icône de la boussole (Nord)
            QPixmap pixmap("../ressource/images/north.png");
            if (!pixmap.isNull()) {
                QTransform matrice;
                matrice.rotate(orientation_nord);
                QPixmap pixmapRotated = pixmap.transformed(matrice);
                painter->drawPixmap(10, 10, pixmapRotated); // Positionné en haut à gauche
            }
            
            painter->setWorldMatrixEnabled(true);
        }

        // Dessine les éléments d'interface par-dessus la carte (échelle de distance). 
        void drawForeground(QPainter *painter, const QRectF &) override {
            painter->setTransform(QTransform(), false); // On repasse en coordonnées écran (pixels)
            painter->setPen(QPen(Qt::black, 2));
            painter->setFont(QFont("Arial", 10, QFont::Bold));
        
            // Configuration de la barre d'échelle (placée en bas à droite)
            int scaleBarLength = 50;
            int margin = 15;
            int x2 = this->width() - margin;
            int y2 = this->height() - margin;
            int x1 = x2 - scaleBarLength;
            
            // Dessin de la ligne horizontale et des petits repères verticaux
            painter->drawLine(x1, y2, x2, y2);
            painter->drawLine(x1, y2 - 3, x1, y2 + 3);
            painter->drawLine(x2, y2 - 3, x2, y2 + 3);
        
            // Affiche la légende de l'échelle
            painter->drawText(QRect(x1, y2 - 25, scaleBarLength, 20), Qt::AlignCenter, "10 km");
        }

    private:
        int orientation_nord; // Angle de rotation du Nord
};

#endif
