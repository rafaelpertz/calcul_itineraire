#ifndef MINIVIEW_H
#define MINIVIEW_H
#include <QGraphicsView>

#include "model/SceneCarte.hpp"

/**
 * @class MiniView, derived class of QGraphicsView
 * @brief Manages a collection of contacts.
 *
 * This class draws a small view on the bottom of the QGroupBox
 *
 * @author Boris Gangue
 * @date April 3, 2025
 */
class MiniView : public QGraphicsView {
    Q_OBJECT
    public :
        // Constructor: Initializes the MiniView with the given SceneCarte and QWidget
        MiniView(SceneCarte *scene, QWidget *w): QGraphicsView(scene, w) {
            Q_UNUSED(scene); // Prevents unused warning for 'scene'
            scale(1, -1); // Invert the y-axis to match coordinate system conventions
        }

      

        ~MiniView(){}

    public slots:
        void trace_viewport(QRectF rect_viewport){
            cadre = rect_viewport; // Update the 'cadre' (frame) with the new rectangle
            viewport()->update(); // Refresh the mini view to reflect the change
        }

    protected:
        void drawForeground(QPainter *painter, const QRectF &) override {
            painter->setPen(QPen(Qt::red, 0)); // Set a red pen for drawing the rectangle (frame)
            painter->drawRect(cadre); // Draw the 'cadre' rectangle on the mini view
        }

        void drawBackground(QPainter *painter, const QRectF &) override {
			// Disable world matrix to work in viewport coordinates
			painter->setWorldMatrixEnabled(false);
		
			// Draw blue background first (covers entire viewport)
			painter->setBrush(QBrush(QColor(70, 130, 180))); // RGB for blue
			painter->setPen(Qt::NoPen); // No border
			painter->drawRect(viewport()->x(), viewport()->y(), viewport()->width(), viewport()->height());
		}
		
        void resizeEvent(QResizeEvent *) override {
            if (this->transform().m11() == 1) { // Check if the transformation is not scaled
                this->fitInView(sceneRect(), Qt::KeepAspectRatio); // Fit the view to the scene
            }
        }

    private:
        QRectF cadre; // Rectangle representing the area of the main view that should be highlighted in the mini view
};

#endif
