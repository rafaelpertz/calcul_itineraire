#ifndef MINIVIEW_H
#define MINIVIEW_H
#include <QGraphicsView>
#include "../models/SceneCarte.h"

class MiniView : public QGraphicsView {
    Q_OBJECT
    public :
        // Constructeur : Initialise la MiniView avec la SceneCarte et le QWidget donnés
        MiniView(SceneCarte *scene, QWidget *w): QGraphicsView(scene, w) {
            Q_UNUSED(scene); // Empêche l'avertissement "variable inutilisée" pour 'scene'
            scale(1, -1); // Inverse l'axe Y pour correspondre aux conventions du système de coordonnées
        }

        ~MiniView(){}

    public slots:
        void trace_viewport(QRectF rect_viewport){
            cadre = rect_viewport; // Met à jour le 'cadre' avec le nouveau rectangle
            viewport()->update(); // Rafraîchit la mini-vue pour refléter le changement
        }

    protected:
        void drawForeground(QPainter *painter, const QRectF &) override {
            painter->setPen(QPen(Qt::red, 0)); // Définit un pinceau rouge pour dessiner le rectangle (cadre)
            painter->drawRect(cadre); // Dessine le rectangle 'cadre' sur la mini-vue
        }

        void drawBackground(QPainter *painter, const QRectF &) override {
            // Désactive la matrice monde pour travailler avec les coordonnées du viewport
            painter->setWorldMatrixEnabled(false);
        
            // Dessine d'abord l'arrière-plan bleu (couvre tout le viewport)
            painter->setBrush(QBrush(QColor(70, 130, 180))); // Code RGB pour le bleu
            painter->setPen(Qt::NoPen); // Pas de bordure
            painter->drawRect(viewport()->x(), viewport()->y(), viewport()->width(), viewport()->height());
        }
        
        void resizeEvent(QResizeEvent *) override {
            if (this->transform().m11() == 1) { // Vérifie si la transformation n'a pas d'échelle appliquée
                this->fitInView(sceneRect(), Qt::KeepAspectRatio); // Ajuste la vue pour qu'elle tienne dans la scène
            }
        }

    private:
        // Rectangle représentant la zone de la vue principale qui doit être mise en évidence dans la mini-vue
        QRectF cadre; 
};

#endif
