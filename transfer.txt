#include "MainWindow.hpp"

/**
 * @brief Initialize the main window with its widgets
 * 
 * @param carte Carte that has all informations from the DB
 * Constructor of the class MainWindow
 */
MainWindow::MainWindow(Carte& carte) : carte(carte) {

    // Init the general widget and set the window title
    this->setWindowTitle("Route-Planner");
    this->mainWidget = new QWidget; // Create the main widget
    QHBoxLayout* qbl_general = new QHBoxLayout; // Create a horizontal layout for the main widget
    this->mainWidget->setLayout(qbl_general); 
    this->setCentralWidget(this->mainWidget); 
    
    // Init the windows size and set minimum size
    this->width = 900; 
    this->height = 600;
    setMinimumSize(this->width, this->height); // Ensure the window is at least 900x600 pixels
    
    // Initialize the scene and view for the map
    this->sceneCarte = new SceneCarte(carte); 
    this->mainView = new MainView(this->sceneCarte, this); 

    // Add the group box and main view to the layout
    qbl_general->addWidget(createGroupBoxInfos());
    qbl_general->addWidget(this->mainView); 

    // Initialize the status bar at the bottom of the window
    this->statusBar = new QStatusBar;
    this->setStatusBar(this->statusBar); // Set the status bar for the main window
    
    // Connect signals to their respective slots
    connect(this->mainView, &MainView::coord_viewport, this->miniView, &MiniView::trace_viewport);
    connect(this->mainView, &MainView::position, this, &MainWindow::geoCoordsSlot);
    connect(this->compute, &QPushButton::clicked, this, &MainWindow::slotCompute);
    connect(this->sceneCarte, &SceneCarte::signalInvalidVille, this, &MainWindow::slotInvalidVille);
}

/**
 * @brief Initialize the groupbox in top of the small scene
 * 
 * @return GroupBox
 */
QGroupBox* MainWindow::createGroupBoxInfos() {
    QGroupBox* gb = new QGroupBox;  
    gb->setMaximumWidth(this->width/3); // Limit the group box width to one-third of the window's width

    QVBoxLayout *vbox = new QVBoxLayout;  
    gb->setLayout(vbox);  
    
    // Create and add widgets for departure and arrival city labels, input fields, and distance label
    QLabel* startLabel = new QLabel("Departure City");
    QLabel* arrivalLabel = new QLabel("Arrival City");
    this->distanceLabel = new QLabel("Distance: 0 km");  

    this->startLineEdit = new QLineEdit;  
    this->startLineEdit->setPlaceholderText("Departure...");  
    this->arrivalLineEdit = new QLineEdit; 
    this->arrivalLineEdit->setPlaceholderText("Arrival...");  
    
    this->compute = new QPushButton("Go");  
    this->miniView = new MiniView(this->sceneCarte, this);  
    
    // Add all widgets to the vertical layout
    vbox->addWidget(startLabel);
    vbox->addWidget(startLineEdit);
    vbox->addWidget(arrivalLabel);
    vbox->addWidget(arrivalLineEdit);
    vbox->addWidget(compute);
    vbox->addWidget(distanceLabel);
    vbox->addWidget(this->miniView);

    return gb;  
}

/**
 * @brief Function to convert decimal degrees to D°MM.M' format
 * 
 * @param decimal decimal variable
 * @param positive positive variable (N or E)
 * @param negative nagative variable (S or W)
 *
 * @return void
 */
std::string MainWindow::decimalToDMS(double decimal, char positive, char negative) {
    char direction = (decimal >= 0) ? positive : negative; // Determine the direction (N/S/E/W)
    decimal = std::fabs(decimal);  // Work with absolute value

    int degrees = (int)decimal;  // Extract degrees
    double minutes = (decimal - degrees) * 60;  // Convert remainder to minutes

    // Format as D°MM.M'
    char buffer[20];
    snprintf(buffer, sizeof(buffer), "%d°%.2f'%c", degrees, minutes, direction);
    return std::string(buffer);  
}

/**
 * @brief Function that convert the coordinates in degrees 
 * 
 * @param x coordinate x
 * @param y coordinate y
 * @param lon longitude variable
 * @param lat latitude variable
 *
 * @return void
 */
void MainWindow::xyToLatLon(double x, double y, float &lon, float &lat) {
    const double EARTH_RADIUS = 6378137.0; // Earth's radius in meters

    // Convert km back to meters
    x *= 1000;
    y *= 1000;

    // Compute longitude in degrees
    lon = (x / EARTH_RADIUS) * (180.0 / M_PI);

    // Compute latitude in degrees
    lat = (2 * atan(exp(y / EARTH_RADIUS)) - M_PI / 2) * (180.0 / M_PI);
}

/*============================= SLOTS ==============================*/

/**
 * @brief Slot for when a waypoint clicked it show the coordinates
 * 
 * @param p waypoint clicked
 * @return void
 */
void MainWindow::geoCoordsSlot(QPointF p) {
    float lat, lon;
    this->xyToLatLon(p.x(), p.y(), lon, lat); // Convert the coordinates from scene space to lat/lon
    std::string latStr = this->decimalToDMS(lat, 'N', 'S');  
    std::string lonStr = this->decimalToDMS(lon, 'E', 'W');  

    // Show coordinates in the status bar
    QString msg = "Stage coordinates: (" + QString::fromStdString(latStr) + ", " + QString::fromStdString(lonStr) + ")";
    this->statusBar->showMessage(msg);
}

/**
 * @brief Slot for the groupBox of the starting city and destination city
 * 
 * @return void
 */
void MainWindow::slotCompute() {
    // Get input values
    QString wp_start = this->startLineEdit->text();
    QString wp_end = this->arrivalLineEdit->text();
 
    QString error_message = "";
    // Validation checks for empty input fields
    if(wp_start.isEmpty()) {
      error_message = "The starting field is empty !";
    } else if(wp_end.isEmpty()) {
      error_message = "The destination field is empty !";
    } else {
        // Draw the shortest path if both fields are filled
        this->sceneCarte->computeAndDrawShortestPath(wp_start.toStdString(), wp_end.toStdString());
 
        // Compute and update distance between source and destination
        this->distanceLabel->setText("Distance: " + QString::fromStdString(std::to_string(this->sceneCarte->getDistance())) + " Km");
 
       return;
    }
 
    // Show error message if validation failed
    QMessageBox::critical(nullptr, "ERROR", error_message);   
}

/**
 * @brief Slot for handling invalid city input
 * 
 * @param invalid_ville Name of the invalid city
 * @return void
 */
void MainWindow::slotInvalidVille(const std::string& invalid_ville) {
    QMessageBox::warning(nullptr, "WARNING", QString("%1 is not a city!").arg(QString::fromStdString(invalid_ville)));
}
