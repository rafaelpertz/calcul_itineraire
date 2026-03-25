#include "LoginDialog.h"

LoginDialog::LoginDialog (QWidget *parent):QDialog{parent} {
	setWindowTitle( tr("BDD Login") );

	// widgets vars locales
	auto hostLabel {new QLabel{tr("Hôte (nom ou ip) ")}};
	auto baseLabel {new QLabel{tr("Nom base données ")}};
	auto userLabel {new QLabel{tr("User base ")}};
	auto pwdLabel {new QLabel{tr("Mot de passe ")}};

	auto loginBtn {new QPushButton{tr("Login")}};
	auto exitBtn {new QPushButton{tr("Annuler")}};

	// widgets attributs
	hostEditLine = new QLineEdit;
	hostEditLine->setText("localhost");
	baseEditLine = new QLineEdit;
	baseEditLine->setText("plans");
	userEditLine = new QLineEdit;
	pwdEditLine = new QLineEdit;
	pwdEditLine->setEchoMode(QLineEdit::Password);

	// set up the layout
	auto formGridLayout {new QGridLayout};
	// place components into the dialog
	formGridLayout->addWidget( hostLabel, 0, 0 );
	formGridLayout->addWidget( hostEditLine, 0, 1 );
	formGridLayout->addWidget( baseLabel, 1, 0 );
	formGridLayout->addWidget( baseEditLine, 1, 1 );
	formGridLayout->addWidget( userLabel, 2, 0 );
	formGridLayout->addWidget( userEditLine, 2, 1 );
	formGridLayout->addWidget( pwdLabel, 3, 0 );
	formGridLayout->addWidget( pwdEditLine, 3, 1 );
	formGridLayout->addWidget( loginBtn, 4, 0 );
	formGridLayout->addWidget( exitBtn, 4, 1 );

	setLayout( formGridLayout );

	// The signal is associated with the slot
	connect(loginBtn, &QPushButton::clicked, this, &LoginDialog::login);
	connect(exitBtn, &QPushButton::clicked, this, &QDialog::close);
}

LoginDialog::~LoginDialog(){
}

void LoginDialog::login(){

	hostname = hostEditLine->text();
	basename = baseEditLine->text();
	username = userEditLine->text();
	password = pwdEditLine->text();

	if ( !hostname.size() || !basename.size() ||
	  !username.size() || !password.size() ){
		QMessageBox::warning(this, tr("Warning"),
			tr("Tous les champs doivent être remplis"));
		return;
	}
	accept();
}
void LoginDialog::getResult(std::string& host, std::string& base,
    std::string& user, std::string& pwd ){
	host = hostname.toStdString();
	base = basename.toStdString();
	user = username.toStdString();
	pwd = password.toStdString();
}
