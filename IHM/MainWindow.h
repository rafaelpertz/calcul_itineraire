#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <cmath> 
#include <QMainWindow> 
#include <QGraphicsView>
#include <QApplication>

#include "MainView.h"
#include "MiniView.h"
#include "../models/Carte.h"
#include "../models/SceneCarte.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include<QGroupBox>
#include<QLabel>
#include <QStatusBar>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

class MainWindow: public QMainWindow {
	Q_OBJECT
	public:
		MainWindow(Carte& carte);

		virtual ~MainWindow(){}

	public slots:
		void geoCoordsSlot(QPointF p);
		void slotCompute();
		void slotInvalidVille(const std::string& invalid_ville);


	private:
		QLineEdit* startLineEdit;
		QLineEdit* arrivalLineEdit;
		QPushButton* compute;
		QLabel* distance;
		QLabel* precision;
		QWidget* mainWidget;
		QStatusBar* statusBar;
		QLabel* distanceLabel;
		// Dimensions 
		int width;
		int height;
		// Views
		MiniView* miniView;
		MainView* mainView;
		// Scene
		SceneCarte* sceneCarte;
		Carte& carte;
		// Methods
		QGroupBox* createGroupBoxInfos();
		std::string decimalToDMS(double decimal, char positive, char negative);
		void xyToLatLon(double x, double y, float &lon, float &lat);
};

#endif
