#include "MainWindow.h"

MainWindow::MainWindow(Carte& carte) : carte(carte) {

	// initialise la fenetre et le titre 
	this->setWindowTitle("Route-Planner");
	this->mainWidget = new QWidget; // creation the main widget
	QHBoxLayout* qbl_general = new QHBoxLayout; // creation a horizontal layout pour main widget
	this->mainWidget->setLayout(qbl_general); 
	this->setCentralWidget(this->mainWidget); 

	// Init the windows size and set minimum size
	this->width = 900; 
	this->height = 600;
	setMinimumSize(this->width, this->height); // Ensure the window is at least 900x600 pixels

	// initialise la scene et view pour la map
	this->sceneCarte = new SceneCarte(carte); 
	this->mainView = new MainView(this->sceneCarte, this); 

	// ajoute le group box et main view au layout
	qbl_general->addWidget(createGroupBoxInfos());
	qbl_general->addWidget(this->mainView); 

	// Initialise le status bar en bas de la window
	this->statusBar = new QStatusBar;
	this->setStatusBar(this->statusBar); 

	// Connect signals to their respective slots
	connect(this->mainView, &MainView::coord_viewport, this->miniView, &MiniView::trace_viewport);
	connect(this->mainView, &MainView::position, this, &MainWindow::geoCoordsSlot);
	connect(this->compute, &QPushButton::clicked, this, &MainWindow::slotCompute);
	connect(this->sceneCarte, &SceneCarte::signalInvalidVille, this, &MainWindow::slotInvalidVille);
}
// information du chemin voulu
QGroupBox* MainWindow::createGroupBoxInfos() {
	QGroupBox* gb = new QGroupBox;  
	gb->setMaximumWidth(this->width/3); 

	QVBoxLayout *vbox = new QVBoxLayout;  
	gb->setLayout(vbox);  

	QLabel* startLabel = new QLabel("depart ville");
	QLabel* arrivalLabel = new QLabel("arrivée ville");
	this->distanceLabel = new QLabel("Distance: 0 km");  

	this->startLineEdit = new QLineEdit;  
	this->startLineEdit->setPlaceholderText("depart...");  
	this->arrivalLineEdit = new QLineEdit; 
	this->arrivalLineEdit->setPlaceholderText("arriver...");  

	this->compute = new QPushButton("Go");  
	this->miniView = new MiniView(this->sceneCarte, this);  

	vbox->addWidget(startLabel);
	vbox->addWidget(startLineEdit);
	vbox->addWidget(arrivalLabel);
	vbox->addWidget(arrivalLineEdit);
	vbox->addWidget(compute);
	vbox->addWidget(distanceLabel);
	vbox->addWidget(this->miniView);

	return gb;  
}
// tranformer a latitudde et la longitude en format DMS
std::string MainWindow::decimalToDMS(double decimal, char positive, char negative) {
	char direction = (decimal >= 0) ? positive : negative; // Determiner the direction (N/S/E/W)
	decimal = std::fabs(decimal);  // valeur absolue

	int degrees = (int)decimal;  // Extractions des degrees
	double minutes = (decimal - degrees) * 60;  // Convertie en minute 

	// Format  D°MM.M'
	char buffer[20];
	snprintf(buffer, sizeof(buffer), "%d°%.2f'%c", degrees, minutes, direction);
	return std::string(buffer);  
}


void MainWindow::xyToLatLon(double x, double y, float &lon, float &lat) {
	const double EARTH_RADIUS = 6378137.0; // Terre rayon en metre

	// Convertir klm en metre
	x *= 1000;
	y *= 1000;

	// longitude in degree
	lon = (x / EARTH_RADIUS) * (180.0 / M_PI);

	// latitude in degree
	lat = (2 * atan(exp(y / EARTH_RADIUS)) - M_PI / 2) * (180.0 / M_PI);
}

void MainWindow::geoCoordsSlot(QPointF p) {
	float lat, lon;
	this->xyToLatLon(p.x(), p.y(), lon, lat); // Convertie les coordonnée de scene space to lat/lon
	std::string latStr = this->decimalToDMS(lat, 'N', 'S');  
	std::string lonStr = this->decimalToDMS(lon, 'E', 'W');  

	// montre les coordonnée dans la status bar
	QString msg = "Stage coordinates: (" + QString::fromStdString(latStr) + ", " + QString::fromStdString(lonStr) + ")";
	this->statusBar->showMessage(msg);
}

void MainWindow::slotCompute() {
	QString wp_start = this->startLineEdit->text();
	QString wp_end = this->arrivalLineEdit->text();

	QString error_message = "";
	if(wp_start.isEmpty()) {
	error_message = "The starting field is empty !";
	} else if(wp_end.isEmpty()) {
	error_message = "The destination field is empty !";
	} else {
	// dessine le chemin
	this->sceneCarte->computeAndDrawShortestPath(wp_start.toStdString(), wp_end.toStdString());

	// compile et met a jours la  distance entre la source et la destination
	this->distanceLabel->setText("Distance: " + QString::fromStdString(std::to_string(this->sceneCarte->getDistance())) + " Km");
 
        return;
    }
 
        // message d'erreur 
        QMessageBox::critical(nullptr, "ERROR", error_message);   
}

void MainWindow::slotInvalidVille(const std::string& invalid_ville) {
        QMessageBox::warning(nullptr, "WARNING", QString("%1 is not a city!").arg(QString::fromStdString(invalid_ville)));
}
