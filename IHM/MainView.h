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

#include "model/SceneCarte.hpp"

/**
 * @class MainView
 * @brief Shows the big scene in Qt
 *
 * This class allows to draw the information in the Big scene.
 * It handles interactions with the scene, such as zooming, panning,
 * and right-clicking to interact with cities on the map.
 *
 * @author Boris Gangue & Gaspard Vieujean
 * @date April 2, 2025 & April 9, 2025
 */

 class MainView : public QGraphicsView {
	Q_OBJECT
	public :
		// Constructor initializes the view with a given scene and orientation.
		// It also sets up basic properties for the view.
		MainView(SceneCarte *scene, QWidget *w, int orientation_nord = 0): QGraphicsView(scene, w), orientation_nord(orientation_nord) {
			Q_UNUSED(scene);
			scale(1, -1); // Inverts the Y-axis (flips the scene vertically)
			setMouseTracking(true); // Enables tracking mouse movements
			setViewportUpdateMode(QGraphicsView::FullViewportUpdate); // Improves performance, especially for the north arrow
		}

		// Destructor
		~MainView(){}

	signals:
		// Signal to send the current viewport coordinates
		void coord_viewport(QRectF);
		// Signal to send the mouse position in the scene
		void position(QPointF);

	protected:
		// Event handlers

		// Handles resizing of the view (fits the scene in the view if unscaled)
		void resizeEvent (QResizeEvent*) override {
			if (this->transform().m11() == 1) {
				this->fitInView(sceneRect(), Qt::KeepAspectRatio); // Ensures the scene fits within the view
			}
		}

		// Handles mouse wheel events for zooming in or out
		void wheelEvent(QWheelEvent *event) override{
			int angle = event->angleDelta().y();
			qreal facteur_zoom = (angle > 0) ? 1.1 : 0.9; // Adjust zoom factor based on wheel direction
			scale(facteur_zoom, facteur_zoom); // Apply the zoom scale
		}

		// Custom paint event for drawing elements in the background of the scene
		void paintEvent (QPaintEvent * event) override {
			// Get the bounding rectangle of the viewport in scene coordinates
			QPolygonF poly = mapToScene(viewport()->x(),viewport()->y(),viewport()->width(),viewport()->height());
			QRectF rect_viewport = poly.boundingRect();

			emit coord_viewport(rect_viewport); // Emit the current viewport coordinates
			// Pass the event to the base class for the actual painting
			QGraphicsView::paintEvent(event);
		}

		// Mouse move event handler to track mouse position on the scene
		void mouseMoveEvent(QMouseEvent *event) override{
			QPointF pos_scene = mapToScene(event->pos()); // Convert mouse position to scene coordinates
			emit position(pos_scene); // Emit the position to any listeners
			// Pass the event to the base class
			QGraphicsView::mouseMoveEvent(event);
		}

		// Mouse press event handler for right-click interactions
		void mousePressEvent(QMouseEvent *event) override{
			if(event->button() == Qt::RightButton){ // Check if right-click is pressed
				QPointF pos_scene = mapToScene(event->pos()); // Convert click position to scene coordinates
				QGraphicsItem *item = scene()->itemAt(pos_scene, transform()); // Get item under the click

				if(item) {
					QString villeName = item->data(0).toString(); // Retrieve the city name from the item
					if(!villeName.isEmpty()) {
						// Create a context menu for the right-click
						QMenu contextMenu;
						QAction *openWikipediaAction = new QAction("Afficher le wikipédia de la ville", this);
						contextMenu.addAction(openWikipediaAction);

						// Connect the action to open the city's Wikipedia page when triggered
						connect(openWikipediaAction, &QAction::triggered, this, [villeName](){
							QString url = QString("https://fr.wikipedia.org/wiki/%1").arg(villeName); // Format the URL
							QDesktopServices::openUrl(QUrl(url)); // Open the URL in the default browser
						});
						
						contextMenu.exec(QCursor::pos()); // Show the context menu at the cursor's position
					}
				} else {
					// If no item was clicked, handle the event like a regular click
					QGraphicsView::mousePressEvent(event);
				}
			}
		}

		// Custom background drawing function for painting static elements like the north arrow
		void drawBackground(QPainter *painter, const QRectF &) override {
			// Disable world matrix to work in viewport coordinates
			painter->setWorldMatrixEnabled(false);
		
			// Draw blue background first (covers entire viewport)
			painter->setBrush(QBrush(QColor(70, 130, 180))); // RGB for blue
			painter->setPen(Qt::NoPen); // No border
			painter->drawRect(viewport()->x(), viewport()->y(), viewport()->width(), viewport()->height());
			
			painter->setWorldMatrixEnabled(false); // Use viewport coordinates (pixels) instead of scene coordinates
			QPixmap pixmap("../ressource/images/north.png"); // Load the north arrow image
			QTransform matrice;
			matrice.rotate(orientation_nord); // Rotate the image according to the given north orientation
			QPixmap pixmap2 = pixmap.transformed(matrice); // Apply the transformation

			// Draw the rotated north arrow on the scene
			painter->drawPixmap(viewport()->x(), viewport()->y(), pixmap2);
			painter->setWorldMatrixEnabled(true); // Re-enable scene coordinates
		}

		// Custom foreground drawing function for painting dynamic elements like a scale bar
		void drawForeground(QPainter *painter, const QRectF &) override {
			painter->setTransform(QTransform(), false); // Switch to view coordinates (pixels)
			painter->setPen(QPen(Qt::black, 2)); // Set the pen for drawing

			QFont font("Arial", 12, QFont::Bold); // Define the font for text
			painter->setFont(font);
		
			// Draw a scale bar in the bottom-right corner
			int scaleBarLength = 50; // Length of the scale bar in pixels
			int x2 = this->width() - 10;  // Right edge of the scale bar (10px margin)
			int y2 = this->height() - 10; // Bottom edge of the scale bar (10px margin)
			int x1 = x2 - scaleBarLength; // Left edge of the scale bar
			int y1 = y2;
			
			int tickLength = 3; // Length of ticks on the scale bar
		
			// Draw the scale bar and ticks
			painter->drawLine(x1, y1, x2, y2);
			painter->drawLine(x1, y1 - tickLength, x1, y1 + tickLength);
			painter->drawLine(x2, y2 - tickLength, x2, y2 + tickLength);
		
			// Adjust the text position and draw the label "10 km"
			QFontMetrics metrics(font);
			int textWidth = metrics.horizontalAdvance("10 km");
			QRectF rect_texte(x1 + (scaleBarLength - textWidth) / 2, y1 - 25, textWidth, 20);
			painter->drawText(rect_texte, Qt::AlignCenter | Qt::TextDontClip, "10 km");
		}

	private:
		int orientation_nord; // The current north orientation angle
};


#endif
