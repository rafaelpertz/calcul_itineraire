#include "LoginDialog.h"

LoginDialog::LoginDialog(QWidget* parent) : QDialog(parent) {
	// Creation des buttons, labels et lineEdits
	this->hostLabel = new QLabel("Host");
	this->databaseLabel = new QLabel("Database");
	this->usernameLabel = new QLabel("Username");
	this->passwordLabel = new QLabel("Password");
	this->hostLineEdit = new QLineEdit;
	this->hostLineEdit->setPlaceholderText("Host...");
	this->usernameLineEdit = new QLineEdit;
	this->usernameLineEdit->setPlaceholderText("Username...");
	this->databaseLineEdit = new QLineEdit;
	this->databaseLineEdit->setPlaceholderText("Database...");
	this->passwordLineEdit = new QLineEdit;
	//passwordLineEdit->setEchoMode(QLineEdit::Password);  // Hides characters (•)
	this->passwordLineEdit->setPlaceholderText("Password...");
	this->loginButton = new QPushButton("Login");
	//this->loginButton->setStyleSheet("background-color: lightblue; color: black; font-weight: bold;");
	this->cancelButton = new QPushButton("Cancel");
	//this->cancelButton->setStyleSheet("background-color: red; color: black; font-weight: bold;");

	// ajouter les widgets au QGridLayout
	QGridLayout* gLayout = new QGridLayout;
	this->setLayout(gLayout);
	this->setWindowTitle("BDD Login");
	gLayout->addWidget(this->hostLabel, 0, 0);
	gLayout->addWidget(this->hostLineEdit, 0, 1);
	gLayout->addWidget(this->databaseLabel, 1, 0);
	gLayout->addWidget(this->databaseLineEdit, 1, 1);
	gLayout->addWidget(this->usernameLabel, 2, 0);
	gLayout->addWidget(this->usernameLineEdit, 2, 1);
	gLayout->addWidget(this->passwordLabel, 3, 0);
	gLayout->addWidget(this->passwordLineEdit, 3, 1);
	gLayout->addWidget(this->loginButton, 4, 0);
	gLayout->addWidget(this->cancelButton, 4, 1);

	// Slots connexions
	connect(this->loginButton, &QPushButton::clicked, this, &LoginDialog::slotLogin);
	connect(this->cancelButton, &QPushButton::clicked, this, &QDialog::close); // reject : QDialog's slot method

}

//obtention et initialisatiion des parametres de base de donnée
void LoginDialog::getResult(string& host, string& database, string& username, string& password) {
	   host = this->host.toStdString();
	   database =  this->database.toStdString();
	   username = this->username.toStdString();
	   password =  this->password.toStdString();
}


//Slot Login 
void LoginDialog::slotLogin() {
	QString host = this->hostLineEdit->text();
	QString database = this->databaseLineEdit->text();
	QString username = this->usernameLineEdit->text();
	QString password = this->passwordLineEdit->text();


	QString errorMessage = "";
	if(host.isEmpty()) {
		errorMessage = "Host is invalid !";
	} else if(database.isEmpty()) {
		errorMessage = "Database is invalid !";
	} else if(username.isEmpty()) {
		errorMessage = "Username is invalid !";
	} else if(password.isEmpty()) {
		errorMessage = "Password is invalid !";
	} else {
		this->host = host;
		this->database = database;
		this->username = username;
		this->password = password;
		this->accept();            
		return;
	}
	QMessageBox::critical(nullptr,"ERROR", errorMessage);   
}
