#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <cmath> 
#include <QMainWindow> // Already include QWidgets
#include <QGraphicsView>
#include <QApplication>

#include "MainView.hpp"
#include "MiniView.hpp"

#include "model/Carte.hpp"
#include "model/SceneCarte.hpp"

// For widget
#include <QVBoxLayout>
#include <QHBoxLayout>
#include<QGroupBox>
#include<QLabel>
#include <QStatusBar>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

/**
 * @class MainWindow, derived clas of QMainWindow
 * @brief Contains the groupBox, big and small vue
 *
 * This class shows a big interface with all the views 
 *
 * @author Boris Gangue
 * @date April 3, 2025
 */

class MainWindow: public QMainWindow {
    Q_OBJECT
    public:
        // Construtor
        MainWindow(Carte& carte);

        // Destructor
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
